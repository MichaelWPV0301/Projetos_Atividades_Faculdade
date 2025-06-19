linha = "; comentário 2"
linha = linha.replace(",", " ")
partes = linha.strip().split(";")
partes = partes[0].strip().split()
if(partes):
    print(partes)

