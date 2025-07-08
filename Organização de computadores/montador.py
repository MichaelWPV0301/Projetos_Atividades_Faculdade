# Aluno: Abel Severo Rocha Matricula: 22401917

import sys

# Dict com o valor em hexadecimal das instruções
opcodes = {
    "LD":  0x00, "ST":  0x10, "DATA": 0x20, "JMPR": 0x30,
    "JMP": 0x40, "JCAEZ": 0x50, "CLF": 0x60, "IN": 0x70,
    "OUT": 0x78, "ADD": 0x80, "SHR": 0x90, "SHL": 0xA0,
    "NOT": 0xB0, "AND": 0xC0, "OR":  0xD0, "XOR": 0xE0, "CMP": 0xF0
}

# Dict com o valor em hexadecimal dos registradores
registradores = {
    "R0": 0x00, "R1": 0x01, "R2": 0x02, "R3": 0x03,
}

# Dict com o valor em hexadecimal das flags do JCAEZ
flags = {"C": 0x08, "A": 0x04, "E": 0x02, "Z": 0x01}

# Dict com os tipos para as instr IN/OUT
tipo = {"DATA": 0x00, "ADDR": 0x04}

# Instruções de salto condicional baseadas em flags
flag_instrs = {'JC', 'JA', 'JE', 'JZ', 'JCA', 'JCE', 'JCZ', 'JCAE', 'JCAZ', 'JCEZ', 'JAE', 'JAZ', 'JAEZ', 'JEZ'}

# Função para determinar o tamanho em bytes de uma instrução
def get_instruction_size(instr_name, args):
    if instr_name in {"LD", "ST", "ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP", "JMPR", "CLF"}:
        return 1
    elif instr_name in {"DATA", "JMP", "JCAEZ", "IN", "OUT"} or instr_name in flag_instrs:
        return 2
    else:
        raise ValueError(f"Instrução desconhecida para cálculo de tamanho: {instr_name}")

# Função de leitura: trata espaços, comentarios, labels e pseudo-instruções
# Retorna uma lista de instruções expandidas e um dicionário de labels
def preprocess_program(arquivo_entrada):
    program_lines = []
    with open(arquivo_entrada, 'r') as f:
        for line_num, line in enumerate(f, 1):
            # Remove comentários e espaços extras, converte para maiúsculas
            cleaned_line = line.split(';')[0].strip().upper()
            if not cleaned_line:
                continue

            program_lines.append((cleaned_line, line_num)) # Guarda a linha original e o número da linha para erros

    expanded_program = [] # Lista de instruções após expansão de pseudo-instruções
    labels = {}           # Dicionário para armazenar labels e seus endereços

    current_address = 0 # Contador de endereço para a primeira passagem

    # Primeira Passagem: Coletar labels e expandir pseudo-instruções
    for cleaned_line, line_num in program_lines:
        tokens = cleaned_line.replace(',', ' ').split()
        if not tokens:
            continue

        first_token = tokens[0]

        # Verifica se é um label
        if first_token.endswith(':'):
            label_name = first_token[:-1]
            if label_name in labels:
                raise ValueError(f"Erro na linha {line_num}: Label '{label_name}' já definido.")
            labels[label_name] = current_address
            tokens = tokens[1:] # Remove o label da lista de tokens
            if not tokens: # Se a linha era só um label, continua para a próxima
                continue

        instr = tokens[0]
        args = tokens[1:]

        # Expansão de pseudo-instruções
        if instr == "CLF": # CLF R<n> -> XOR R<n>, R<n>
            if len(args) != 1 or args[0] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de CLF. Esperado 'CLF R<n>'.")
            reg = args[0]
            expanded_program.append(['XOR', reg, reg])
            current_address += get_instruction_size('XOR', [reg, reg])
        elif instr == "MOVE": # MOVE R<n>, R<m> -> XOR R<m>, R<m>; ADD R<m>, R<n>
            if len(args) != 2 or args[0] not in registradores or args[1] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de MOVE. Esperado 'MOVE R<n>, R<m>'.")
            reg_src = args[0]
            reg_dest = args[1]
            expanded_program.append(['XOR', reg_dest, reg_dest])
            current_address += get_instruction_size('XOR', [reg_dest, reg_dest])
            expanded_program.append(['ADD', reg_dest, reg_src])
            current_address += get_instruction_size('ADD', [reg_dest, reg_src])
        elif instr == "HALT": # HALT -> JMP <current_address>
            # O endereço do JMP será o endereço da própria instrução JMP
            # Usamos um placeholder que será substituído na segunda passagem
            expanded_program.append(['JMP', 'HALT_PLACEHOLDER'])
            current_address += get_instruction_size('JMP', ['HALT_PLACEHOLDER'])
        else: # Instruções normais
            expanded_program.append([instr] + args)
            current_address += get_instruction_size(instr, args)

    # Na primeira passagem, o HALT_PLACEHOLDER é substituído pelo endereço real do JMP
    # que é o current_address do momento em que o HALT foi expandido.
    for i, inst_args in enumerate(expanded_program):
        if inst_args[0] == 'JMP' and inst_args[1] == 'HALT_PLACEHOLDER':
            # Encontra o endereço desta instrução JMP
            addr_of_jmp = 0
            for j in range(i):
                addr_of_jmp += get_instruction_size(expanded_program[j][0], expanded_program[j][1:])
            expanded_program[i][1] = str(addr_of_jmp) # Converte para string para manter o tipo consistente

    return expanded_program, labels

