# Aluno : Pedro Henrique Belota Gadelha
# Matrícula: 22401920

import sys
import os
from enum import Enum

# Constantes globais da montagem
CABECALHO_ARQUIVO = "v3.0 hex words plain\n"
TAMANHO_BYTE = 1
BITS_TOTAIS = TAMANHO_BYTE * 8
VALOR_MAXIMO = (1 << (BITS_TOTAIS - 1)) - 1
VALOR_MINIMO = -(1 << (BITS_TOTAIS - 1))
MASCARA_BITS = (1 << BITS_TOTAIS) - 1
AJUSTE_NEGATIVO = (1 << BITS_TOTAIS)
MEMORIA_LIMITE = 256

# Enumeração com os códigos das instruções
class CodigoInstrucao(Enum):
    def __new__(cls, opcode, usa_segundo_byte=False):
        obj = object.__new__(cls)
        obj._value_ = opcode
        obj.usa_segundo_byte = usa_segundo_byte
        return obj

    LD = (0x00, False)
    ST = (0x10, False)
    DATA = (0x20, True)
    JMPR = (0x30, False)
    JMP = (0x40, True)
    JC = (0x58, True)
    JA = (0x54, True)
    JE = (0x52, True)
    JZ = (0x51, True)
    JCA = (0x5C, True)
    JCE = (0x5A, True)
    JCZ = (0x59, True)
    JAE = (0x56, True)
    JAZ = (0x55, True)
    JEZ = (0x53, True)
    JCAE = (0x5E, True)
    JCAZ = (0x5D, True)
    JCEZ = (0x5B, True)
    JAEZ = (0x57, True)
    JCAEZ = (0x5F, True)
    CLF = (0x60, False)
    IN = (0x70, False)
    OUT = (0x78, False)
    ADD = (0x80, False)
    SHR = (0x90, False)
    SHL = (0xA0, False)
    NOT = (0xB0, False)
    AND = (0xC0, False)
    OR = (0xD0, False)
    XOR = (0xE0, False)
    CMP = (0xF0, False)

# Estrutura que representa uma linha traduzida do código ASM
class LinhaInstrucao:
    def __init__(self, operacao="", arg1="", arg2=""):
        self.operacao = operacao
        self.arg1 = arg1
        self.arg2 = arg2

def verificar_argumentos():
    """Função: verificar_argumentos
    Verifica os argumentos passados pela linha de comando."""
    if len(sys.argv) != 3:
        print("Uso correto: python3 montador.py <entrada.asm> <saida.txt>")
        sys.exit(1)

    ext1 = os.path.splitext(sys.argv[1])[1].lower()
    ext2 = os.path.splitext(sys.argv[2])[1].lower()

    if ext1 != ".asm" or ext2 != ".txt":
        print("Extensões devem ser .asm e .txt.")
        sys.exit(1)

def carregar_arquivos():
    """Função carregar_arquivo
    Abre os arquivos de entrada e saída."""
    try:
        origem = open(sys.argv[1], "r")
        destino = open(sys.argv[2], "w")
        destino.write(CABECALHO_ARQUIVO)
        return origem, destino
    except FileNotFoundError:
        print(f"O arquivo {sys.argv[1]} não foi encontrado.")
        sys.exit(1)

def interpretar_linha(texto):
    """Função: interpretar_linha
    Traduz uma linha para uma estrutura de instrução."""
    texto = texto.upper().split(";")[0].strip()
    texto = texto.replace(",", " ")
    partes = texto.split()
    if not partes:
        return None

    op = partes[0]
    arg1 = partes[1] if len(partes) > 1 else None
    arg2 = partes[2] if len(partes) > 2 else None
    return LinhaInstrucao(op, arg1, arg2)

def obter_registrador(nome):
    """Função: obter_registrador
    Valida e retorna o índice numérico do registrador."""
    if not nome or not nome.upper().startswith("R") or not nome[1:].isdigit():
        print(f"Registrador inválido: {nome}")
        sys.exit(1)

    indice = int(nome[1])
    if 0 <= indice <= 3:
        return indice

    print(f"Registrador fora do intervalo válido: {nome}")
    sys.exit(1)

def localizar_instrucao(nome):
    """Função: localizar_instrucao
    Busca o código de operação ao nome dado."""
    for codigo in CodigoInstrucao:
        if codigo.name == nome:
            return codigo
    print(f"Instrução desconhecida: {nome}")
    sys.exit(1)

