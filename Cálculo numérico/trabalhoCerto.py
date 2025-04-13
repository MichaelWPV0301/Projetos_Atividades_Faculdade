def rotacionaPonto(ponto, matriz): # Função para rotação de pontos
    ponto = [matriz[0][0]*ponto[0]+matriz[0][1]*ponto[1], matriz[1][0]*ponto[0]+matriz[1][1]*ponto[1]]#multplicação de MxN -> (2,2)X(2x1) => [[a,b],[c,d]X[[e],[f]] = [[ae+bf],[ce,df]]
    return ponto

def senoTaylor(radiano, erro): # Cálculo do seno do ângulo theta (theta é recebido em radiano)
    termo = radiano # Primeiro termo da série de taylor do seno
    seno = radiano # Serie de taylor do seno com o primeiro termo. 
    qtdTermos = 1 # Componente inicial da Série de Taylor para o seno

    while True: # Laço que itera "n-1" termos da Série de Taylor para o seno, com base na comparação entre erro e erroAbsoluto que será feito dentro do while
        # Note: "n-1" iterações, não "n", visto que a primeira iteração da série é dada antes do laço
        numerador = -radiano * radiano # Componente para iterar com o numerador do (k-1)-ésimo para compor o k-ésimo termo da Série de Taylor
        denominador = (2*qtdTermos+1) * (2*qtdTermos) #  Componente para iterar com o denominador do (k-1)-ésimo para compor o k-ésimo termo da Série de Taylor 
        termo *= numerador /denominador # k-ésimo termo da Série
        seno+=termo # Soma sequencial que compõe o seno do ângulo recebido pela função
        erroAbsoluto = abs(termo/seno) # Atualização do erro
        if(erroAbsoluto<erro):#Comparação para obter um série com o erro desejado como dito acima
            break
        qtdTermos+=1 # Atualização do número de termos (na prática, uma contagem de iterações)
    return seno,qtdTermos

def cosTaylor(radiano, erro): # Cálculo do cosseno do ângulo theta (theta é recebido em radiano)
    termo = 1 #Primeiro termo da série de taylor do cosseno
    cos = 1 #  Serie de taylor do cosseno com o primeiro termo. 
    qtdTermos = 1 # Componente inicial da Série de Taylor para o cosseno

    while True: # Laço que itera "n-1" termos da Série de Taylor para o cosseno, com base na comparação entre erro e erroAbsoluto que será feito dentro do while
        # Note novamente: "n-1" iterações, pelo mesmo motivo da função senoTaylor
        numerador = -radiano * radiano  # Componente para iterar com o numerador do (k-1)-ésimo para compor o k-ésimo termo da Série de Taylor
        denominador = (2*qtdTermos) * (2*qtdTermos-1)  # Componente para iterar com o denominador do (k-1)-ésimo para compor o k-ésimo termo da Série de Taylor 
        termo *= numerador/denominador # k-ésimo termo da Série
        cos += termo # Soma sequencial que compõe o cosseno do ângulo recebido pela função
        erroAbsoluto = abs(termo/cos) # Atualizção do erro 
        if(erroAbsoluto<erro): #Comparação para obter um série com o erro desejado como dito acima
            break
        
        qtdTermos+=1 # Atualização do número de termos (na prática, uma contagem de iterações)
    return cos,qtdTermos


def arctanTaylor(x, erro=1e-12, max_iter=10**6):
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
        resultado, termos = arctanTaylor(-x, erro, max_iter)
        return -resultado, termos

    # Redução de domínio para acelerar convergência da série
    if x > 1:
        # arctan(x) = pi/2 - arctan(1/x)
        inner, termos = arctanTaylor(1/x, erro, max_iter)
        return PI / 2 - inner, termos
    elif x > 0.5:
        # arctan(x) = pi/4 + arctan((x - 1)/(1 + x))
        inner, termos = arctanTaylor((x - 1)/(1 + x), erro, max_iter)
        return PI / 4 + inner, termos

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
        if erro_estimado < erro or n > max_iter:
            break

        n += 1

    return soma, n



