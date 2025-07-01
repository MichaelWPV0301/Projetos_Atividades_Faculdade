"""
Trabalho de Organização de Computadores - Montador
Aluno: [Miguel Oliveira Moraes de Souza]
Matrícula: [22450211]

Descrição:
Este montador converte instruções escritas em linguagem de montagem (assembly)
a partir de um arquivo .asm para um arquivo de saída .txt contendo instruções
em hexadecimal (formato Logisim).

Modo de uso:
    python3 montador.py programa.asm exe3.txt

Observação:
Se houver erro na conversão de alguma linha, o programa exibirá a mensagem de erro
correspondente e será encerrado.
- O primeiro argumento deve ser um arquivo com extensão .asm.
- O segundo argumento deve ser o nome do arquivo de saída com extensão .txt.
"""

import sys

arquivo_entrada = sys.argv[1]
arquivo_saida = sys.argv[2]
numeros_hexa = []

jcaezBinario = {"c":0b1000, "a":0b0100, "e":0b0010, "z":0b0001}
instrucoes = {"add":0b10000000,"shr":0b10010000, "shl":0b10100000, "not":0b10110000, "and":0b11000000, 
"or":0b11010000, "xor":0b11100000, "cmp":0b11110000, "ld":0b00000000, "st":0b00010000, "data":0b00100000,
"jmpr":0b00110000, "jmp":0b01000000, "jcaez":0b01010000, "clf":0b01100000}
enderecos = {}

def remover_comentario(linha):
    """Remove comentários de uma linha, considerando o caractere ';' como início de comentário."""
    if ";" in linha:
        linha = linha.split(";")[0]
    return linha

def flags_caez(jcaez):
    """
    Converte a instrução condicional JCAEZ para seu equivalente binário e retorna o hexadecimal.
    Exemplo: jce -> adiciona as flags C (1000) e E (0010)
    """   
    codbinario = 0b01010000
    lista = jcaez[1:]
    for letra in lista:
        codbinario += jcaezBinario[letra]
    return converter_para_hexa(codbinario)
    
def converter_para_hexa(binario):
    """
    Converte um número dado (em string ou binário) para hexadecimal com 2 dígitos.
    Lida com entradas em decimal, binário (0b), hexadecimal (0x), inclusive negativas.

    Valida se o número está dentro do intervalo de 8 bits com sinal (-128 a 127).
    """
    binario = str(binario)
    if binario.startswith("-"):
        sinal = "-"
        numero = binario[1:]
        numero = numero.lstrip('0') or '0'
        binario = sinal + numero
    if binario.startswith('0x'):
        decimal = int(binario,16)
    elif binario.startswith('0b'):
        decimal = int(binario,2)
    else:
        binario = binario.lstrip("0") or "0"
        decimal = int(binario, 10)
    if decimal > 127 and decimal < 256:
        decimal = decimal - 256
    if decimal > 127 or decimal < -128:
        print("AVISO: Algum valor está fora do intervalo de 8 bits. O programa será encerrado. Conversão falha.")
        exit(1)
    convertido = hex(decimal & 0xFF)[2:].zfill(2)
    if len(convertido) < 2:
        convertido = "0" + convertido
    return convertido
    