def converter_operando(entrada):
    """Função: converter_operando
    converte um argumento da instrucao para o hexadecimal"""
    if entrada and not entrada.startswith("R") and entrada not in {"DATA", "ADDR"}:
        try:
            if entrada.startswith("0X"):
                valor = int(entrada, 16)
            elif entrada.startswith("0B"):
                valor = int(entrada, 2)
            else:
                valor = int(entrada)
                if valor < VALOR_MINIMO or valor > VALOR_MAXIMO:
                    raise ValueError(f"valor fora do intervalo permitido: {valor} | [{VALOR_MINIMO},{VALOR_MAXIMO}]")
                if valor < 0:
                    valor += AJUSTE_NEGATIVO
            return valor & MASCARA_BITS
        except ValueError as e:
            print(e)
            sys.exit(1)
    return entrada

def converter_operando_jump(entrada):
    """Função: converter_operando_jump
    converte um argumento da instrucao para o hexadecimal"""
    if entrada and not entrada.startswith("R") and entrada not in {"DATA", "ADDR"}:
        try:
            if entrada.startswith("0X"):
                valor = int(entrada, 16)
            elif entrada.startswith("0B"):
                valor = int(entrada, 2)
            else:
                valor = int(entrada)
                if valor < 0 or valor > MASCARA_BITS:
                    raise ValueError(f"valor fora do intervalo permitido: {valor} | [0,{MASCARA_BITS}]")
            return valor & MASCARA_BITS
        except ValueError as e:
            print(e)
            sys.exit(1)
    return entrada

def montar_instrucao(instrucao, memoria, posicao):
    """Função: montar_instrução
    Gera os bytes de instrução e armazena na memória."""
    codigo = localizar_instrucao(instrucao.operacao)
    

    byte1 = codigo.value
    byte2 = 0x00

    if codigo.name in {"LD", "ST", "ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP"}:
        op1 = converter_operando(instrucao.arg1)
        op2 = converter_operando(instrucao.arg2 )
        byte1 |= (obter_registrador(op1) << 2) | obter_registrador(op2)
    elif codigo.name == "DATA":
        op1 = converter_operando(instrucao.arg1)
        op2 = converter_operando(instrucao.arg2 )
        byte1 |= obter_registrador(op1)
        byte2 = op2
    elif codigo.name in {"IN", "OUT"}:
        op1 = converter_operando(instrucao.arg1)
        op2 = converter_operando(instrucao.arg2 )
        tipo1 = 1 if codigo.name == "OUT" else 0
        tipo0 = 1 if op1 == "ADDR" else 0
        byte1 |= (tipo1 << 3) | (tipo0 << 2) | obter_registrador(op2)
    elif codigo.name == "JMPR":
        op1 = converter_operando(instrucao.arg1)
        byte1 |= obter_registrador(op1)
    elif codigo.name == "CLF":
        byte1 = codigo.value
    else: #jumps
        op1 = converter_operando_jump(instrucao.arg1)
        byte2 = op1

    if posicao >= MEMORIA_LIMITE:
        print("memória insuficiente para armazenar o programa.")
        sys.exit(1)

    memoria[posicao] = byte1
    posicao += 1

    if codigo.usa_segundo_byte:
        if posicao >= MEMORIA_LIMITE:
            print("memória insuficiente para segundo byte da instrução.")
            sys.exit(1)
        memoria[posicao] = byte2
        posicao += 1

    return posicao

def gravar_memoria(memoria, tamanho, arquivo_saida):
    """Função: gravar_memoria
    Salva o conteúdo da memória no arquivo de saída."""
    for i in range(tamanho, MEMORIA_LIMITE):
        memoria.append(0x00)

    for i in range(MEMORIA_LIMITE):
        arquivo_saida.write(f"{memoria[i]:02x} ")
        if (i + 1) % 16 == 0:
            arquivo_saida.write("\n")

def main():
    verificar_argumentos()
    arquivo_entrada, arquivo_saida = carregar_arquivos()

    memoria_ram = [0x00] * MEMORIA_LIMITE
    posicao_atual = 0

    for linha in arquivo_entrada:
        instrucao = interpretar_linha(linha)
        print(instrucao)
        if instrucao and instrucao.operacao:
            posicao_atual = montar_instrucao(instrucao, memoria_ram, posicao_atual)

    gravar_memoria(memoria_ram, posicao_atual, arquivo_saida)
    arquivo_entrada.close()
    arquivo_saida.close()
    print(f"Montagem concluída com sucesso. Arquivo gerado em {sys.argv[2]}")

main()