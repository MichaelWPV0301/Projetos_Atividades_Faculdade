# Nome: Michael Willian Pereira Vieira; Matricula: 22400829;

import sys

# Captura os nomes dos arquivos passados por linha de comando:
# sys.argv[1] é o nome do arquivo de entrada (.asm)
# sys.argv[2] é o nome do arquivo de saída (.txt com código hexa)
entrada = sys.argv[1]
saida = sys.argv[2]

# Dicionários com instruções e seus respectivos opcodes em hexadecimal
# instrucoes1: instruções que usam dois registradores (1 byte)
instrucoes1 = {
    "ADD": "0x8", "SHR": "0x9", "SHL": "0xa", "NOT": "0xb",
    "AND": "0xc", "OR": "0xd", "XOR": "0xe", "CMP": "0xf",
    "LD": "0x0", "ST": "0x1", "JMPR":"0x3", "DATA": "0x2"
}

# instrucoes2: instruções que não usam os registradores
instrucoes2 = {
    "JMP": "0x40", "CLF": "0x60", "J": "0x5"
}

# outside: instruções de periféricos, convertidas para bits
outside = {"BASE": "0x7", "IN": "0", "OUT": "1", "DATA": "0", "ADDR": "1"}

# registradores: representação binária dos registradores
registradores = {"R0": "00", "R1": "01", "R2": "10", "R3": "11"}

# jcaez: representação binária das condições de salto (JCAEZ)
jcaez = {"C": "1000", "A": "0100", "E": "0010", "Z": "0001"}

# Lista que conterá as instruções convertidas para hexadecimal
instrucoes_hex = []

# Dicionário para armazenar labels (rótulos) e seus endereços
label = {}


def converte_hexadecimal(valor):
    # Se for um número inteiro, converte para string
    if isinstance(valor, int):
        valor = str(valor)

    try:   
        # Converte para decimal
        decimal = int(valor, 0)
    except ValueError:
        raise ValueError("Formato inválido. Use binário (0b...), hexadecimal (0x...), ou decimal.")
    
    # Converte para hexadecimal (sem o prefixo '0x') e retorna em minúsculas
    hexadecimal = f"{decimal:02x}"
    return hexadecimal

def limpa_linhas(linha):
    linha = linha.replace(",", " ")  # Substitui vírgulas por espaços para facilitar o split
    partes = linha.strip().split(';')  # Remove os comentário
    partes = partes[0].strip().split()  # Separa os elementos da instrução
    return partes

def verifica_label(partes):
    global endereco, label
    if ":" in partes[0]:
        label[partes[0]] = f"0x{endereco+1:02x}"  # Salva o endereço do label
        partes = partes[1:]  # Remove o label da linh
    return partes

def converte_registradores(ra, rb):
    regs = registradores[ra] + registradores[rb]
    hexaregs = converte_hexadecimal(regs)
    return hexaregs


def instru_com_regs(instrucao, ra, rb):
    hexaregs = converte_registradores(ra, rb)
    hexainstru = instrucoes1[instrucao] + hexaregs
    return hexainstru

def complemento_de_dois(valor):
    # if '-' in str(valor):  Se valor negativo, aplica complemento de dois
    if( "x" not in valor and "b" not in valor):
        valor = int(valor)
    else:
        valor = int(valor, 0)
    valor = f"{valor:09b}"
    valor = "".join("1" if b == "0" else "0" for b in valor if b != '-')
    valor = int(valor, 2) + 1
    return  f"0x{valor:02x}"


def verifica_intervalo_data(hexa):
    try:
        if "x" not in hexa and "b" not in hexa:
            hexa = int(hexa)  # Trata decimal puro
            if hexa > 127 or hexa < -128:
                return 0
        else:
            hexa = int(hexa, 0)  # Converte bin/hex str -> int
            if(hexa>255):
                return 0
        return 1
    except ValueError:
        return 0
    
def instru_jcaez(instrucao):
    letras = list(instrucao[1:].upper())  # Pega os flags (CAEZ)
    letrasBin = sum(int(jcaez[letra], 2) for letra in letras)  # Soma os bits
    hexaLetras = hex(letrasBin)  # Converte para hexadecimal
    instruhexa = instrucoes2[instrucao[0]] + hexaLetras[2:]  # Monta primeiro byte
    return instruhexa