# Função de escrita: escreve o txt conforme o modelo do logisim
def escrever_saida(arquivo_saida, saida):
    with open(arquivo_saida, 'w') as f:
        f.write('v3.0 hex words plain\n' + '\n'.join(saida) + '\n')

# Converte os valores(hexa, bin ou decimal) para hexadecimal em complemento de 2 e verifica se respeita o intervalo
def parse_val(val_str, labels, current_address, line_num):
    # Se o valor for um label, resolve para o endereço
    if val_str in labels:
        return labels[val_str]

    # Caso contrário, tenta parsear como número
    val_str = val_str.upper()

    try:
        if val_str.startswith('0X'):
            num = int(val_str, 16)
        elif val_str.startswith('0B'):
            num = int(val_str, 2)
        else:
            num = int(val_str.lstrip('0') or '0')
    except ValueError:
        raise ValueError(f"Erro na linha {line_num}: Valor ou label inválido '{val_str}'.")

    if not -128 <= num <= 255:
        raise ValueError(f"Erro na linha {line_num}: Valor fora do intervalo suportado (-128 a 255): {num}")

    return num & 0xFF # Retorna o valor em 8 bits

# Função principal que gera uma lista com os hexas correspondentes de cada instr
def montador(expanded_program, labels):
    saida = []
    current_address = 0 # Contador de endereço para a segunda passagem

    for line_num, instr_args in enumerate(expanded_program, 1): # Usar line_num para mensagens de erro mais precisas
        instr = instr_args[0]
        args = instr_args[1:]

        op = opcodes.get(instr if instr not in flag_instrs else "JCAEZ")
        if op is None:
            raise ValueError(f"Erro na linha {line_num}: Instrução inválida '{instr}'.")

        if instr in {"LD", "ST", "ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP"}: # Instr + RA + RB
            if len(args) != 2 or args[0] not in registradores or args[1] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de {instr}. Esperado '{instr} RA, RB'.")
            ra = registradores[args[0]]
            rb = registradores[args[1]]
            saida.append(f"{(op + (ra << 2) + rb):02X}")
            current_address += 1

        elif instr == "DATA": # Instr + RA + VAL
            if len(args) != 2 or args[0] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de DATA. Esperado 'DATA RA, VAL'.")
            reg = registradores[args[0]]
            val = parse_val(args[1], labels, current_address, line_num)
            saida.append(f"{(op + reg):02X}")
            saida.append(f"{val:02X}")
            current_address += 2

        elif instr == "JMP": # Instr + Val (ou Label)
            if len(args) != 1:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de JMP. Esperado 'JMP VAL' ou 'JMP LABEL'.")
            val = parse_val(args[0], labels, current_address, line_num)
            saida.append(f"{op:02X}")
            saida.append(f"{val:02X}")
            current_address += 2

        elif instr == "JMPR": # Instr + RB
            if len(args) != 1 or args[0] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de JMPR. Esperado 'JMPR RB'.")
            rb = registradores[args[0]]
            saida.append(f"{(op + rb):02X}")
            current_address += 1

        elif instr == "CLF": # CLF original (limpa flags)
            # A pseudo-instrução CLF R<n> é tratada na primeira passagem
            # Esta é para a instrução CLF sem argumentos (limpar flags)
            if len(args) != 0:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de CLF. Esperado 'CLF' (para limpar flags).")
            saida.append(f"{op:02X}")
            current_address += 1

        elif instr in flag_instrs: # Instr + Flags + Val (ou Label)
            if len(args) != 1:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de {instr}. Esperado '{instr} VAL' ou '{instr} LABEL'.")
            flag_val = sum(flags[f] for f in instr[1:])
            val = parse_val(args[0], labels, current_address, line_num)
            saida.append(f"{(op + flag_val):02X}")
            saida.append(f"{val:02X}")
            current_address += 2

        elif instr in {"IN", "OUT"}: # Instr + Tipo + Reg
            if len(args) != 2 or args[0] not in tipo or args[1] not in registradores:
                raise ValueError(f"Erro na linha {line_num}: Uso inválido de {instr}. Esperado '{instr} TIPO, REG'.")
            tipo_val = tipo[args[0]]
            reg = registradores[args[1]]
            saida.append(f"{(op + tipo_val + reg):02X}")
            current_address += 2
        else:
            raise ValueError(f"Erro na linha {line_num}: Instrução inválida ou não implementada '{instr}'.")

    return saida

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python3 montador.py entrada.asm saida.txt")
    
    entrada_arquivo, saida_arquivo = sys.argv[1], sys.argv[2]

    try:
        # Primeira passagem: coletar labels e expandir pseudo-instruções
        expanded_program, labels = preprocess_program(entrada_arquivo)

        # Segunda passagem: montar o código hexadecimal
        hexa = montador(expanded_program, labels)

        # Escrever a saída no arquivo
        escrever_saida(saida_arquivo, hexa)
        print(f"Montagem concluída com sucesso. Saída gravada em '{saida_arquivo}'.")

    except ValueError as e:
        print(f"Erro de montagem: {e}")
        sys.exit(1) # Saída com erro
    except FileNotFoundError:
        print(f"Erro: Arquivo de entrada '{entrada_arquivo}' não encontrado.")
        sys.exit(1) # Saída com erro
    except Exception as e:
        print(f"Ocorreu um erro inesperado: {e}")
        sys.exit(1) # Saída com erro