OUT ADDR,R0
DATA R0, 0x2f; 0x2f="/"

; "-0x30" PARA CONVERTER ASCII -> HEXA
DATA R3, 0x30; para subtrair
DATA R2, 0x01; somar um do complemento de dois
NOT R3,R3; negação do 0x30
ADD R2, R3


; DEZENA(PRIMEIRO VALOR)
IN DATA,R1 
CMP R1,R0
JE FINAL

; UNIDADE(SE EXISTIR NO SEGUNUDO VALOR)
IN DATA, R2
CMP R0, R2
JMP CONVERSAO ; NUMERO COM DOIS ALGARISMOS, ASCII -> HEXA



CONVERSAO:  ADD R3, R1
            CMP R2, R0
            JE UMDIGITO
            ADD R3, R2
            DATA R0, 0x01
            DATA R3, 0x01
            NOT R3,R3
            ADD R0, R3

LOOP1:       DATA R0, 0x00
            CMP R1,R0
            JE SEGUNDOVALOR
            DATA R0, 0x0a
            ADD R0, R2
            ADD R3, R1
            JMP LOOP

UMDIGITO:   MOVE R1, R2
            DATA R1, 0x30
            ADD R1, R2; pois ele vai tirar os 30 denovo
            JMP CONVERSAO 


SEGUNDOVALOR:   MOVE R2, R0
                DATA R2, 0x2f
                IN DATA, R1
                CMP R2, R1
                JA DIVISAO
                IN DATA, R1; Oque o teclado passa quando nao tem nada?
                JMP DIVISAO


FINAL: HALT