def instru_sem_regs(instrucao):
    if instrucao == "JMP" or instrucao == "CLF":
        hexinstru = instrucoes2[instrucao]  # Opcode fixo da instrução
    elif instrucao[0] == "J":
        hexinstru = instru_jcaez(instrucao)
    return hexinstru

def instru_outside(lista):
    hexa = outside["BASE"]  # Começa com BASE = 0x7
    comandos = outside[partes[0].upper()] + outside[partes[1].upper()] + registradores[partes[2].upper()]
    comando = int(comandos, 2)  # Monta comando binário total
    comando = hex(comando)
    hexa += comando[2:]  # Junta BASE + bits do comando
    return hexa

def pseudo_instru(instrucao, ra=0, rb=0):
    return "por fazer"

# Abre o arquivo .asm de entrada
with open(entrada) as arquivo:
    endereco = -1  # Endereço atual (contador de instruções)

    for linha in arquivo:
        if not linha:
            continue  # Ignora linhas vazias

        linha = linha.replace(",", " ")  # Substitui vírgulas por espaços para facilitar o split
        partes = linha.strip().split(';')  # Remove os comentários
        partes = partes[0].strip().split()  # Separa os elementos da instrução

        if partes:  # Se houver instrução na linha

            # Verifica se há label no início da linha (ex: INICIO: ...)
            if ":" in partes[0]:
                label[partes[0]] = f"0x{endereco+1:02x}"  # Salva o endereço do label
                partes = partes[1:]  # Remove o label da linha

            instrucao = partes[0].upper()  # Converte a instrução para maiúsculo

            # INSTRUÇÕES COM DOIS REGISTRADORES (1 BYTE)
            if instrucao in instrucoes1:
                reg1 = partes[1].upper()
                reg2 = partes[2].upper()
                regs = registradores[reg1] + registradores[reg2]  # Concatena os bits RA + RB
                inteiro = int(regs, 2)  # Converte binário para inteiro
                hexaregs = hex(inteiro)  # Converte inteiro para hexadecimal
                hexa = instrucoes1[instrucao] + hexaregs[2:]  # Monta instrução final em hexa

            # INSTRUÇÕES COM DOIS BYTES (JMPR, DATA, JMP, CLF, JCAEZ)
            elif instrucao in instrucoes2 or instrucao[0] == "J":

                # DATA e JMPR possuem registrador + valor imediato
                if instrucao == "DATA" or instrucao == "JMPR":
                    reg = registradores[partes[1].upper()]  # Pega registrador RX
                    inteiro = int(reg, 2)
                    hexareg = hex(inteiro)
                    hexa = instrucoes2[instrucao] + hexareg[2:]  # Primeiro byte (op + reg)

                    if instrucao == "DATA":  # Para DATA, precisa armazenar o segundo byte (ADDR)
                        instrucoes_hex.append(hexa)
                        endereco += 1
                        hexa = partes[2]  # Segundo operando (ADDR)

                        try:
                            if "x" not in hexa and "b" not in hexa:
                                hexa = int(hexa)  # Trata decimal puro
                                if hexa > 127 or hexa < -128:
                                    print("Erro: valor fora do intervalo permitido (-128 a 127)")
                                    break
                            else:
                                hexa = int(hexa, 0)  # Converte bin/hex str -> int
                        except ValueError:
                            print("Erro: valor inválido, não é um número inteiro")
                            break

                        if '-' in str(hexa):  # Se valor negativo, aplica complemento de dois
                            hexa = f"{hexa:09b}"
                            hexa = "".join("1" if b == "0" else "0" for b in hexa if b != '-')
                            hexa = int(hexa, 2) + 1

                        hexa = f"0x{hexa:02x}"  # Formata o valor final

                # JMP e CLF usam opcode fixo + segundo byte com o endereço
                elif instrucao == "JMP" or instrucao == "CLF":
                    hexa = instrucoes2[instrucao]  # Opcode fixo da instrução
                    if instrucao == "JMP":
                        instrucoes_hex.append(hexa)
                        endereco += 1
                        hexa = partes[1]  # Segundo byte: endereço
                        try:
                            hexa = int(hexa, 0)
                            if hexa < 0 or hexa > 255:
                                print("Erro: valor fora do intervalo permitido (0 a 255)")
                                break
                            hexa = hex(hexa)
                        except:
                            instrucoes_hex.append(hexa)
                            endereco += 1
                            continue

                # JCAEZ: instrução condicional com combinação de flags + endereço
                elif instrucao[0] == "J":
                    letras = list(instrucao[1:].upper())  # Pega os flags (CAEZ)
                    letrasBin = sum(int(jcaez[letra], 2) for letra in letras)  # Soma os bits
                    hexaLetras = hex(letrasBin)  # Converte para hexadecimal
                    hexa = instrucoes2[instrucao[0]] + hexaLetras[2:]  # Monta primeiro byte

                    instrucoes_hex.append(hexa)
                    endereco += 1
                    hexa = partes[1]  # Segundo byte (endereço de salto)
                    try:
                        hexa = int(hexa, 0)
                        if hexa > 255 or hexa < 0:
                            print("Erro: valor fora do intervalo permitido (0 a 255)")
                            break
                        hexa = f"0x{hexa:02x}"
                    except:
                        instrucoes_hex.append(hexa)
                        endereco += 1
                        continue

            # INSTRUÇÕES DE PERIFÉRICOS: IN/OUT/DATA/ADDR
            elif instrucao in outside:
                hexa = outside["BASE"]  # Começa com BASE = 0x7
                comandos = outside[partes[0].upper()] + outside[partes[1].upper()] + registradores[partes[2].upper()]
                comando = int(comandos, 2)  # Monta comando binário total
                comando = hex(comando)
                hexa += comando[2:]  # Junta BASE + bits do comando

            # INSTRUÇÕES ESPECIAIS (NÃO ESTÃO NOS SETS)/
            else:
                # MOVE RX, RY: troca de valores via XOR Duplo
                if instrucao == 'MOVE':
                    reg1 = partes[1].upper()
                    reg2 = partes[2].upper()

                    regs = registradores[reg2] + registradores[reg1]  # XOR RY, RX
                    inteiro = int(regs, 2)
                    hexaregs = hex(inteiro)
                    hexa = instrucoes1['XOR'] + hexaregs[2:]
                    instrucoes_hex.append(hexa)
                    endereco += 1

                    regs = registradores[reg1] + registradores[reg2]  # XOR RX, RY
                    inteiro = int(regs, 2)
                    hexaregs = hex(inteiro)
                    hexa = instrucoes1['XOR'] + hexaregs[2:]
                    instrucoes_hex.append(hexa)
                    endereco += 1
                    continue

                # CLR RX: limpa registrador (gera 0x2X)
                elif instrucao == 'CLR':
                    reg = registradores[partes[1].upper()]
                    inteiro = int(reg, 2)
                    hexareg = hex(inteiro)
                    hexa = "0x2" + hexareg[2:]
                    instrucoes_hex.append(hexa)
                    endereco += 1
                    hexa = '0x00'

                # HALT: simula parada como JMP para próxima linha
                elif instrucao == 'HALT':
                    hexa = instrucoes2['JMP']
                    instrucoes_hex.append(hexa)
                    endereco += 1
                    if endereco <= 255:
                        instrucoes_hex.append(f"0x{endereco:02x}")
                        endereco += 1
                        continue
                    else:
                        print("Erro: valor fora do intervalo permitido (0 a 255)")
                        break
            instrucoes_hex.append(hexa)  # Adiciona último byte da instrução
            endereco += 1

# Gera arquivo de saída no formato compatível com o Logisim
print(instrucoes_hex)
with open(saida, "w") as f:
    f.write("v3.0 hex words plain\n")  # Cabeçalho exigido pelo Logisim
    for hexa in instrucoes_hex:
        if '0x' not in hexa:  # Se for label, resolve o endereço
            hexa = label[f'{hexa}:']
        f.write(f"{hexa}\n")
