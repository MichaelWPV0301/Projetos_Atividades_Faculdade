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
    "CLF": "0x6"
}
instrucoes2 = {
    "DATA": "0x2",
    "JMP": "0x40",
}

registradores = {
    "R0" : "00", 
    "R1" : "01",
    "R2" : "10",
    "R3" : "11"
}
instrucoes_hex = []

with open("teste.asm") as arquivo:
    for linha in arquivo:
        linha = linha. replace(",", " ")
        if not linha: continue


        partes = linha.strip().split()
        instrucao = partes[0]
        


        if(instrucao in instrucoes1):
            reg1 = partes[1]    
            reg2 = partes[2]

            regs = registradores[reg1] + registradores[reg2]
            inteiro = int(regs, 2)
            hexaregs = hex(inteiro)
            hexa = instrucoes1[instrucao] + hexaregs[2:]
        
        elif(instrucao in instrucoes2):
            if(instrucao =="DATA"):
                reg = registradores[partes[1]]
                inteiro = int(reg,2)
                hexareg = hex(inteiro)
                hexa = instrucoes2[instrucao] + hexareg[2:]
                instrucoes_hex.append(hexa)
                hexa = partes[2]
            else:
                hexa = instrucoes2[instrucao]
                instrucoes_hex.append(hexa)
                hexa = partes[1]
            


        instrucoes_hex.append(hexa)
    print(instrucoes_hex)