instrucoes1 = {
    "ADD": "0x8",
    "SHR": "0x9",
    "SHL": "0xa",
    "NOT": "0xb",
    "AND": "0xc",
    "OR": "0xd",
    "XOR": "0xe",
    "CMP": "0xf",
    "LD": "0x0",
    "ST": "0x1",
    "JMPR": "0x3",
}
instrucoes2 = {
    "JMP": "0x40",
    "CLF": "0x60",
    "DATA": "0x2",
    "J" : "0x5",
}
outside = {
    "BASE" : "0x7",
    "IN" : "0",
    "OUT" : "1",
    "DATA" : "0",
    "ADDR" : "1" 
}
registradores = {
    "R0" : "00", 
    "R1" : "01",
    "R2" : "10",
    "R3" : "11"
}
jcaez = {
    "C" : "1000",
    "A" : "0100",
    "E" : "0010",
    "Z" : "0001",

}

instrucoes_hex = []

with open("teste.asm") as arquivo:
    for linha in arquivo:
        linha = linha. replace(",", " ")
        if not linha: continue


        partes = linha.strip().split()
        instrucao = partes[0].upper()
        print(instrucao)


        #INSTRUCOES SÓ COM UM BYTE E QUE TÊM DOIS REGISTRADORES
        if(instrucao in instrucoes1):
            reg1 = partes[1].upper()    
            reg2 = partes[2].upper()

            regs = registradores[reg1] + registradores[reg2]
            inteiro = int(regs, 2)
            hexaregs = hex(inteiro)
            hexa = instrucoes1[instrucao] + hexaregs[2:]
        
        elif(instrucao in instrucoes2 or instrucao[0]=="J"):
            #DATA
            if(instrucao =="DATA"):
                reg = registradores[partes[1].upper()]
                inteiro = int(reg,2)
                hexareg = hex(inteiro)
                hexa = instrucoes2[instrucao] + hexareg[2:]
                instrucoes_hex.append(hexa)
                hexa = partes[2]
            
            #JMP e CLF
            elif(instrucao == "JMP" or instrucao == "CLF"):
                hexa = instrucoes2[instrucao]
                if(instrucao == "JMP"):
                    instrucoes_hex.append(hexa)
                    hexa = partes[1]
            
            #JCAEZ
            elif(instrucao[0]=="J"):
                letras = list(instrucao[1:])
                letras = list(letra.upper() for letra in letras)
                letrasBin = sum(int(jcaez[letra],2) for letra in letras)
                hexaLetras = hex(letrasBin)
                hexa = instrucoes2[instrucao[0]] + hexaLetras[2:]
                instrucoes_hex.append(hexa)
                hexa = partes[1]
        
        #Periféricos
        elif(instrucao in outside):
            hexa = outside["BASE"]
            comandos = outside[partes[0].upper()] + outside[partes[1].upper()] + registradores[partes[2].upper()]
            comando = int(comandos, 2)
            comando = hex(comando)
            hexa += comando[2:]
            
        print(partes)
        instrucoes_hex.append(hexa)




    print(instrucoes_hex)