P = [6,5] #Ponto P dado pelo problema
R = [3,2] #Ponto R dado pelo problema
C = [5,2] #Ponto C dado pelo problema
PemR = [P[0]-R[0],P[1]-R[1]] #Passo para transformar um ponto do plano P em R( MatRotação X (P-R))

teta = 50 #Ângulo dado pelo problema
PI = 3.141592653589793 #Número de PI de acordo com biblioteca math.pi
radiano = (PI * teta)/180 #Transformação do ângulo de graus para radiano
erro = 10**(-12) #Erro desejado dado pelo problema

cos, qtdcos = cosTaylor(radiano, erro) #Aplicação da série de taylor do cosseno(radiano) com erro(10*(-12)), note que a função também retorna a quantidade de termos calculados(qtdcos) 
seno, qtdseno = senoTaylor(radiano, erro) #Aplicação da série de taylor do seno(radiano) com erro(10*(-12)), note que a função também retorna a quantidade de termos calculados(qtdseno) 
matrizRotacao = [[cos, seno], [-seno, cos]] #Montagem da matriz de Rotação 



PemR = rotacionaPonto(PemR, matrizRotacao) #Rotação do ponto com a função, ou seja a função retorno a multiplição da Matriz pelo ponto.
raioR = ((PemR[0]**2)+(PemR[1]**2))**(1/2) #Cálculo do raio para notação em coordenada polar, note que é apenas a implementação do teorema de pitágoras R=(x^(2)+y^(2))^(1/2)
anguloR, termosR = arctanTaylor(PemR[1]/PemR[0]) #Cálculo da Serie de taylor do Arctan(y/x), um dos passos necessários para notação polar, note que a função também retorna a quantidade de termos calculados na série.
PRpolar = [raioR, anguloR*180/PI] #Montagem do ponto em coordenada polar, PemR(x,y) = PemR(raio, ângulo medido a partir do eixo polar)



PemC = [PemR[0]-2, PemR[1]] #Visto que a câmera está atrelada ao robô e os planos R e C são paralelos, então para obter P em C, basta subtrair 2 do ponto PemR já obtido.
raioC = ((PemC[0]**2)+(PemC[1]**2))**(1/2) #Cálculo do raio para notação em coordenada polar, note que é apenas a implementação do teorema de pitágoras R=(x^(2)+y^(2))^(1/2)
anguloC,termosC = arctanTaylor(PemC[1]/PemC[0]) #Cálculo da Serie de taylor do Arctan(y/x), um dos passos necessários para notação polar, note que a função também retorna a quantidade de termos calculados na série.
PCpolar = [raioC, anguloC*180/PI] #Montagem do ponto em coordenada polar, PemC(x,y) = PemC(raio, ângulo medido a partir do eixo polar)

#Retornando os resultados obtidos, exigidos no trabalho.
print(f"O ponto P em R:\nCoordenada cartesiana = ({PemR[0]:.12f},{PemR[1]:.12f})\nCoordenada polar = ({PRpolar[0]:.12f},{PRpolar[1]:.12f})\n")
print(f"O ponto P em C:\nCoordenada cartesiana = ({PemC[0]:.12f},{PemC[1]:.12f})\nCoordenada polar = ({PCpolar[0]:.12f},{PCpolar[1]:.12f})")

print(f"\nQuantidade de termos utlizadas para calcular a série de Taylor da função seno(50°) foi: {qtdseno}")
print(f"Quantidade de termos utlizadas para calcular a série de Taylor da função cosseno(50°) foi: {qtdcos}")
print(f"Quantidade de termos utlizadas para calcular a série de Taylor da função arco tangente(y/x) do ponto PemR foi: {termosR}")
print(f"Quantidade de termos utlizadas para calcular a série de Taylor da função arco tangente(y/x) do ponto PemC foi: {termosC}")
