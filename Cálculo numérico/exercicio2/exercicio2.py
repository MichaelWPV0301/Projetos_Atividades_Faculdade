from math import sqrt as raiz_quadrada
import time

operacoes_ponto_fixo = 0
operacoes_ponto_flutuante = 0

#funções auxiliares para as resoluções exigidas no trabalho:


def resolver_triangular_inferior(L, b):
    global operacoes_ponto_fixo, operacoes_ponto_flutuante
    n = len(L)  # Tamanho do sistema
    y = [0] * n  # Inicializa o vetor y com zeros

    for i in range(n):
        # Soma dos termos já resolvidos: L[i][k] * y[k]
        sum_k = 0.0
        for k in range(i):
            contar_operacao(L[i][k],y[k])
            mult = L[i][k]*y[k]
            contar_operacao(mult, sum_k)
            sum_k += mult

        operacoes_ponto_fixo-=1
        # Calcula y[i] resolvendo a equação L[i][i] * y[i] = b[i] - soma
        contar_operacao(b[i], sum_k)
        contar_operacao_divisao(b[i]-sum_k, L[i][i])        
        y[i] = (b[i] - sum_k) / L[i][i]  # Divisão para resolver y[i]

    return y  # Retorna o vetor intermediário y



def resolver_triangular_superior(U, y):
    global operacoes_ponto_fixo, operacoes_ponto_flutuante
    n = len(U)  # Tamanho do sistema
    x = [0] * n  # Inicializa o vetor solução x com zeros

    # Começa da última equação e vai subindo
    for i in reversed(range(n)):
        # Soma dos termos já resolvidos: U[i][k] * x[k]
        
        sum_k = 0.0
        for k in range(i):
            contar_operacao(U[i][k],x[k])
            mult = U[i][k]*x[k]
            contar_operacao(mult, sum_k)
            sum_k += mult

        operacoes_ponto_fixo-=1
        # Verifica divisão por zero
        if U[i][i] == 0:
            raise ValueError("Divisão por zero — matriz singular")

        # Resolve x[i]
        contar_operacao(y[i], sum_k)
        contar_operacao_divisao(y[i]-sum_k, U[i][i]) 
        x[i] = (y[i] - sum_k) / U[i][i]


    return x  # Retorna o vetor solução x



def verificacao_de_simetria(A):
    n = len(A)
    # Verifica se A é simétrica (A[i][j] == A[j][i] para todo i, j)
    for i in range(n):
        for j in range(i + 1, n):  # Apenas verifica os elementos acima da diagonal
            if A[i][j] != A[j][i]:
                return False
    return True




def permutacao_b(b, P):
    # Aplica a permutação de linhas ao vetor b, de acordo com o vetor de permutação P
    return [b[i] for i in P]




def contar_operacao(valor1=0, valor2=0, valor3=0):
    global operacoes_ponto_flutuante, operacoes_ponto_fixo
    if float(valor1).is_integer() and float(valor2).is_integer() and float(valor3).is_integer():
        operacoes_ponto_fixo += 1
    else:
        operacoes_ponto_flutuante += 1

def contar_operacao_divisao(numerador, divisao):
    global operacoes_ponto_flutuante, operacoes_ponto_fixo    
    if(float(numerador).is_integer() and float(divisao).is_integer() and float(numerador/divisao).is_integer()):
        operacoes_ponto_fixo+=1
    else:
        operacoes_ponto_flutuante+=1

#método de decomposição Cholesky ---------------------------------------------------------------------------------------------------------------


def decomposicao_cholesky(A):
    global operacoes_ponto_fixo
    n = len(A)
    
    # Verifica se A é simétrica
    if not verificacao_de_simetria(A):
        raise ValueError("A matriz não é simétrica")

    L = [[0] * n for _ in range(n)]  # Inicializa a matriz L

    # Fatoração de Cholesky
    for i in range(n):
        for j in range(i + 1):
            # Soma dos produtos de L[i][k] e L[j][k]
            sum_k = 0.0           
            for k in range(j):
                contar_operacao(L[i][k],L[j][k])
                mult = L[i][k]*L[j][k]
                contar_operacao(mult, sum_k)
                sum_k += mult
            operacoes_ponto_fixo -= 1

            if i == j:
                # Para a diagonal, calcula o valor de L[i][i]
                contar_operacao(A[i][i], sum_k)
                diag = A[i][i] - sum_k
                
                if diag <= 0:
                    raise ValueError("Matriz não é definida positiva")
                
                contar_operacao(diag)
                raiz = raiz_quadrada(diag)
                L[i][j] = raiz  # Raiz quadrada para a diagonal
            else:
                # Para os elementos abaixo da diagonal
                contar_operacao(A[i][j], sum_k)
                diag = A[i][j] - sum_k

                contar_operacao_divisao(diag, L[j][j])
                div = diag / L[j][j]
                L[i][j] =  div

    return L


