# Nome: Mikaelle Costa de Santana
# Matrícula: 22401909

import sys  # Importa módulo sys para acessar args e controlar saída

# Função para converter strings numéricas em inteiros
# Suporta decimal, hex (0x) e binário (0b)
def parse_num(val, line):
    """
    Converte val em inteiro. Se começar com '0x' ou '0b', int(val,0) detecta base.
    'line' é o número da linha para mensagens de erro.
    """
    try:
        if val.lower().startswith(('0x', '0b')):
            return int(val, 0)  # Interpreta como hex/bin
        return int(val, 10)     # Interpreta como decimal
    except ValueError:
        print(f"Linha {line}: valor inválido '{val}'")  # Erro de conversão
        sys.exit(1)  # Sai com erro

# Função para validar argumentos de entrada e saída
def check_args():
    """Verifica se script recebeu exatamente 2 args: entrada e saída."""
    if len(sys.argv) != 3:
        print("Uso: python assembler.py <entrada> <saida>")  # Instrução de uso
        sys.exit(1)
    return sys.argv[1], sys.argv[2]  # Retorna os nomes dos arquivos

# Codifica instrução de 1 byte com dois registradores
def encode_reg_pair(opcode, r1, r2, line):
    """
    opcode: string com prefixo hex da instrução
    r1, r2: registradores ('R0' a 'R3')
    line: número da linha para erros
    """
    for r in (r1, r2):
        if r not in REG:
            print(f"Linha {line}: registrador inválido '{r}'")
            sys.exit(1)
    bits = REG[r1] + REG[r2]  # Concatena bits dos registradores
    return opcode + format(int(bits, 2), 'x')  # Retorna opcode+regs

# Codifica instrução com imediato (DATA ou JMPR)
def encode_immediate(opcode, reg, raw, line, signed=False):
    """
    opcode: prefixo hex
    reg: registrador alvo
    raw: valor imediato em string
    signed: True para DATA (intervalo -128..127), False para JMPR
    """
    if reg not in REG:
        print(f"Linha {line}: registrador inválido '{reg}'")
        sys.exit(1)
    b1 = opcode + format(int(REG[reg], 2), 'x')  # Primeiro byte: opcode + reg
    num = parse_num(raw, line)  # Converte raw para inteiro
    # Validação de intervalo para valores decimais
    if signed and not raw.lower().startswith(('0x','0b')):
        if not -128 <= num <= 127:
            print(f"Linha {line}: valor fora do intervalo -128 a 127")
            sys.exit(1)
        num &= 0xFF  # Ajusta para complemento de 2
    elif not signed and not raw.lower().startswith(('0x','0b')):
        if not 0 <= num <= 255:
            print(f"Linha {line}: valor fora do intervalo 0 a 255")
            sys.exit(1)
    return [b1, '0x' + format(num, '02x')]  # Retorna opcode+imediato

# Codifica instruções de salto (JMP ou CLF)
def encode_jump(opcode, raw, line):
    """
    opcode: prefixo hex de JMP ou CLF
    raw: texto do operando (endereço) ou vazio para CLF
    """
    if opcode == INSTR2['CLF']:
        return [opcode]  # CLF não tem segundo byte

    addr = raw
    if(('0x' in addr) or ('0b' in addr)):
        addr = parse_num(raw, line)  # Converte endereço
        if not 0 <= addr <= 255:
            print(f"Linha {line}: endereço fora do intervalo 0 a 255")
            sys.exit(1)
        addr = '0x' + format(addr, '02x')
    return [opcode, addr]  # Retorna opcode+endereço

# Codifica saltos condicionais JCAEZ
def encode_conditional(flags, raw, line):
    """
    flags: string com letras C A E Z
    raw: endereço
    """
    bits = 0
    for f in flags:
        if f not in FLG:
            print(f"Linha {line}: flag inválida '{f}'")
            sys.exit(1)
        bits |= int(FLG[f], 2)  # Acumula bits de flags
    b1 = INSTR2['J'] + format(bits, 'x')  # Primeiro byte J+flags
    addr = raw
    if(('0x' in addr) or ('0b' in addr)):
        addr = parse_num(raw, line)  # Converte endereço
        if not 0 <= addr <= 255:
            print(f"Linha {line}: endereço fora do intervalo 0 a 255")
            sys.exit(1)
        addr =  '0x' + format(addr, '02x')
    return [b1, addr]  # Retorna J+flags e endereço

# Codifica instruções de I/O (IN/OUT)
def encode_io(kind, port, reg, line):
    """
    kind: 'IN' ou 'OUT'
    port: 'DATA' ou 'ADDR'
    reg: registrador
    """
    if port not in PRT or reg not in REG:
        print(f"Linha {line}: operador I/O inválido: {port}, {reg}")
        sys.exit(1)
    bits = PRT[kind] + PRT[port] + REG[reg]  # Concatena bits instr+port+reg
    return [PRT['FIXO'] + format(int(bits, 2), 'x')]  # Retorna FIXO+comando

