# Nome: Michael Willian Pereira Vieira; Matricula: 22400829;

import sys

# Captura os nomes dos arquivos passados por linha de comando:
# sys.argv[1] é o nome do arquivo de entrada (.asm)
# sys.argv[2] é o nome do arquivo de saída (.txt com código hexa)
entrada = sys.argv[1]
saida = sys.argv[2]

# Dicionários com instruções e seus respectivos opcodes em hexadecimal ---------------------
# instrucoesComRegs: instruções que usam dois registradores ou 1 registrador(DATA e JMPR)
instrucoesComRegs = {
    "ADD": "0x8", "SHR": "0x9", "SHL": "0xa", "NOT": "0xb",
    "AND": "0xc", "OR": "0xd", "XOR": "0xe", "CMP": "0xf",
    "LD": "0x0", "ST": "0x1", "JMPR":"0x3", "DATA": "0x2"
}

# instrucoesSemRegs: instruções que não usam os registradores
instrucoesSemRegs = {
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
    """
    Converte um valor binário (0b...), hexadecimal (0x...) ou decimal para 
    uma representação hexadecimal com exatamente dois dígitos, em letras minúsculas.
    
    Parâmetros:
    ----------
        valor (int ou str): O valor a ser convertido. Pode ser um número inteiro
                            ou uma string representando um número binário, hexadecimal ou decimal.
    
    Retorna:
    ----------
        str: Representação hexadecimal com dois dígitos, sem prefixo '0x'.
    
    Exceções:
    ----------
        ValueError: Se o valor não puder ser convertido para um número inteiro válido.
    """

    if isinstance(valor, int):
        valor = str(valor)

    try:
        if "x" in valor or "b" in valor:
            decimal = int(valor, 0)
        else:
            decimal = int(valor)
    except ValueError:
        raise ValueError("Formato inválido. Use binário (0b...), hexadecimal (0x...), ou decimal.")
    
    hexadecimal = f"{decimal:02x}"

    return hexadecimal

def limpa_linhas(linha):
    """
    Limpa e formata uma linha de código de montagem (assembly), removendo comentários e
    normalizando os separadores. Retorna uma lista com os elementos da instrução.

    Parâmetros:
    -----------
        linha (str): Linha bruta do código, possivelmente com vírgulas e comentários.

    Retorna:
    -----------
        list[str]: Lista de strings representando os elementos da instrução limpa.
    """

    linha = linha.replace(",", " ")
    partes = linha.strip().split(';')
    partes = partes[0].strip().split()

    return partes


def verifica_label(partes):
    """
    Verifica se há um label no início da instrução e, se houver,
    armazena o label associado ao endereço atual (em hexadecimal).

    Parâmetros:
        partes (list[str]): Lista de elementos da instrução, podendo começar com um label.

    Retorna:
        list[str]: Lista de elementos da instrução sem o label.
    """
    global endereco, label

    if ":" in partes[0]:
        label[partes[0]] = f"0x{endereco+1:02x}"
        partes = partes[1:]

    return partes

def converte_registradores(ra, rb):
    """
    Concatena os valores binários de dois registradores e converte o resultado
    para uma representação hexadecimal com dois dígitos.

    Parâmetros:
        ra (str): Nome do primeiro registrador (ex: 'r0', 'r1', ...).
        rb (str): Nome do segundo registrador.

    Retorna:
        str: Representação hexadecimal dos dois registradores combinados.
    """
    regs = registradores[ra] + registradores[rb]
    hexaregs = converte_hexadecimal(f"0b{regs}")

    return hexaregs



def instru_com_regs(instrucao, ra, rb):
    """
    Gera a instrução em hexadecimal com base no nome da instrução e dois registradores.

    Para instruções especiais como "DATA" ou "JMPR", substitui o primeiro registrador por "r0"
    e duplica o registrador original em `rb`. Eles só utilizam um registrador 'rb'.

    Parâmetros:
    ----------
        instrucao (str): Nome da instrução (ex: "XOR", "ADD", "DATA", "JMPR").
        ra (str): Nome do registrador de origem.
        rb (str): Nome do registrador de destino.

    Retorna:
    --------
        str: Instrução em formato hexadecimal.
    """

    if instrucao == "DATA" or instrucao == "JMPR":
        rb = ra    
        ra = "r0"  

    hexaregs = converte_registradores(ra.upper(), rb.upper())
    print(hexaregs)
    hexainstru = instrucoesComRegs[instrucao] + hexaregs[1:]
    return hexainstru

def complemento_de_dois(valor):
    """
    Calcula o complemento de dois de um valor (binário, hexadecimal ou decimal)
    e retorna o resultado em hexadecimal com dois dígitos.

    Parâmetros:
    ----------
        valor (str): Valor numérico como string, podendo estar em formato decimal, binário (0b...) ou hexadecimal (0x...).

    Retorna:
    --------
        str: Valor em complemento de dois, representado como hexadecimal (ex: '0xFE').
    """

    if "x" not in valor and "b" not in valor:
        valor = int(valor)
    else:
        valor = int(valor, 0)

    valor = f"{valor:09b}"
    valor = "".join("1" if b == "0" else "0" for b in valor if b != '-')
    valor = int(valor, 2) + 1
    
    return f"0x{valor:02x}"


def verifica_intervalo(hexa):
    """
    Verifica se o valor fornecido está dentro dos limites válidos para a arquitetura.

    - Para valores decimais (sem prefixo '0x' ou '0b'): aceita intervalo de -128 a 127 (8 bits com sinal).
    - Para valores binários ou hexadecimais (com prefixos): aceita até 255 (8 bits sem sinal).

    Parâmetros:
        hexa (str): Valor numérico em formato decimal, binário (0b...) ou hexadecimal (0x...).

    Retorna:
        int: Retorna 1 se o valor está no intervalo válido, senão 0.
    """
    try:
        if "x" not in hexa and "b" not in hexa:
            hexa = int(hexa)
            if hexa > 127 or hexa < -128:
                return 0
        else:
            hexa = int(hexa, 0)
            if hexa > 255:
                return 0

        return 1

    except ValueError:
        return 0

    
def instru_jcaez(instrucao):
    """
    Constrói a instrução em hexadecimal para comandos do tipo JCAEZ,
    que usam combinações de flags (C, A, E, Z) codificadas em bits.

    Parâmetros:
        instrucao (str): Instrução composta por uma letra de opcode (ex: 'J') seguida por flags (ex: 'CAEZ').

    Retorna:
        str: Instrução montada em hexadecimal (sem prefixo '0x').
    """

    letras = list(instrucao[1:].upper())
    letrasBin = sum(int(jcaez[letra], 2) for letra in letras)
    hexaLetras = hex(letrasBin)
    instruhexa = instrucoesSemRegs[instrucao[0]] + hexaLetras[2:]

    return instruhexa



def instru_sem_regs(instrucao):
    """
    Gera o código hexadecimal para instruções que não utilizam registradores.

    Instruções como "JMP" e "CLF" possuem opcodes fixos.
    Instruções condicionais como "JCAEZ" são processadas separadamente.

    Parâmetros:
        instrucao (str): Nome da instrução (ex: 'JMP', 'CLF', 'JCAEZ').

    Retorna:
        str: Instrução convertida para hexadecimal (sem prefixo '0x').
    """

    if instrucao == "JMP" or instrucao == "CLF":
        hexinstru = instrucoesSemRegs[instrucao]

    elif instrucao[0] == "J":
        hexinstru = instru_jcaez(instrucao)

    return hexinstru

def instru_outside(partes):
    """
    Monta a instrução hexadecimal para comandos do tipo 'outside',
    combinando uma base fixa com bits de operação e registrador.

    Parâmetros:
        partes (list[str]): Lista contendo os elementos da instrução,
                           onde:
                           - partes[0] e partes[1] são comandos mapeados no dicionário 'outside'.
                           - partes[2] é o nome do registrador.

    Retorna:
        str: Instrução completa em formato hexadecimal (ex: '07ab').
    """

    hexa = outside["BASE"]
    comandos = outside[partes[0].upper()] + outside[partes[1].upper()] + registradores[partes[2].upper()]
    comando = int(comandos, 2)
    comando = hex(comando)
    hexa += comando[2:]

    return hexa

def adiciona_instrucao(instrucao):
    """
    Adiciona uma instrução em formato hexadecimal à lista global de instruções
    e incrementa o endereço da próxima instrução.

    Parâmetros:
        instrucao (str): Instrução hexadecimal a ser adicionada.
    """

    global instrucoes_hex, endereco  # Variáveis globais usadas para armazenar instruções e controlar o endereço
    instrucoes_hex.append(instrucao)
    endereco += 1


# Abre o arquivo .asm de entrada
with open(entrada) as arquivo:
    endereco = -1  # Endereço atual (contador de instruções)

    for linha in arquivo:
        print(linha)
        if not linha:
            continue  # Ignora linhas vazias

        partes = limpa_linhas(linha) # Separa os elementos da instrução

        if partes:  # Se houver instrução na linha

            # Verifica se há label no início da linha (ex: INICIO: ...)
            partes = verifica_label(partes)

            # Converte a instrução para maiúsculo
            if(partes):
                instrucao = partes[0].upper() 
            else:
                continue

            print(f"Instrução a ser executada: {instrucao}")
            # INSTRUÇÕES COM DOIS REGISTRADORES (1 BYTE)
            if instrucao in instrucoesComRegs:
                if(instrucao=="JMPR" or instrucao=="DATA"):
                    partes.append("r0")

                hexainstru = instru_com_regs(instrucao, partes[1], partes[2])
                adiciona_instrucao(hexainstru)

                if(instrucao == "DATA"):
                    hexainstru = partes[2]
                    if(verifica_intervalo(hexainstru)):
                        if("-" in hexainstru):
                            hexainstru = complemento_de_dois(hexainstru)
                        
                        hexainstru = "0x" + converte_hexadecimal(hexainstru)
                        adiciona_instrucao(hexainstru)
                    
                    else:
                        print("Erro no valor colocado no Data")
                        break

            
            # INSTRUÇÕES COM DOIS BYTES ( JMP, CLF, JCAEZ)
            elif instrucao in instrucoesSemRegs or instrucao[0] == "J":
                hexainstru = instru_sem_regs(instrucao)
                adiciona_instrucao(hexainstru)

                if(instrucao[0] == "J"):
                    print(partes)
                    hexainstru = partes[1]
                    if(("0b" in hexainstru) or ("0x" in hexainstru) or (hexainstru.isnumeric())):
                        hexainstru = "0x" + converte_hexadecimal(hexainstru)
                    adiciona_instrucao(hexainstru)

            # INSTRUÇÕES DE PERIFÉRICOS: IN/OUT/DATA/ADDR
            elif instrucao in outside:
                hexainstru = instru_outside(partes)
                adiciona_instrucao(hexainstru)

            # INSTRUÇÕES ESPECIAIS (NÃO ESTÃO NOS SETS)/
            else:
                # MOVE RX, RY: troca de valores via XOR Duplo
                if instrucao == 'MOVE':

                    hexainstru = instru_com_regs("XOR", partes[2], partes[1])
                    adiciona_instrucao(hexainstru)

                    hexainstru = instru_com_regs("XOR", partes[1], partes[2])
                    adiciona_instrucao(hexainstru)
                    continue

                # CLR RX: limpa registrador (gera 0x2X)
                elif instrucao == 'CLR':
                    hexainstru = instru_com_regs("DATA", partes[1], "r0")
                    adiciona_instrucao(hexainstru)
                    adiciona_instrucao("0x00")



                # HALT: simula parada como JMP para próxima linha
                elif instrucao == 'HALT':
                    hexainstru = instru_sem_regs("JMP")
                    adiciona_instrucao(hexainstru)
                    if(verifica_intervalo(f"0x{endereco:02x}")):
                        adiciona_instrucao(f"0x{endereco:02x}")
                    else:
                        print("Erro: valor fora do intervalo permitido (0 a 255)")
                        break
                    
            print(f"Instrução: {partes}. hexadecimal final: {hexainstru}")
            print("A label está dessa forma: ", label)
            
# Gera arquivo de saída no formato compatível com o Logisim
print(instrucoes_hex)
with open(saida, "w") as f:
    f.write("v3.0 hex words plain\n")  # Cabeçalho exigido pelo Logisim
    for hexa in instrucoes_hex:
        if '0x' not in hexa:  # Se for label, resolve o endereço
            hexa = label[f'{hexa}:']
            if(not verifica_intervalo(hexa)):
                print("Erro no intervalo colocado no endereço da Label")
                break
        f.write(f"{hexa}\n")
