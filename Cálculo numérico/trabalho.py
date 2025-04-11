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

def seno_taylor(radiano, erro):
    seno = 0
    qtdTermos = 0
    erroRelativo = 1
    while(erroRelativo>erro):
        numerador = (-1)**qtdTermos * radiano**(2*qtdTermos+1)
        numerador1 = (-1)**qtdTermos * radiano**(2*qtdTermos+3)
        denominador = math.factorial(2*qtdTermos+1)
        denominador1 = math.factorial(2*qtdTermos+3)
        erroAbsoluto = abs( numerador1/denominador1)
        termo = numerador /denominador
        seno+=termo
        erroRelativo = abs(erroAbsoluto/seno)
        qtdTermos+=1
    return seno,erroRelativo

def cos_taylor(radiano, erro):
    cos = 0
    qtdTermos = 0
    erroRelativo = 1    
    while(erroRelativo>erro):
        numerador = (-1)**qtdTermos* radiano**(2*qtdTermos)
        numerador1 = (-1)**qtdTermos * radiano**(2*qtdTermos+2)
        denominador = math.factorial(2*qtdTermos)
        denominador1 = math.factorial(2*qtdTermos+2)
        termo = numerador/denominador
        erroAbsoluto = abs(numerador1/denominador1)
        cos += termo
        erroRelativo = abs(erroAbsoluto/cos)
        qtdTermos+=1
    return cos, erroRelativo


P = [[6,5]]
R = [[3,2]]
PemR = [[P[0][0]-R[0][0],P[0][1]-R[0][1]]]
teta = 50
radiano = (math.pi * teta)/180
erro = 1e-12
cos,t1 = cos_taylor(radiano, erro)
seno,t2 = seno_taylor(radiano, erro)
matrizRotacao = [[cos, -seno], [seno, cos]]
print(cos)
print(seno)
print(math.cos(radiano))
print(t1)
print((math.cos(radiano)-cos)/math.cos(radiano))
print(t2)
print(abs((math.sin(radiano)-seno)/math.sin(radiano)))
PemR = multmatriz(PemR, matrizRotacao)
print(PemR)