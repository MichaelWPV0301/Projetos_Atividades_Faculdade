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

class LinhaInstrucao:
    def __init__(self, operacao="", arg1="", arg2=""):
        self.operacao = operacao
        self.arg1 = arg1
        self.arg2 = arg2

def verificar_argumentos():
    if len(sys.argv) != 3:
        print("Uso correto: python3 montador.py <entrada.asm> <saida.txt>")
        sys.exit(1)

    ext1 = os.path.splitext(sys.argv[1])[1].lower()
    ext2 = os.path.splitext(sys.argv[2])[1].lower()

    if ext1 != ".asm" or ext2 != ".txt":
        print("Extensões devem ser .asm e .txt.")
        sys.exit(1)

def carregar_arquivos():
    try:
        origem = open(sys.argv[1], "r")
        destino = open(sys.argv[2], "w")
        destino.write(CABECALHO_ARQUIVO)
        return origem, destino
    except FileNotFoundError:
        print(f"O arquivo {sys.argv[1]} não foi encontrado.")
        sys.exit(1)

def interpretar_linha(texto):
    texto_original = texto.strip()
    texto = texto.upper().split(";")[0].strip()
    texto = texto.replace(",", " ")
    if not texto:
        return None
    if ":" in texto:
        label, rest = texto.split(":", 1)
        if rest.strip():
            partes = rest.strip().split()
            op = partes[0]
            arg1 = partes[1] if len(partes) > 1 else None
            arg2 = partes[2] if len(partes) > 2 else None
            return [("LABEL", label.strip()), LinhaInstrucao(op, arg1, arg2)]
        return ("LABEL", label.strip())
    partes = texto.split()
    if not partes:
        return None
    op = partes[0]
    arg1 = partes[1] if len(partes) > 1 else None
    arg2 = partes[2] if len(partes) > 2 else None
    return LinhaInstrucao(op, arg1, arg2)

def obter_registrador(nome):
    if not nome or not nome.upper().startswith("R") or not nome[1:].isdigit():
        print(f"Registrador inválido: {nome}")
        sys.exit(1)
    indice = int(nome[1])
    if 0 <= indice <= 3:
        return indice
    print(f"Registrador fora do intervalo válido: {nome}")
    sys.exit(1)

def localizar_instrucao(nome):
    for codigo in CodigoInstrucao:
        if codigo.name == nome:
            return codigo
    return None

def converter_operando(entrada):
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

def converter_operando_jump(entrada, labels):
    if entrada.upper() in labels:
        return int(labels[entrada.upper()])
    return converter_operando(entrada)

def montar_instrucao(instrucao, memoria, posicao, labels):
    if instrucao.operacao == "MOVE":
        r1 = obter_registrador(instrucao.arg1)
        r2 = obter_registrador(instrucao.arg2)
        for a, b in [(r2, r1), (r1, r2), (r2, r1)]:
            byte = CodigoInstrucao.XOR.value | (a << 2) | b
            memoria[posicao] = byte
            posicao += 1
        return posicao

    if instrucao.operacao == "CLR":
        byte1 = CodigoInstrucao.DATA.value | obter_registrador(instrucao.arg1)
        memoria[posicao] = byte1
        posicao += 1
        memoria[posicao] = 0x00
        posicao += 1
        return posicao

    if instrucao.operacao == "HALT":
        memoria[posicao] = CodigoInstrucao.JMP.value
        posicao += 1
        memoria[posicao] = posicao - 1
        posicao += 1
        return posicao

    codigo = localizar_instrucao(instrucao.operacao)
    if not codigo:
        print(f"Instrução desconhecida: {instrucao.operacao}")
        sys.exit(1)

    byte1 = codigo.value
    byte2 = 0x00

    if codigo.name in {"LD", "ST", "ADD", "SHR", "SHL", "NOT", "AND", "OR", "XOR", "CMP"}:
        op1 = obter_registrador(instrucao.arg1)
        op2 = obter_registrador(instrucao.arg2)
        byte1 |= (op1 << 2) | op2
    elif codigo.name == "DATA":
        op1 = obter_registrador(instrucao.arg1)
        op2 = converter_operando(instrucao.arg2)
        byte1 |= op1
        byte2 = op2
    elif codigo.name in {"IN", "OUT"}:
        tipo1 = 1 if codigo.name == "OUT" else 0
        tipo0 = 1 if instrucao.arg1 == "ADDR" else 0
        op2 = obter_registrador(instrucao.arg2)
        byte1 |= (tipo1 << 3) | (tipo0 << 2) | op2
    elif codigo.name == "JMPR":
        op1 = obter_registrador(instrucao.arg1)
        byte1 |= op1
    elif codigo.name == "CLF":
        byte1 = codigo.value
    else:
        byte2 = converter_operando_jump(instrucao.arg1, labels)

    if posicao >= MEMORIA_LIMITE:
        print("Memória insuficiente para armazenar o programa.")
        sys.exit(1)

    memoria[posicao] = byte1
    posicao += 1

    if codigo.usa_segundo_byte:
        if posicao >= MEMORIA_LIMITE:
            print("Memória insuficiente para segundo byte da instrução.")
            sys.exit(1)
        memoria[posicao] = byte2
        posicao += 1

    return posicao

def gravar_memoria(memoria, tamanho, arquivo_saida):
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
    linhas = arquivo_entrada.readlines()

    labels = {}
    pos_tmp = 0
    instrucoes_lidas = []

    for linha in linhas:
        resultado = interpretar_linha(linha)
        if resultado is None:
            continue
        if isinstance(resultado, list):
            for item in resultado:
                if isinstance(item, tuple) and item[0] == "LABEL":
                    labels[item[1].upper()] = pos_tmp
                elif isinstance(item, LinhaInstrucao):
                    instrucoes_lidas.append(item)
                    if item.operacao == "MOVE":
                        pos_tmp += 3
                    elif item.operacao == "CLR":
                        pos_tmp += 2
                    elif item.operacao == "HALT":
                        pos_tmp += 2
                    else:
                        codigo = localizar_instrucao(item.operacao)
                        if codigo:
                            pos_tmp += 2 if codigo.usa_segundo_byte else 1
        elif isinstance(resultado, tuple) and resultado[0] == "LABEL":
            labels[resultado[1].upper()] = pos_tmp
        elif isinstance(resultado, LinhaInstrucao):
            instrucoes_lidas.append(resultado)
            if resultado.operacao == "MOVE":
                pos_tmp += 3
            elif resultado.operacao == "CLR":
                pos_tmp += 2
            elif resultado.operacao == "HALT":
                pos_tmp += 2
            else:
                codigo = localizar_instrucao(resultado.operacao)
                if codigo:
                    pos_tmp += 2 if codigo.usa_segundo_byte else 1

    for instrucao in instrucoes_lidas:
        posicao_atual = montar_instrucao(instrucao, memoria_ram, posicao_atual, labels)

    gravar_memoria(memoria_ram, posicao_atual, arquivo_saida)
    arquivo_entrada.close()
    arquivo_saida.close()
    print(f"Montagem concluída com sucesso. Arquivo gerado em {sys.argv[2]}")

main()
