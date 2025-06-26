#Nome: Michael Willian Pereira Vieira; Matricula: 22400829;
import sys
entrada = sys.argv[1] #verifica o arquivo de entrada especificado no terminal
saida = sys.argv[2]  #verifica o arquivo de saida especificado no terminal

instrucoes1 = {"ADD": "0x8","SHR": "0x9","SHL": "0xa","NOT": "0xb","AND": "0xc","OR": "0xd","XOR": "0xe","CMP": "0xf","LD": "0x0","ST": "0x1"}
instrucoes2 = {"JMP": "0x40","CLF": "0x60","DATA": "0x2","JMPR": "0x3","J" : "0x5"}
outside = {"BASE" : "0x7","IN" : "0","OUT" : "1","DATA" : "0","ADDR" : "1" }
registradores = {"R0" : "00", "R1" : "01","R2" : "10","R3" : "11"}
jcaez = {"C" : "1000","A" : "0100","E" : "0010","Z" : "0001"}

instrucoes_hex = [] #TODAS OS VALORES EM HEXADECIMAL QUE TEM QUE ESTÁ NO .txt   
label = {}
with open(entrada) as arquivo:
    endereco = 0
    for linha in arquivo:
        linha = linha. replace(",", " ") #COLOCA ESPAÇO NO LUGAR DE VIRGULAS PARA FAZER O SPLIT()
        if not linha: continue

        partes = linha.strip().split(';') #SEPARA EM DUAS PARTES, A PRIMEIRA É TUDO QUE VEM ANTES DO COMENTARIO E OUTRA DEPOIS
        partes = partes[0].strip().split()
        #INSTRUCOES SÓ COM UM BYTE E QUE TÊM DOIS REGISTRADORES
        if(partes): #verifica se é uma linha de comentário ou se têm algo na linha

            print(partes)
            if(":" in partes[0]):
                label[partes[0]] = f"0x{endereco:02x}"
                partes = partes[1:]


            instrucao = partes[0].upper() #TRANSFORMA A INSTRUÇÃO(SEMPRE PRIMEIRA PARTE) TODA EM MAISCULA
            print(instrucao)
            if(instrucao in instrucoes1): #CASO DE INSTRUÇÕES QUE VÃO TER RARB NOS ULTIMOS 4 BITS
                reg1 = partes[1].upper() #TRANSFORMA RA TODA EM MAISCULA PARA PROCURA NO SET
                reg2 = partes[2].upper()

                regs = registradores[reg1] + registradores[reg2] #CONCATENA RARB DE ACORDO COM O SET POIS OS DOIS SÃO STRINGS
                inteiro = int(regs, 2) #FASE DE CONVERTER A PARTE DOS REGISTRADORES EM HEXADECIMAL
                hexaregs = hex(inteiro)
                hexa = instrucoes1[instrucao] + hexaregs[2:] #CONCATENA O HEXA DA INSTRUÇÃO COM O DO REGISTRADORES
            
            elif(instrucao in instrucoes2 or instrucao[0]=="J"): #VERIFICA SE É UMA INSTRUÇÃO QUE LEVA DOIS BYTES(SET ESPECIFICO)
                #DATA e JMPR
                if(instrucao =="DATA" or instrucao == "JMPR"): #INSTRUÇÕES QUE LEVAM DOIS BYTES E CONSIDERAM RX
                    reg = registradores[partes[1].upper()] #PARTE DO REGISTRADOR DESSAS FUNÇÕES
                    inteiro = int(reg,2) #CONVERTE O BIN DO REGISTRADOR PARA HEXA
                    hexareg = hex(inteiro)
                    hexa = instrucoes2[instrucao] + hexareg[2:] #CONCATENA O HEXA DA INSTRUÇÃO COM O DO REGISTRADORES
                    if(instrucao =="DATA"): #CASO ESPECIFICO DATA: VERIFICA SE O ADDR ESTÁ ENTRE -128 E 127
                        instrucoes_hex.append(hexa) #JÁ COLOCA O HEXA DO PRIMEIRO BYTE DENTRO DA LISTA
                        endereco += 1
                        hexa = partes[2] #SEGUNDO BYTE DA INSTRUÇÃO
                        try: #TRATAMENTO PARA VER SE É UUUM VALOR QUE PODE SER ACEITO PARA O DATA
                            if("x" not in hexa and "b" not in hexa): #VERIFICA SE É DECIMAL
                                hexa = int(hexa) #CASO FOR DECIMAL A FUNÇÃO INT(HEXA, 0) NÃO FUNCIONA
                                if(hexa>127 or hexa<-128): #VERIFICA O INTERVALO DO ADDR
                                    print("Erro: valor fora do intervalo permitido (-128 a 127)")
                                    break
                            else:
                                hexa = int(hexa, 0) #CASO FOR BINARIO, SÓ CONVERTE PARA INT() PARA NÃO TER CONFLITO
                        except ValueError: #TRATAMENTO
                            print("Erro: valor inválido, não é um número inteiro")
                            break
                        
                        if( '-' in str(hexa)): #COMPLEMENTO DE DOIS SE FOR UM ADDR NEGATIVO
                            hexa = f"{hexa:09b}" #CONVERTE PARA BINARIO COM 8 BITS
                            hexa = "".join("1" if b=="0" else "0" for b in hexa if b!='-') #NOT DO BINÁRIO
                            hexa = int(hexa, 2) + 1 #SOMA MAIS UM, PARTE DO PROCESSO DO COMPLEMENTO DE 2

                        hexa = f"0x{hexa:02x}" #CONVERTE PARA HEXADECIMAL
                    
                #JMP e CLF
                elif(instrucao == "JMP" or instrucao == "CLF"):#PRIMEIRA PARTE EM HEXA NÃO MUDA(JMP: 0X40; CLF: 0X60)
                    hexa = instrucoes2[instrucao]#COLOCA A PRIMEIRA PARTE  HEXA DA INSTRUÇÃO QUE JA É ESTABELECIDA
                    if(instrucao == "JMP"): #CASO ESPECIFICO JMP: ADDR ENTRE 0 E 255
                        instrucoes_hex.append(hexa) #COLOCA A PRIMEIRA PARTE EM HEXA DENTRO DA LISTA QUE SERA CONVERTIDA
                        endereco += 1
                        hexa = partes[1] #SEGUNDO BYTE DO JMP
                        try: #TESTE PARA VER SE O VALOR DO ENDEREÇO ESTÁ ENTRE 0 E 255;
                            hexa = int(hexa, 0) #CONVERTE PARA INT SE TIVER EM STRING DE BINARIO OU HEXA
                            if(hexa<0 or hexa>255): #VERIFICA O INTERVALO
                                print("Erro: valor fora do intervalo permitido (0 a 255)")
                                break
                            hexa = hex(hexa) #CONVERTE PARA HEXA NOVAMENTE 
                        except: #Valores inválidos
                            instrucoes_hex.append(hexa) #ADICIONA A INSTRUÇÃO NA LISTA(CASOS DE 2 BYTES ELE ADICIONA O SEGUNDO BYTE)
                            endereco += 1
                            continue
                
                #JCAEZ
                elif(instrucao[0]=="J"): #CASO JCAEZ NO CASO SÓ VERIFICA SE TÊM JOTA CASO NÃO SEJA JMP OU JMPR
                    letras = list(instrucao[1:])#TRANFORMA AS LETRAS(CAEZ) EM UMA LISTA, CADA ELEMENTO É UMA LETRA
                    letras = list(letra.upper() for letra in letras) #TRANSFORMA EM MAISCULA, EVITAR CONFLITO
                    letrasBin = sum(int(jcaez[letra],2) for letra in letras) #FAZ A SOMA DAS LETRAS EM BINARIO DE ACORDO COM O SET DOS CAEZ
                    hexaLetras = hex(letrasBin) #TRANSFORMA EM HEXA
                    hexa = instrucoes2[instrucao[0]] + hexaLetras[2:] #CONCATENA O HEXA DAS LETRAS COM O DA INSTRU
                    instrucoes_hex.append(hexa) #ADICIONA O PRIMEIRA BYTE DA INSTRUÇÃO
                    endereco += 1
                    hexa = partes[1] #PARTE DO SEGUNDO BYTE DO JCAEZ
                    try: #VERIFICAÇÃO DO INTERVALO DO ENDEREÇO DADO
                        hexa = int(hexa, 0) #CONVERTE PARA INT PARA FAZER COMPARAÇÃO
                        if(hexa>255 or hexa<0): #VERIFICA INTERVALO
                            print("Erro: valor fora do intervalo permitido (0 a 255)")
                            break
                        hexa = f"0x{hexa:02x}" #CONVERTE PARA STRING DE HEXA NOVAMENTE
                    except: #Valores inválidos
                        instrucoes_hex.append(hexa) #ADICIONA A INSTRUÇÃO NA LISTA(CASOS DE 2 BYTES ELE ADICIONA O SEGUNDO BYTE)
                        endereco += 1
                        continue

            
            #Periféricos
            elif(instrucao in outside): #INSTRUÇÕES DE PERIFÉRICOS
                hexa = outside["BASE"] #TODA INSTRUÇÃO DE PERIFÉRICO COMEÇA COM 0X7(BASE)
                comandos = outside[partes[0].upper()] + outside[partes[1].upper()] + registradores[partes[2].upper()] #CADA ELEMENTO DA INSTRUÇÃO ESTÃO EM UMA LISTA SEPARADOS, PORTANTO SÓ VERIFICA E CONCATENA OS BITS CORRESPONDENTES.
                comando = int(comandos, 2) #CONVERTE A STRING FORMADA EM BINARIO  EM INT() 
                comando = hex(comando) #CONVERTE EM HEXADECIMAL
                hexa += comando[2:] #SÓ CONCATENA O 0X7 COM A PARTE DA INTRUÇÃO ESPECIFICADA.
            else:
                if(instrucao == 'MOVE'):
                    reg1 = partes[1].upper() #TRANSFORMA RA TODA EM MAISCULA PARA PROCURA NO SET
                    reg2 = partes[2].upper()

                    regs = registradores[reg2] + registradores[reg1] #CONCATENA RA RB DE ACORDO COM O SET POIS OS DOIS INVERTIDO, EXEMPLO: MOVE RA,RB-> REGS = BIN(RB) + BIN(RA)
                    inteiro = int(regs, 2) #FASE DE CONVERTER A PARTE DOS REGISTRADORES EM HEXADECIMAL
                    hexaregs = hex(inteiro)
                    hexa = instrucoes1['XOR'] + hexaregs[2:] #CONCATENA O HEXA DA INSTRUÇÃO COM O DO REGISTRADORES
                    instrucoes_hex.append(hexa) #ADICIONA A PRIMEIRA INSTRUÇÃO XOR RB,RA
                    endereco += 1
                    regs = registradores[reg1] + registradores[reg2] #CONCATENA RA RB DE ACORDO COM O SET POIS OS DOIS NORMAL, EXEMPLO: MOVE RA,RB-> REGS = BIN(RA) + BIN(RB)
                    inteiro = int(regs, 2) #FASE DE CONVERTER A PARTE DOS REGISTRADORES EM HEXADECIMAL
                    hexaregs = hex(inteiro)
                    hexa = instrucoes1['XOR'] + hexaregs[2:] #CONCATENA O HEXA DA INSTRUÇÃO COM O DO REGISTRADORES
                    instrucoes_hex.append(hexa) #ADICIONA A PRIMEIRA INSTRUÇÃO XOR RB,RA
                    endereco += 1
                    continue
                elif(instrucao == 'CLR'):
                    reg = registradores[partes[1].upper()]
                    inteiro = int(reg,2) #CONVERTE O BIN DO REGISTRADOR PARA HEXA
                    hexareg = hex(inteiro)
                    hexa = "0x2" + hexareg[2:] #CONCATENA O HEXA DA INSTRUÇÃO COM O DO REGISTRADORES
                    instrucoes_hex.append(hexa)
                    endereco += 1
                    hexa = '0x00'
                elif(instrucao == 'HALT'):
                    hexa = instrucoes2['JMP']
                    instrucoes_hex.append(hexa) #COLOCA A PRIMEIRA PARTE EM HEXA DENTRO DA LISTA QUE SERA CONVERTIDA
                    endereco += 1
                    if(endereco<=255):
                        instrucoes_hex.append(f"0x{endereco:02x}")
                        endereco += 1
                        continue
                    else:
                        print("Erro: valor fora do intervalo permitido (0 a 255)")
                        break

                        


            print(partes)
            print(hexa)
            instrucoes_hex.append(hexa) #ADICIONA A INSTRUÇÃO NA LISTA(CASOS DE 2 BYTES ELE ADICIONA O SEGUNDO BYTE)
            endereco += 1
            print(endereco)
            print(label)

print(instrucoes_hex)
with open(saida, "w") as f: #ABRE O ARQUIVO DE TXT DE SAÍDA
    f.write("v3.0 hex words plain\n")#EXIGIDO PELO LOGISIM
    for hexa in instrucoes_hex:#TRANSFORMA A LISTA FORMA EM LINHAS NO .txt
        if('0x' not in hexa):
            hexa = label[f'{hexa}:']
        f.write(f"{hexa}\n")
