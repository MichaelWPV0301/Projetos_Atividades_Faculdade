def multmatriz(matA, matB):
    matR = []
    for i in range(len(matA)):
        lista = []
        for k in range(len(matB[0])):
            soma = 0
            for j in range(len(matA[0])):
                soma += matA[i][j] * matB[j][k]
            lista.append(soma)
        matR.append(lista)
    return matR

def multmatrizB(matA, matB):

    linhasA, colunasA= len(matA), len(matA[0])
    linhasB, colunasB = len(matB), len(matB[0])

    result = [[0] * colunasB for _ in range(linhasA)]

    for i in range(linhasA):
        Ai = matA[i]
        Ci = result[i]
        for k in range(colunasA):
            Aik = Ai[k]
            Bk = matB[k]
            for j in range(linhasB):
                Ci[j] += Aik * Bk[j]
    
    return result

print(multmatrizB([[1,3]],[[5,4],[3,2]]))