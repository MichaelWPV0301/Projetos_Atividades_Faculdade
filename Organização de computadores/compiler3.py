import sys  # Importa o módulo sys para leitura de argumentos da linha de comando

# Coleta os nomes dos arquivos de entrada e saída passados via linha de comando
entrada = sys.argv[1]
saida = sys.argv[2]

# Tabelas de instruções, registradores, periféricos e condições
opcodes_1byte = {
    "ADD": "0x8", "SHR": "0x9", "SHL": "0xa", "NOT": "0xb",
    "AND": "0xc", "OR": "0xd", "XOR": "0xe", "CMP": "0xf",
    "LD": "0x0", "ST": "0x1"
}

opcodes_2byte = {
    "JMP": "0x40", "CLF": "0x60", "DATA": "0x2", "JMPR": "0x3", "J": "0x5"
}

perifericos = {
    "BASE": "0x7", "IN": "0", "OUT": "1", "DATA": "0", "ADDR": "1"
}

regs = {
    "R0": "00", "R1": "01", "R2": "10", "R3": "11"
}

condicoes = {
    "C": "1000", "A": "0100", "E": "0010", "Z": "0001"
}

# Lista que armazenará os códigos de máquina gerados
saida_hex = []

# Função auxiliar para converter valores para hexadecimal com verificação de intervalo
def parse_valor(valor_str, intervalo=(-128, 255)):
    try:
        valor = int(valor_str, 0)  # Aceita formatos binários, decimais e hexadecimais
        if not (intervalo[0] <= valor <= intervalo[1]):
            raise ValueError(f"Valor fora do intervalo {intervalo}")
        if valor < 0:
            valor = (1 << 8) + valor  # Converte para complemento de dois
        return f"0x{valor:02x}"
    except ValueError as e:
        print(f"Erro: {e}")
        return None

# Função para montar instruções de 1 byte (2 registradores)
def monta_instrucao_1byte(instrucao, partes):
    rA = regs[partes[1].upper()]  # Primeiro registrador (bits mais significativos)
    rB = regs[partes[2].upper()]  # Segundo registrador (bits menos significativos)
    bin_reg = rA + rB
    return opcodes_1byte[instrucao] + hex(int(bin_reg, 2))[2:]  # Retorna código completo

# Função para montar instruções de 2 bytes

def monta_instrucao_2bytes(instrucao, partes):
    try:
        if instrucao in ["DATA", "JMPR"]:
            if len(partes) < 3:
                raise IndexError("Instrução incompleta: esperados 3 argumentos")
            rX = regs[partes[1].upper()]  # Registrador
            byte1 = opcodes_2byte[instrucao] + hex(int(rX, 2))[2:]  # Opcode + registrador
            byte2 = parse_valor(partes[2], (-128, 127))  # Valor imediato com sinal
        elif instrucao in ["JMP", "CLF"]:
            if len(partes) < 2:
                raise IndexError("Instrução incompleta: esperados 2 argumentos")
            byte1 = opcodes_2byte[instrucao]  # Opcode
            byte2 = parse_valor(partes[1], (0, 255))  # Endereço sem sinal
        elif instrucao.startswith("J"):
            if len(partes) < 2:
                raise IndexError("Instrução de salto condicional incompleta")
            flags = instrucao[1:].upper()  # Ex: JZ, JAE, etc
            soma = sum(int(condicoes[c], 2) for c in flags)  # Soma os bits das condições
            byte1 = opcodes_2byte["J"] + hex(soma)[2:]  # Opcode + bits de condição
            byte2 = parse_valor(partes[1], (0, 255))  # Endereço
        else:
            return None, None
        return byte1, byte2
    except (IndexError, KeyError, ValueError) as e:
        print(f"Erro ao montar instrução '{' '.join(partes)}': {e}")
        return None, None

# Leitura do arquivo de entrada linha a linha
with open(entrada) as arquivo:
    for linha in arquivo:
        linha = linha.replace(",", " ").strip()  # Remove vírgulas e espaços
        if not linha or linha.startswith(";"):  # Ignora linhas vazias ou comentários
            continue

        partes = linha.split()  # Divide a linha em partes (instrução + operandos)
        instrucao = partes[0].upper()  # Converte a instrução para maiúscula

        # Instrução de 1 byte (usa dois registradores)
        if instrucao in opcodes_1byte:
            if len(partes) >= 3:
                codigo = monta_instrucao_1byte(instrucao, partes)
                saida_hex.append(codigo)
            else:
                print(f"Erro: instrução incompleta '{linha}'")

        # Instrução de 2 bytes (jump, immediate, etc)
        elif instrucao in opcodes_2byte or instrucao.startswith("J"):
            byte1, byte2 = monta_instrucao_2bytes(instrucao, partes)
            if byte1 and byte2:
                saida_hex.extend([byte1, byte2])

        # Instrução de periférico (IN/OUT)
        elif instrucao in perifericos:
            if len(partes) >= 3:
                codigo = perifericos["BASE"]  # Opcode base para periféricos
                bits = (
                    perifericos[partes[0].upper()] +  # IN ou OUT
                    perifericos[partes[1].upper()] +  # DATA ou ADDR
                    regs[partes[2].upper()]           # Registrador
                )
                cod_final = hex(int(bits, 2))
                codigo += cod_final[2:]
                saida_hex.append(codigo)
            else:
                print(f"Erro: instrução de periférico incompleta '{linha}'")

        else:
            print(f"Erro: instrução desconhecida '{instrucao}'")

# Escreve os códigos de máquina no arquivo de saída
with open(saida, "w") as f:
    f.write("v3.0 hex words plain\n")  # Cabeçalho para Logisim Evolution
    for linha in saida_hex:
        f.write(f"{linha}\n")  # Escreve cada instrução convertida