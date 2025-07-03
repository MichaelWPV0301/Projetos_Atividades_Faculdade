def converte_hexadecimal(valor):
    # Se for um número inteiro, converte para string
    if isinstance(valor, int):
        valor = str(valor)

    try:   
        # Converte para decimal
        decimal = int(valor, 0)
    except ValueError:
        raise ValueError("Formato inválido. Use binário (0b...), hexadecimal (0x...), ou decimal.")
    
    # Converte para hexadecimal (sem o prefixo '0x') e retorna em minúsculas
    hexadecimal = f"{decimal:02x}"
    return hexadecimal

def complemento_de_dois(valor):
    # if '-' in str(valor):  Se valor negativo, aplica complemento de dois
    if( "x" not in valor and "b" not in valor):
        valor = int(valor)
    else:
        valor = int(valor, 0)
    valor = f"{valor:09b}"
    valor = "".join("1" if b == "0" else "0" for b in valor if b != '-')
    valor = int(valor, 2) + 1
    return  f"0x{valor:02x}"


def verifica_intervalo_data(hexa):
    try:
        if "x" not in hexa and "b" not in hexa:
            hexa = int(hexa)  # Trata decimal puro
            if hexa > 127 or hexa < -128:
                return 0
        else:
            hexa = int(hexa, 0)  # Converte bin/hex str -> int
            if(hexa>255):
                return 0
        return 1
    except ValueError:
        return 0
    

if(verifica_intervalo_data(x)):
    if("-" in x):
        x = complemento_de_dois(x)
    x = "0x" + converte_hexadecimal(x)
    print(x)
else:
    print("Erro no valor colocado no Data")


 
