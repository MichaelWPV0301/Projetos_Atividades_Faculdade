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

def qtd_termos_seno(radiano, erro):
    n=0
    resto = erro+1
    while(resto>erro):
        resto = abs(radiano)**(2*n+1)/math.factorial(2*n+1)
        n+=1
    return n


def seno_taylor1(radiano, n):
    qtd = 0
    seno = 0
    while(qtd<n):
        numerador = (-1)**qtd* radiano**(2*qtd+1)
        denominador = math.factorial(2*qtd+1)
        seno += numerador/denominador
        qtd+=1
    return seno

def qtd_termos_cos(radiano, erro):
    n=0
    resto = erro+1
    while(resto>erro):
        resto = abs(radiano)**(2*n)/math.factorial(2*n)
        n+=1
    return n

def cos_taylor1(radiano, n):
    qtd =0
    cos = 0
    while(qtd<n):
        numerador = (-1)**qtd*radiano**(2*qtd)
        denominador = math.factorial(2*qtd)
        cos += numerador/denominador
        qtd+=1
    return cos
        



def seno_taylor(radiano, erro):
    seno = 0
    qtdTermos = 0
    erroRelativo = 1
    while(erroRelativo>erro):
        numerador = (-1)**qtdTermos * radiano**(2*qtdTermos+1)
        #numerador1 = (-1)**qtdTermos * radiano**(2*qtdTermos+3)
        denominador = math.factorial(2*qtdTermos+1)
        #denominador1 = math.factorial(2*qtdTermos+3)
        #erroAbsoluto = abs( numerador1/denominador1)
        termo = numerador /denominador
        seno+=termo
        #esse erro Relativo é o erro estimado.
        erroRelativo = abs(termo)/abs(seno)
        qtdTermos+=1
    return seno, qtdTermos

def cos_taylor(radiano, erro):
    cos = 0
    qtdTermos = 0
    erroRelativo = 1  
    while(erroRelativo>erro):
        numerador = (-1)**qtdTermos* radiano**(2*qtdTermos)
        ##numerador1 = (-1)**qtdTermos * radiano**(2*qtdTermos+2)
        denominador = math.factorial(2*qtdTermos)
        ##denominador1 = math.factorial(2*qtdTermos+2)
        termo = numerador/denominador
        #erroAbsoluto = abs(numerador1/denominador1)
        cos += termo
        #esse erro Relativo é o erro estimado.
        erroRelativo = abs(termo)/abs(cos)
        qtdTermos+=1
    return cos, qtdTermos


P = [[6,5]]
R = [[3,2]]
PemR = [[P[0][0]-R[0][0],P[0][1]-R[0][1]]]
PemR1 = [[P[0][0]-R[0][0],P[0][1]-R[0][1]]]

teta = 50
pi = math.pi
radiano = (math.pi * teta)/180
erro = 10**(-12)




qtdcos = qtd_termos_cos(radiano, erro)
qtdsen = qtd_termos_seno(radiano, erro)
cos1 = cos_taylor1(radiano, qtdcos)
seno1 = seno_taylor1(radiano, qtdsen)




cos,t1 = cos_taylor(radiano, erro)
seno,t2 = seno_taylor(radiano, erro)

xsd, t3 = cos_taylor(math.pi, erro)
xssad, t4 = seno_taylor(math.pi, erro)
xsd, t5 = cos_taylor(2*math.pi, erro)
xssad, t6 = seno_taylor(2*math.pi, erro)


matrizRotacao = [[cos, -seno], [seno, cos]]
matrizRotacao1 = [[cos1, -seno1], [seno1, cos1]]

print(f"Valor cos(50) regs usando série de taylor: {cos}")
print(f"Valor cos1(50) lagrange usando série de taylor: {cos1}")
print(f"Valor cos(50) real: {math.cos(radiano)}")


print(f"\nValor sen(50)  regs usando série de taylor: {seno}")
print(f"Valor sen(50) lagrange usando série de taylor: {seno1}")
print(f"Valor sen(50) real: {math.sin(radiano)}")

print(f"\nQuantidade de termos cos(50) regs: {t1}")
print(f"Quantidade de termos cos(180) regs: {t3}")
print(f"Quantidade de termos cos(360) regs: {t6}")
print(f"Quantidade de termos cos lagrange teta=50: {qtdcos}")
print(f"Quantidade de termos cos lagrange teta=180: {qtd_termos_cos(pi, erro)}")
print(f"Quantidade de termos cos lagrange teta=360: {qtd_termos_cos(2*math.pi, erro)}")


print(f"\nQuantidade de termos sen(50) regs: {t2}")
print(f"Quantidade de termos sen(180) regs: {t4}")
print(f"Quantidade de termos sen(360) regs: {t6}")
print(f"Quantidade de termos sen lagrange teta=50: {qtdsen}")
print(f"Quantidade de termos sen lagrange teta=180: {qtd_termos_seno(pi, erro)}")
print(f"Quantidade de termos sen lagrange teta=360: {qtd_termos_seno(2*math.pi, erro)}")


print(f"\nErro relativo cos regs real: {abs((math.cos(radiano)-cos)/math.cos(radiano))}")
print(f"Erro relativo sen regs real: {(abs(math.sin(radiano)-seno)/math.sin(radiano))}")
print(f"Erro relativo cos1 lagrange real: {abs((math.cos(radiano)-cos1)/math.cos(radiano))}")
print(f"Erro relativo sen1 lagrange real: {(abs(math.sin(radiano)-seno1)/math.sin(radiano))}")


print(f'\ncomparação lagrange sen(360) 18x15: {seno_taylor1(2*pi, 18)} X {seno_taylor1(2*pi, 15 )}')


PemR = multmatriz(PemR, matrizRotacao)
PemR1 = multmatriz(PemR1, matrizRotacao1)

print(PemR)
print(PemR1)