def metodo_cholesky(A, b):
    # Primeiro, realiza a decomposição de Cholesky
    L = decomposicao_cholesky(A)

    # Segundo, resolve o sistema L * y = b (substituição direta) sucessiva
    y = resolver_triangular_inferior(L, b)

    # Por fim, resolve o sistema L^T * x = y (substituição reversa) retroativa
    x = resolver_triangular_superior(L, y)

    return x



#método de decomposição LU ---------------------------------------------------------------------------------------------------------------




def decomposicao_LU(A):
    global operacoes_ponto_fixo
    n = len(A)  # Número de linhas/colunas da matriz (assumimos matriz quadrada)

    A = [row[:] for row in A]  # Clona a matriz A para não modificar a original

    # Inicializa as matrizes L e U com zeros
    L = [[0] * n for _ in range(n)]
    U = [[0] * n for _ in range(n)]

    # Vetor de permutação para rastrear trocas de linhas (pivotamento)
    P = list(range(n))

    # Loop sobre cada coluna i
    for i in range(n):
        # Encontra o índice da linha com o maior valor absoluto na coluna i (para pivotamento)
        max_row = max(range(i, n), key=lambda r: abs(A[r][i]))

        # Verifica se a matriz é singular (não pode prosseguir se pivô for zero)
        if A[max_row][i] == 0:
            raise ValueError("Matriz singular")

        # Troca as linhas na matriz A
        A[i], A[max_row] = A[max_row], A[i]

        # Troca as posições no vetor de permutação
        P[i], P[max_row] = P[max_row], P[i]

        # Troca as linhas já preenchidas em L (somente as colunas anteriores a i)
        L[i], L[max_row] = L[max_row], L[i]

        # Calcula a linha i da matriz U
        for j in range(i, n):
            # Soma dos produtos L[i][k] * U[k][j] para k de 0 até i-1

            sum_k = 0
            
            for k in range(i):
                contar_operacao(L[i][k],L[k][j])
                mult = L[i][k]*L[k][j]

                contar_operacao(mult, sum_k)
                sum_k += mult

            operacoes_ponto_fixo-=1
            # Define o valor de U[i][j]
            contar_operacao(A[i][j], sum_k)
            U[i][j] = A[i][j] - sum_k

        # Define o valor da diagonal de L
        L[i][i] = 1

        # Calcula os elementos da coluna i da matriz L abaixo da diagonal
        for j in range(i + 1, n):
            # Soma dos produtos L[j][k] * U[k][i] para k de 0 até i-1

            sum_k = 0.0
            for k in range(i):
                contar_operacao(L[j][k],L[k][i])
                mult = L[j][k]*L[k][i]
                
                contar_operacao(mult, sum_k)
                sum_k += mult

            operacoes_ponto_fixo-=1


            # Define o valor de L[j][i]
            contar_operacao(A[j][i], sum_k)
            numerador = A[j][i] - sum_k
            
            contar_operacao_divisao(numerador, U[i][i])
            L[j][i] = numerador /U[i][i]

    return L, U, P  # Retorna as matrizes L, U e o vetor de permutação





def metodo_LU(A, b):
    # Executa a decomposição LU com pivotamento
    L, U, P = decomposicao_LU(A)

    # Aplica a permutação ao vetor b: resolve o sistema P*b
    b_permutado = permutacao_b(b, P)

    # Resolve o sistema L*y = Pb (substituição direta)
    y = resolver_triangular_inferior(L, b_permutado)

    # Resolve o sistema U*x = y (substituição reversa)
    x = resolver_triangular_superior(U, y)


    return x  # Retorna a solução final x


#Parte de teste do programa feito para o trabalho:

try:
    #Sistema Ax = b

    linhas = int(input("Quantas linhas tem seu sistema? "))
    colunas = int(input("Quantas variaveis diferentes(colunas) tem seu sistema? "))
    A = [[int(input(f"Qual elemento da posicao ixj={i}x{j} :  ")) for i in range(colunas)] for j in range(linhas)]
    b = [int(input(f"Qual a respota da linha {i} do sistema: ")) for i in range(1,linhas+1)]

    #aplicação do método de LU 
    inicio = time.perf_counter()
    x = metodo_LU(A, b)
    fim = time.perf_counter()
    print(f'\nResolução do problema usando LU= {x}')
    print(f"Tempo de execução: {fim - inicio:.10f} segundos")
    print(f"O numero de operações:\nFlutuante={operacoes_ponto_flutuante}\nFixo={operacoes_ponto_fixo}\n\n")
    
    
    
    #aplicação do método de Cholesky
    operacoes_ponto_fixo = 0
    operacoes_ponto_flutuante = 0
    inicio = time.perf_counter()
    x = metodo_cholesky(A, b)
    fim = time.perf_counter()
    print(f'Resolução do problema usando Cholesky= {x}')
    print(f"Tempo de execução: {fim - inicio:.10f} segundos")
    print(f"O numero de operações:\nFlutuante={operacoes_ponto_flutuante}\nFixo={operacoes_ponto_fixo}\n\n")    




except ValueError as erro:
    print(f"Erro: {erro}")