import math

def rotaciona_ponto(ponto, matriz):
    ponto = [matriz[0][0]*ponto[0]+matriz[0][1]*ponto[1], matriz[1][0]*ponto[0]+matriz[1][1]*ponto[1]]
    return ponto

def seno_taylor(radiano, erro):
    seno = radiano
    qtdTermos = 1
    denominador = 1
    erroAbsoluto = 1 + erro
    while(erroAbsoluto>erro):
        numerador = (-1)**qtdTermos * radiano**(2*qtdTermos+1)
        denominador *= (2*qtdTermos+1) * (2*qtdTermos)
        termo = numerador /denominador
        seno+=termo
        erroAbsoluto = abs(termo)
        qtdTermos+=1
    return seno

def cos_taylor(radiano, erro):
    cos = 1
    qtdTermos = 1
    denominador = 1 
    erroAbsoluto = 1 +erro 

    while(erroAbsoluto>erro):
        numerador = (-1)**qtdTermos* radiano**(2*qtdTermos)
        denominador *= (2*qtdTermos) * (2*qtdTermos-1)
        termo = numerador/denominador
        cos += termo
        erroAbsoluto = abs(termo)
        qtdTermos+=1
    return cos


def taylor_arctan(x, erro_relativo=1e-12, max_iter=10**6):
    """
    Calcula uma aproximação para arctan(x) utilizando a série de Taylor,
    com otimizações para acelerar a convergência e reduzir o custo computacional.

    Estratégias adotadas:
    - Redução de domínio para x > 1 e 0.5 < x <= 1 usando identidades trigonométricas.
    - Uso da simetria da função para x < 0.
    - Evita chamadas a pow() e factorial(), utilizando atualização recursiva do termo.
    - Critério de parada baseado em erro relativo estimado.

    Parâmetros:
    x (float): valor real para o qual se deseja calcular arctan(x)
    erro_relativo (float): precisão desejada para o erro relativo da aproximação
    max_iter (int): número máximo de iterações para evitar loops infinitos

    Retorna:
    (float, int): aproximação de arctan(x) e número de termos usados
    """

    # Lida com valores negativos usando simetria: arctan(-x) = -arctan(x)
    if x < 0:
        resultado, termos = taylor_arctan(-x, erro_relativo, max_iter)
        return -resultado, termos

    # Redução de domínio para acelerar convergência da série
    if x > 1:
        # arctan(x) = pi/2 - arctan(1/x)
        inner, termos = taylor_arctan(1/x, erro_relativo, max_iter)
        return math.pi / 2 - inner, termos
    elif x > 0.5:
        # arctan(x) = pi/4 + arctan((x - 1)/(1 + x))
        inner, termos = taylor_arctan((x - 1)/(1 + x), erro_relativo, max_iter)
        return math.pi / 4 + inner, termos

    # Série de Taylor para |x| <= 0.5
    termo = x              # Primeiro termo da série: x^(2*0+1)/(2*0+1)
    soma = termo           # Acumulador da soma da série
    n = 1                  # Índice do termo atual

    while True:
        # Geração eficiente do próximo termo: termo_n = -x^2 * termo_(n-1)
        termo *= -x * x
        prox = termo / (2 * n + 1)
        soma += prox

        # Estimativa do erro relativo com base no último termo adicionado
        erro_estimado = abs(prox / soma) if soma != 0 else abs(prox)
        if erro_estimado < erro_relativo or n > max_iter:
            break

        n += 1

    return soma, n



P = [6,5]
R = [3,2]
C = [5,2] 
PemR = [P[0]-R[0],P[1]-R[1]]
#PemR1 = [P[0][0]-R[0][0],P[0][1]-R[0][1]]

teta = 50
pi = math.pi
radiano = (pi * teta)/180
erro = 10**(-12)

cos = cos_taylor(radiano, erro)
seno = seno_taylor(radiano, erro)
matrizRotacao = [[cos, seno], [-seno, cos]]



PemR = rotaciona_ponto(PemR, matrizRotacao)
raioR = ((PemR[0]**2)+(PemR[1]**2))**(1/2)
anguloR = taylor_arctan(PemR[1]/PemR[0])[0]*180/pi
PRpolar = [raioR, anguloR]



PemC = [PemR[0]-2, PemR[1]]
raioC = ((PemC[0]**2)+(PemC[1]**2))**(1/2)
anguloC = taylor_arctan(PemC[1]/PemC[0])[0]*180/pi
PCpolar = [raioC, anguloC]

print(f"O ponto P em R:\nCoordenada cartesiana = ({PemR[0]:.12f},{PemR[1]:.12f})\nCoordenada polar = ({PRpolar[0]:.12f},{PRpolar[1]:.12f})\n")

print(f"O ponto P em C:\nCoordenada cartesiana = ({PemC[0]:.12f},{PemC[1]:.12f})\nCoordenada polar = ({PCpolar[0]:.12f},{PCpolar[1]:.12f})")

