import sys

# Coleta os nomes dos arquivos de entrada e saída passados via linha de comando
entrada = sys.argv[1]  # Primeiro argumento: arquivo .asm com o código de montagem
saida = sys.argv[2]    # Segundo argumento: arquivo .txt que conterá o código hexadecimal

# Tabelas de conversão de instruções e operandos para seus equivalentes em código de máquina
opcodes_1byte = {  # Instruções que ocupam um byte e usam dois registradores
    "ADD": "0x8", "SHR": "0x9", "SHL": "0xa", "NOT": "0xb",
    "AND": "0xc", "OR": "0xd", "XOR": "0xe", "CMP": "0xf",
    "LD": "0x0", "ST": "0x1"
}

opcodes_2byte = {  # Instruções que ocupam dois bytes e podem usar registrador ou endereço
    "JMP": "0x40", "CLF": "0x60", "DATA": "0x2", "JMPR": "0x3", "J": "0x5"
}

perifericos = {  # Mapeamento de comandos para I/O (entrada/saída)
    "BASE": "0x7", "IN": "0", "OUT": "1", "DATA": "0", "ADDR": "1"
}

regs = {  # Mapeamento dos registradores para seus códigos binários
    "R0": "00", "R1": "01", "R2": "10", "R3": "11"
}

condicoes = {  # Códigos das condições para instruções JCAEZ
    "C": "1000", "A": "0100", "E": "0010", "Z": "0001"
}

saida_hex = []  # Lista que vai armazenar todas as instruções convertidas para hexadecimal

# Abre o arquivo de entrada e lê linha por linha
with open(entrada) as arquivo:
    for linha in arquivo:
        linha = linha.replace(",", " ").strip()  # Substitui vírgulas por espaço e remove espaços excedentes
        if not linha or linha.startswith(";"):  # Ignora linhas em branco ou comentários
            continue

        partes = linha.split()  # Divide a linha em partes (instrução e operandos)
        instrucao = partes[0].upper()  # Transforma a instrução em maiúsculo por segurança

        # CASO 1: Instruções com dois registradores (1 byte)
        if instrucao in opcodes_1byte:
            rA = regs[partes[1].upper()]  # Primeiro registrador
            rB = regs[partes[2].upper()]  # Segundo registrador
            bin_reg = rA + rB  # Junta os dois códigos binários dos registradores
            valor = hex(int(bin_reg, 2))  # Converte para hexadecimal
            codigo = opcodes_1byte[instrucao] + valor[2:]  # Junta com o opcode da instrução

        # CASO 2: Instruções de dois bytes
        elif instrucao in opcodes_2byte or instrucao.startswith("J"):

            # Subcaso: DATA e JMPR usam registrador + valor
            if instrucao == "DATA" or instrucao == "JMPR":
                rX = regs[partes[1].upper()]  # Registrador usado
                codigo = opcodes_2byte[instrucao] + hex(int(rX, 2))[2:]  # Opcode + registrador
                saida_hex.append(codigo)  # Armazena primeiro byte

                valor = partes[2]  # Segundo operando (valor ou endereço)
                try:
                    if "x" in valor or "b" in valor:
                        valor = int(valor, 0)  # Interpreta como binário ou hexadecimal
                    else:
                        valor = int(valor)  # Interpreta como decimal
                    if valor < -128 or valor > 127:
                        print("Erro: valor fora do intervalo permitido (-128 a 127)")
                    if valor < 0:
                        valor = (1 << 8) + valor  # Faz complemento de 2 para valores negativos
                    valor = f"0x{valor:02x}"  # Converte para string hexadecimal com 2 dígitos
                except ValueError:
                    print("Erro: valor inválido no segundo byte de DATA/JMPR")

            # Subcaso: JMP e CLF usam apenas valor
            elif instrucao == "JMP" or instrucao == "CLF":
                codigo = opcodes_2byte[instrucao]  # Código da instrução
                saida_hex.append(codigo)  # Armazena primeiro byte

                try:
                    valor = int(partes[1], 0)  # Lê o valor como int (decimal, binário ou hexa)
                    if valor < 0 or valor > 255:
                        print("Erro: endereço inválido (0 a 255)")
                    valor = hex(valor)  # Converte de volta para hexadecimal
                except ValueError:
                    print("Erro: valor inválido no JMP/CLF")

            # Subcaso: Instruções do tipo J<condições>
            elif instrucao.startswith("J"):
                flags = instrucao[1:].upper()  # Extrai as letras CAEZ
                soma = sum(int(condicoes[c], 2) for c in flags)  # Soma os bits das condições
                cond_hex = hex(soma)  # Converte para hexadecimal
                codigo = opcodes_2byte["J"] + cond_hex[2:]  # Monta o primeiro byte
                saida_hex.append(codigo)

                try:
                    valor = int(partes[1], 0)  # Segundo byte: endereço
                    if valor < 0 or valor > 255:
                        print("Erro: endereço inválido (0 a 255)")
                    valor = f"0x{valor:02x}"  # Converte para hexadecimal com 2 dígitos
                except ValueError:
                    print("Erro: valor inválido no segundo byte do J<cond>")

        # CASO 3: Instruções de periférico (como IN/OUT)
        elif instrucao in perifericos:
            codigo = perifericos["BASE"]  # Começa com o código fixo "BASE" (0x7)
            bits = (
                perifericos[partes[0].upper()] +  # Comando (IN/OUT)
                perifericos[partes[1].upper()] +  # Tipo (DATA/ADDR)
                regs[partes[2].upper()]           # Registrador
            )
            cod_final = hex(int(bits, 2))  # Converte os 6 bits para hexadecimal
            codigo += cod_final[2:]  # Junta com o BASE

        else:
            print(f"Erro: instrução desconhecida '{instrucao}'")
            continue  # Pula essa linha se houver erro

        # Adiciona os bytes montados à lista final
        saida_hex.append(codigo)
        if 'valor' in locals():
            saida_hex.append(valor)
            del valor  # Limpa variável para evitar conflitos

# Escreve os valores hexadecimais no arquivo de saída
with open(saida, "w") as f:
    f.write("v3.0 hex words plain\n")  # Cabeçalho necessário para Logisim Evolution
    for linha in saida_hex:
        f.write(f"{linha}\n")  # Cada instrução em uma nova linha