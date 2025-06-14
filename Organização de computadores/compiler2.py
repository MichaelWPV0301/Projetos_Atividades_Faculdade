import sys

# Função para converter strings numéricas com ou sem prefixo (0x, 0b)
def parse_num(val, linha):
    try:
        if val.lower().startswith(("0x", "0b")):
            return int(val, 0)
        return int(val, 10)
    except ValueError:
        print(f"Linha {linha}: valor inválido: {val}")
        sys.exit(1)

# Verifica argumentos
if len(sys.argv) != 3:
    print("Uso: python assembler.py <arquivo_entrada> <arquivo_saida>")
    sys.exit(1)
entrada, saida = sys.argv[1], sys.argv[2]

# Mapeamentos de instruções e códigos
instrucoes1 = {"ADD":"0x8","SHR":"0x9","SHL":"0xa","NOT":"0xb",
               "AND":"0xc","OR":"0xd","XOR":"0xe","CMP":"0xf",
               "LD":"0x0","ST":"0x1"}
instrucoes2 = {"JMP":"0x40","CLF":"0x60","DATA":"0x2","JMPR":"0x3","J":"0x5"}
jcaez = {"C":"1000","A":"0100","E":"0010","Z":"0001"}
registradores = {"R0":"00","R1":"01","R2":"10","R3":"11"}
# Mapeamento de periféricos e direções
outside = {"BASE":"0x7","IN":"0","OUT":"1","DATA":"0","ADDR":"1"}

instrucoes_hex = []
# Leitura do arquivo entrada
try:
    arquivo = open(entrada)
except Exception as e:
    print(f"Erro ao abrir arquivo de entrada: {e}")
    sys.exit(1)

with arquivo:
    for num_linha, linha in enumerate(arquivo, start=1):
        linha = linha.replace(","," ")
        partes = linha.strip().split()
        if not partes or partes[0].startswith(";"):
            continue
        instr = partes[0].upper()
        # 1 byte, 2 regs
        if instr in instrucoes1:
            if len(partes)<3:
                print(f"Linha {num_linha}: {instr} requer 2 registradores")
                sys.exit(1)
            r1,r2 = partes[1].upper(),partes[2].upper()
            if r1 not in registradores or r2 not in registradores:
                print(f"Linha {num_linha}: registrador inválido: {r1} ou {r2}")
                sys.exit(1)
            bits = registradores[r1]+registradores[r2]
            instrucoes_hex.append(instrucoes1[instr]+hex(int(bits,2))[2:])
        # DATA
        elif instr=="DATA":
            if len(partes)<3:
                print(f"Linha {num_linha}: DATA requer registrador e valor")
                sys.exit(1)
            r=partes[1].upper()
            if r not in registradores:
                print(f"Linha {num_linha}: registrador inválido: {r}")
                sys.exit(1)
            # byte1
            byte1 = instrucoes2[instr]+hex(int(registradores[r],2))[2:]
            instrucoes_hex.append(byte1)
            # valor
            raw=partes[2]; num=parse_num(raw,num_linha)
            if not raw.lower().startswith(("0x","0b")) and not (-128<=num<=127):
                print(f"Linha {num_linha}: valor fora do intervalo -128 a 127")
                sys.exit(1)
            if num<0: num=(num+256)&0xFF
            instrucoes_hex.append(f"0x{num:02x}")
        # JMPR
        elif instr=="JMPR":
            if len(partes)<2:
                print(f"Linha {num_linha}: JMPR requer registrador")
                sys.exit(1)
            r=partes[1].upper()
            if r not in registradores:
                print(f"Linha {num_linha}: registrador inválido: {r}")
                sys.exit(1)
            instrucoes_hex.append(instrucoes2[instr]+hex(int(registradores[r],2))[2:])
        # JMP/CLF
        elif instr in ("JMP","CLF"):
            if instr=="CLF": instrucoes_hex.append(instrucoes2[instr])
            else:
                if len(partes)<2:
                    print(f"Linha {num_linha}: JMP requer endereço")
                    sys.exit(1)
                addr=parse_num(partes[1],num_linha)
                if not(0<=addr<=255):
                    print(f"Linha {num_linha}: endereço fora do intervalo 0 a 255")
                    sys.exit(1)
                instrucoes_hex.append(instrucoes2[instr])
                instrucoes_hex.append(f"0x{addr:02x}")
        # JCAEZ
        elif instr.startswith("J") and instr not in ("JMP","JMPR","DATA"):
            if len(partes)<2:
                print(f"Linha {num_linha}: {instr} requer endereço")
                sys.exit(1)
            flags=instr[1:]; bits=0
            for f in flags:
                if f not in jcaez:
                    print(f"Linha {num_linha}: flag inválida: {f}")
                    sys.exit(1)
                bits|=int(jcaez[f],2)
            instrucoes_hex.append(instrucoes2["J"]+hex(bits)[2:])
            addr=parse_num(partes[1],num_linha)
            if not(0<=addr<=255):
                print(f"Linha {num_linha}: endereço fora do intervalo 0 a 255")
                sys.exit(1)
            instrucoes_hex.append(f"0x{addr:02x}")
        # I/O
        elif instr in ("IN","OUT"):
            if len(partes)<3:
                print(f"Linha {num_linha}: {instr} requer tipo de porta e registrador")
                sys.exit(1)
            port=partes[1].upper(); r=partes[2].upper()
            if port not in ("DATA","ADDR") or r not in registradores:
                print(f"Linha {num_linha}: operador I/O inválido: {port}, {r}")
                sys.exit(1)
            cmds=outside[instr]+outside[port]+registradores[r]
            # concatena BASE + hex do comando
            instrucoes_hex.append(outside["BASE"]+hex(int(cmds,2))[2:])
        else:
            print(f"Linha {num_linha}: instrução não reconhecida: {instr}")
            sys.exit(1)
# grava saída
try:
    with open(saida,"w") as f:
        f.write("v3.0 hex words plain\n")
        for c in instrucoes_hex: f.write(f"{c}\n")
except Exception as e:
    print(f"Erro ao escrever arquivo de saída: {e}")
    sys.exit(1)
print(f"Conversão concluída com sucesso. {len(instrucoes_hex)} palavras geradas.")