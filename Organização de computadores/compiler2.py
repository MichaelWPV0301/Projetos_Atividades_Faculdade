import sys  # Importa o módulo sys para manipular argumentos e encerrar o programa

# Função parse_num: converte string numérica em inteiro, suportando prefixos '0x' (hex) e '0b' (binário)
def parse_num(val, linha):
    try:
        # Se a string iniciar com '0x' ou '0b', usa int(val, 0) para detectar a base automaticamente
        if val.lower().startswith(("0x", "0b")):
            return int(val, 0)
        # Caso contrário, interpreta como decimal (base 10)
        return int(val, 10)
    except ValueError:
        # Se ocorrer erro na conversão, imprime mensagem com número da linha e encerra
        print(f"Linha {linha}: valor inválido: {val}")
        sys.exit(1)  # Sai do programa com código de erro

# Verifica se foram passados exatamente dois argumentos: arquivo de entrada e arquivo de saída
def main():
    if len(sys.argv) != 3:
        # Se não, exibe instrução de uso e encerra o programa
        print("Uso: python assembler.py <arquivo_entrada> <arquivo_saida>")
        sys.exit(1)
    # Atribui variáveis 'entrada' e 'saida' com base nos argumentos
    entrada, saida = sys.argv[1], sys.argv[2]

    # Dicionários de mapeamento de opcodes simples (1 byte) e complexos (múltiplos bytes)
    instrucoes1 = {
        "ADD": "0x8", "SHR": "0x9", "SHL": "0xa", "NOT": "0xb",
        "AND": "0xc", "OR":  "0xd", "XOR": "0xe", "CMP": "0xf",
        "LD":  "0x0", "ST":  "0x1"
    }
    instrucoes2 = {
        "JMP":  "0x40", "CLF":  "0x60", "DATA": "0x2",
        "JMPR": "0x3",  "J":    "0x5"
    }
    # Mapeamento de flags para saltos condicionais (JCAEZ)
    jcaez = {"C": "1000", "A": "0100", "E": "0010", "Z": "0001"}
    # Mapeamento de registradores de 2 bits
    registradores = {"R0": "00", "R1": "01", "R2": "10", "R3": "11"}
    # Mapeamento de periféricos e direções para operações de I/O
    outside = {"PRF": "0x7", "IN": "0", "OUT": "1", "DATA": "0", "ADDR": "1"}

    # Lista que armazenará cada código hexadecimal gerado
    instrucoes_hex = []

    # Tenta abrir o arquivo de entrada
    try:
        arquivo = open(entrada)
    except Exception as e:
        # Se houver erro (arquivo não encontrado ou sem permissão), exibe mensagem e encerra
        print(f"Erro ao abrir arquivo de entrada: {e}")
        sys.exit(1)

    # Processa cada linha do arquivo aberto
    with arquivo:
        for num_linha, linha in enumerate(arquivo, start=1):
            # Substitui vírgulas por espaços para facilitar o split
            linha = linha.replace(",", " ")
            # Divide linha em tokens, removendo espaços extras
            partes = linha.strip().split()
            # Ignora linhas vazias ou comentários (iniciados por ';')
            if not partes or partes[0].startswith(";"):
                continue
            # Extrai o opcode e normaliza para maiúsculas
            instr = partes[0].upper()

            # Bloco para instruções de 1 byte que usam dois registradores
            if instr in instrucoes1:
                # Garante que existam ao menos 2 registradores informados
                if len(partes) < 3:
                    print(f"Linha {num_linha}: {instr} requer 2 registradores")
                    sys.exit(1)
                # Normaliza nomes dos registradores para maiúsculas
                r1, r2 = partes[1].upper(), partes[2].upper()
                # Verifica se os registradores são válidos
                if r1 not in registradores or r2 not in registradores:
                    print(f"Linha {num_linha}: registrador inválido: {r1} ou {r2}")
                    sys.exit(1)
                # Concatena bits dos registradores e converte para inteiro
                bits = registradores[r1] + registradores[r2]
                # Gera string hex: opcode + bits convertidos
                instrucoes_hex.append(instrucoes1[instr] + hex(int(bits, 2))[2:])

            # Bloco para instrução DATA (2 bytes: opcode+reg e imediato)
            elif instr == "DATA":
                # Verifica presença de registrador e valor
                if len(partes) < 3:
                    print(f"Linha {num_linha}: DATA requer registrador e valor")
                    sys.exit(1)
                r = partes[1].upper()
                # Valida registrador
                if r not in registradores:
                    print(f"Linha {num_linha}: registrador inválido: {r}")
                    sys.exit(1)
                # Primeiro byte: opcode + código do registrador
                byte1 = instrucoes2[instr] + hex(int(registradores[r], 2))[2:]
                instrucoes_hex.append(byte1)
                # Valor imediato: parse e validação
                raw = partes[2]
                num = parse_num(raw, num_linha)
                # Se valor for decimal, checa intervalo -128 a 127
                if not raw.lower().startswith(("0x", "0b")) and not (-128 <= num <= 127):
                    print(f"Linha {num_linha}: valor fora do intervalo -128 a 127")
                    sys.exit(1)
                # Ajuste de complemento de 2 para número negativo
                if num < 0:
                    num = (num + 256) & 0xFF
                # Adiciona valor imediato em formato hex de 2 dígitos
                instrucoes_hex.append(f"0x{num:02x}")

            # Bloco para JMPR (1 byte: opcode+reg)
            elif instr == "JMPR":
                # Verifica presença de registrador
                if len(partes) < 2:
                    print(f"Linha {num_linha}: JMPR requer registrador")
                    sys.exit(1)
                r = partes[1].upper()
                # Valida registrador
                if r not in registradores:
                    print(f"Linha {num_linha}: registrador inválido: {r}")
                    sys.exit(1)
                # Gera opcode + código do registrador e adiciona
                instrucoes_hex.append(instrucoes2[instr] + hex(int(registradores[r], 2))[2:])

            # Bloco para saltos absolutos (JMP e CLF)
            elif instr in ("JMP", "CLF"):
                if instr == "CLF":
                    # CLF não requer operandos, apenas o opcode
                    instrucoes_hex.append(instrucoes2[instr])
                else:
                    # Para JMP, garante presença de endereço
                    if len(partes) < 2:
                        print(f"Linha {num_linha}: JMP requer endereço")
                        sys.exit(1)
                    # Converte endereço para inteiro
                    addr = parse_num(partes[1], num_linha)
                    # Valida intervalo 0 a 255
                    if not (0 <= addr <= 255):
                        print(f"Linha {num_linha}: endereço fora do intervalo 0 a 255")
                        sys.exit(1)
                    # Adiciona opcode e byte de endereço
                    instrucoes_hex.append(instrucoes2[instr])
                    instrucoes_hex.append(f"0x{addr:02x}")

            # Bloco para saltos condicionais JCAEZ
            elif instr.startswith("J") and instr not in ("JMP", "JMPR", "DATA"):
                # Garante presença de endereço
                if len(partes) < 2:
                    print(f"Linha {num_linha}: {instr} requer endereço")
                    sys.exit(1)
                # Extrai flags após 'J'
                flags = instr[1:]
                bits = 0
                # Converte cada flag em bit
                for f in flags:
                    if f not in jcaez:
                        print(f"Linha {num_linha}: flag inválida: {f}")
                        sys.exit(1)
                    bits |= int(jcaez[f], 2)
                # Primeiro byte: opcode J + flags
                instrucoes_hex.append(instrucoes2["J"] + hex(bits)[2:])
                # Converte e valida endereço
                addr = parse_num(partes[1], num_linha)
                if not (0 <= addr <= 255):
                    print(f"Linha {num_linha}: endereço fora do intervalo 0 a 255")
                    sys.exit(1)
                # Adiciona byte de endereço
                instrucoes_hex.append(f"0x{addr:02x}")

            # Bloco para operações de I/O (IN/OUT)
            elif instr in ("IN", "OUT"):
                # Verifica presença de porta e registrador
                if len(partes) < 3:
                    print(f"Linha {num_linha}: {instr} requer tipo de porta e registrador")
                    sys.exit(1)
                port = partes[1].upper()
                r = partes[2].upper()
                # Valida porta (DATA/ADDR) e registrador
                if port not in ("DATA", "ADDR") or r not in registradores:
                    print(f"Linha {num_linha}: operador I/O inválido: {port}, {r}")
                    sys.exit(1)
                # Concatena bits: PRF + porta + registrador
                cmds = outside[instr] + outside[port] + registradores[r]
                # Adiciona código completo de I/O
                instrucoes_hex.append(outside["PRF"] + hex(int(cmds, 2))[2:])

            # Caso instrução não reconhecida
            else:
                print(f"Linha {num_linha}: instrução não reconhecida: {instr}")
                sys.exit(1)

    # Escrita do arquivo de saída no formato exigido pelo Logisim
    try:
        with open(saida, "w") as f:
            # Cabeçalho obrigatório para arquivos hex words plain
            f.write("v3.0 hex words plain\n")
            # Escreve cada código em nova linha
            for c in instrucoes_hex:
                f.write(f"{c}\n")
    except Exception as e:
        # Em caso de erro de escrita, exibe mensagem e encerra
        print(f"Erro ao escrever arquivo de saída: {e}")
        sys.exit(1)

    # Impressão final informando sucesso e quantidade de instruções geradas
    print(f"Conversão concluída com sucesso. {len(instrucoes_hex)} palavras geradas.")

# Executa função main quando script for rodado diretamente
if __name__ == '__main__':
    main()
