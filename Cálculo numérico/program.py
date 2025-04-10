import math

def multmatriz(matA, matB):

    linhasA, colunasA= len(matA), len(matA[0])
    linhasB, colunasB = len(matB), len(matB[0])

    result = [[0] * colunasB for _ in range(linhasA)]

    for i in range(linhasA):
        Ai = matA[i]
        Ci = result[i]
        for k in range(colunasB):
            Aik = Ai[k]
            Bk = matB[k]
            for j in range(linhasB):
                Ci[j] += Aik * Bk[j]
    
    return result


def termos_erroSeno(radiano , erro_desejado):
    real = math.sin(radiano)
    soma = 0
    n = 0
    while True:
        termo = (-1)**n * radiano**(2*n + 1) / math.factorial(2*n + 1)
        soma += termo
        erro = abs(real - soma)
        if erro < erro_desejado:
            break
        n += 1
    return n + 1  # +1 porque o índice começa em 0



def termos_erroCos(radiano , erro_desejado):
    real = math.cos(radiano)
    soma = 0
    n = 0
    while True:
        termo = (-1)**n * radiano**(2*n) / math.factorial(2*n)
        soma += termo
        erro = abs(real - soma)
        if erro < erro_desejado:
            break
        n += 1
    return n + 1  # +1 porque o índice começa em 0

def seno_taylor(radiano, termos):
    seno = 0
    for n in range(termos):
        numerador = (-1)**n * radiano**(2*n+1)
        denominador = math.factorial(2*n+1)
        termo = numerador /denominador
        seno+=termo
    return seno

def cos_taylor(radiano, termos):
    cos = 0
    for n in range(termos):
        numerador = (-1)**n * radiano**(2*n)
        denominador = math.factorial(2*n)
        termo = numerador/denominador
        cos += termo
    return cos


P = [[6,5]]
R = [[3,2]]
PemR = [[P[0][0]-R[0][0],P[0][1]-R[0][1]]]
teta = 50
radiano = (math.pi * teta)/180
erro = 10**(-12)
termosCos = termos_erroCos(radiano, erro)
termosSen = termos_erroSeno(radiano, erro)
matrizRotacao = [[cos_taylor(radiano, termosCos), -seno_taylor(radiano, termosSen)], [seno_taylor(radiano, termosSen), cos_taylor(radiano, termosSen)]]
PemR = multmatriz(PemR, matrizRotacao)
print(PemR)