def montador(instrucao):
    global enderecos
    global endereco
    """
    Recebe uma instrução assembly como string e converte para código hexadecimal
    correspondente, que será adicionado na lista global `numeros_hexa`.

    Trata instruções:
    - in/out
    - JCAEZ
    - instruções aritméticas, lógicas, memória e controle.
    """
    instrucao = instrucao.replace(',', ' ').split()
    if(":" in instrucao[0]):
        enderecos[instrucao[0]] = converter_para_hexa(f"0x{endereco+1:02x}")
        instrucao = instrucao[1:]

    if instrucao[0].lower() in ["in", "out"]:
        codbinario = 0b01110000
        if instrucao[0].lower() == "in":
            codbinario += 0b0000
        elif instrucao[0].lower() == "out":
            codbinario += 0b1000
        if instrucao[1].lower() == "data":
            codbinario += 0b0000
        elif instrucao[1].lower() == "addr":
            codbinario += 0b0100
        codbinario += int(instrucao[2][1])
        numeros_hexa.append(converter_para_hexa(codbinario))
        endereco+=1
    elif instrucao[0][0].lower() == "j" and "mp" not in instrucao[0]:
        numeros_hexa.append(flags_caez(instrucao[0]))
        numeros_hexa.append(converter_para_hexa(instrucao[1]) if ('0x' in instrucao[1]) or ('0b' in instrucao[1]) else instrucao[1])
        endereco+=2
    elif instrucao[0].upper() == 'MOVE':
        ra = int(instrucao[2][1])
        rb = int(instrucao[1][1])
        codbinario = int(instrucoes['xor']) + (ra<<2) + rb
        numeros_hexa.append(converter_para_hexa(codbinario))

        ra = int(instrucao[1][1])
        rb = int(instrucao[2][1])
        codbinario = int(instrucoes['xor']) + (ra<<2) + rb
        numeros_hexa.append(converter_para_hexa(codbinario))
        endereco+=2


    elif instrucao[0].upper() == 'CLR':
        codbinario = int(instrucoes['data']) + int(instrucao[1][1])
        numeros_hexa.append(converter_para_hexa(codbinario))
        numeros_hexa.append(converter_para_hexa('0x00'))
        endereco+=2
    elif instrucao[0].upper() == 'HALT':
        numeros_hexa.append(converter_para_hexa(0b01000000))
        endereco+=1
        numeros_hexa.append(converter_para_hexa(f"0b{endereco:09b}"))
        endereco+=1
    else:
        if instrucoes[instrucao[0]] > 0b01110000 or instrucoes[instrucao[0]] < 0b00100000:
            ra = int(instrucao[1][1])
            rb = int(instrucao[2][1])
            codbinario = int(instrucoes[instrucao[0]]) + (ra<<2) + rb
            numeros_hexa.append(converter_para_hexa(codbinario))
            endereco+=1
        elif instrucoes[instrucao[0]] == 0b00100000: #Data
            codbinario = int(instrucoes[instrucao[0]]) + int(instrucao[1][1])
            numeros_hexa.append(converter_para_hexa(codbinario))
            print(instrucao[2])
            numeros_hexa.append(converter_para_hexa(instrucao[2]))
            endereco+=2
        elif instrucoes[instrucao[0]] == 0b00110000: #Jmpr
            codbinario = int(instrucoes[instrucao[0]]) + int(instrucao[1][1])
            numeros_hexa.append(converter_para_hexa(codbinario))
            endereco+=1
        elif instrucoes[instrucao[0]] == 0b01000000: #Jmp
            numeros_hexa.append(converter_para_hexa(0b01000000))
            numeros_hexa.append(converter_para_hexa(instrucao[1]) if ('0x' in instrucao[1]) or ('0b' in instrucao[1]) else instrucao[1])
            endereco+=2
        elif instrucoes[instrucao[0]] == 0b01100000: #CLF
            numeros_hexa.append(converter_para_hexa(0b01100000))
            endereco+=1

arquivo_assembly = open(arquivo_entrada, "r")
linhas = arquivo_assembly.readlines()
qtde_linhas = len(linhas)
endereco = -1
for i in range(qtde_linhas):
        
    i = remover_comentario(linhas[i]).strip().lower()
    if i:
        converter = montador(i)
arquivo_assembly.close()
       
arquivo_texto = open(arquivo_saida, "w") 
arquivo_texto.write("v3.0 hex words plain\n")
numero_instrucoes = len(numeros_hexa)
for elemento in range(numero_instrucoes):
    if(f'{numeros_hexa[elemento]}:' in enderecos):
        numero_hexa = enderecos[f'{numeros_hexa[elemento]}:']
    else:
        try:
            int(numeros_hexa[elemento], 16)
            numero_hexa = numeros_hexa[elemento]
        except Exception:
            print(numeros_hexa[elemento])
            print("AVIS0: algum endereço fornecido nos JMP ou JCAEZ está incorreto.")    
    arquivo_texto.write(numero_hexa + "\n")
print("Conversão feita com sucesso!")