# Função para montar linhas em códigos hex
def assemble(lines):
    out = []  # Lista final de instruções em hexa
    endereco = -1  # Contador de endereço
    for i, raw in enumerate(lines, 1):
        txt = raw.replace(',', ' ').strip()  # Remove vírgulas e espaços desnecessários
        parts = txt.split(';')
        parts = parts[0].strip().split()  # Divide instrução e argumentos
        if not parts or parts[0].startswith(';'):
            continue  # Ignora comentários e linhas vazias

        if ":" in parts[0]:  # Detecta label
            LABEL[parts[0]] = f"0x{endereco+1:02x}"  # Salva endereço do label
            parts = parts[1:]  # Remove label da instrução

        op = parts[0].upper()  # Converte opcode para maiúsculo

        # Instruções com registradores
        if op in INSTR1:
            out.append(encode_reg_pair(INSTR1[op], parts[1].upper(), parts[2].upper(), i))
            endereco += 1

        # Instrução com valor imediato (DATA)
        elif op == 'DATA':
            out.extend(encode_immediate(INSTR2['DATA'], parts[1].upper(), parts[2], i, signed=True))
            endereco += 2

        # Salto relativo (JMPR) com imediato zero
        elif op == 'JMPR':
            out.append(encode_immediate(INSTR2['JMPR'], parts[1].upper(), '0', i, signed=False)[0])
            endereco += 1

        # Saltos absolutos (JMP e CLF)
        elif op in ('JMP','CLF'):
            out.extend(encode_jump(INSTR2[op], parts[1] if op=='JMP' else '', i))
            if op == 'JMP':
                endereco += 2
            elif op == 'CLF':
                endereco += 1

        # Saltos condicionais JCAEZ (ex: JZ, JCE, etc.)
        elif op.startswith('J') and op not in ('JMP','JMPR','DATA'):
            out.extend(encode_conditional(op[1:], parts[1], i))
            endereco += 2

        # Instruções de I/O
        elif op in ('IN','OUT'):
            out.extend(encode_io(op, parts[1].upper(), parts[2].upper(), i))
            endereco += 1

        # MOVE RX, RY -> simulado por XOR triplo
        elif op == "MOVE":
            out.append(encode_reg_pair(INSTR1['XOR'], parts[2].upper(), parts[1].upper(), i))
            out.append(encode_reg_pair(INSTR1['XOR'], parts[1].upper(), parts[2].upper(), i))
            endereco += 2

        # CLR RX -> simulado como DATA RX, 0x00
        elif op == 'CLR':
            out.extend(encode_immediate(INSTR2['DATA'], parts[1].upper(), '0x00', i, signed=True))
            endereco += 2

        # HALT -> simulado como JMP para próxima linha
        elif op == 'HALT':
            out.extend(encode_jump(INSTR2['JMP'], f"0x{endereco+1:02x}", i))
            endereco += 2

        else:
            print(f"Linha {i}: instrução não reconhecida '{op}'")
            sys.exit(1)

    return out

# Função principal de execução
def main():
    entrada, saida = check_args()  # Valida args e obtém caminhos
    try:
        with open(entrada) as f:
            codes = assemble(f.readlines())  # Monta códigos hex
    except Exception as e:
        print(f"Erro leitura: {e}")
        sys.exit(1)
    try:
        with open(saida, 'w') as f:
            f.write('v3.0 hex words plain\n')  # Cabeçalho para Logisim
            for c in codes:
                if('0x' not in c):
                    try:
                        c = LABEL[f'{c}:']  # Resolve labels se necessário
                    except Exception:
                        print(c)
                        print(LABEL)
                        print("Erro de Label")
                f.write(f"{c}\n")  # Escreve cada código em nova linha
    except Exception as e:
        print(f"Erro escrita: {e}")  # Erro ao escrever arquivo
        sys.exit(1)
    print(f"Convertido: {len(codes)} palavras.")  # Confirmação de sucesso

# Constantes globais definidas após funções
INSTR1 = {
    'ADD':'0x8','SHR':'0x9','SHL':'0xa','NOT':'0xb',
    'AND':'0xc','OR':'0xd','XOR':'0xe','CMP':'0xf','LD':'0x0','ST':'0x1'
}
INSTR2 = {'JMP':'0x40','CLF':'0x60','DATA':'0x2','JMPR':'0x3','J':'0x5'}
FLG    = {'C':'1000','A':'0100','E':'0010','Z':'0001'}
REG    = {'R0':'00','R1':'01','R2':'10','R3':'11'}
PRT    = {'FIXO':'0x7','IN':'0','OUT':'1','DATA':'0','ADDR':'1'}
LABEL = {}

# Execução do script
if __name__ == '__main__':
    main()
