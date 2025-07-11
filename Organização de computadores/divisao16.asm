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
JE ERRADO

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

LOOP1:      DATA R0, 0x00
            CMP R1,R0
            JE SEGUNDOVALOR
            DATA R0, 0x0a
            ADD R0, R2
            ADD R3, R1
            JMP LOOP1

UMDIGITO:   MOVE R1, R2
            DATA R1, 0x30
            ADD R1, R2; pois ele vai tirar os 30 denovo
            JMP CONVERSAO 


SEGUNDOVALOR:   MOVE R2, R0
                DATA R3, 0x00
                DATA R2, 0x2f
LOOP2:          IN DATA, R1
                CMP R1, R3
                JE ERRADO
                CMP R1, R2
                JE LOOP2
                DATA R3, 0x01
                DATA R2, 0x30
                NOT R2, R2
                ADD R3, R2
                ADD R2, R1 ; ASCII -> HEXA
                JMP DIVISAO





ERRADO: DATA R0, 0x21
        DATA R1, 0x01
        OUT ADDR, R1
        OUT DATA, R0
        JMP FINAL

DIVISAO: DATA R2, 0x00
         CMP R1, R2
         JE ERRADO
         DATA R3, 0x01 ; valor fixo (complemento de dois e incrementação)

LOOP3:   CMP R1, R0
         JA MONITOR
         NOT R1, R1
         ADD R1, R0
         ADD R3, R0
         NOT R1, R1
         ADD R3, R2
         JMP LOOP3
         

MONITOR: MOVE R2, R0
         DATA R2, 0x09
         DATA R3, 0x0a
         DATA R1, 0x01
         NOT R3, R3
         ADD R1, R3
         DATA R1, 0x00
LOOP4:   CMP R0, R2
         JA DEZENAS
         DATA R2, 0x01
         OUT ADDR, R2
         DATA R3, 0x30
         ADD R3, R1
         ADD R3, R0
         OUT DATA, R1
         OUT DATA, R0
         JMP FINAL



DEZENAS: ADD R3, R0
         DATA R2, 0x01
         ADD R2, R1
         DATA R2, 0x09
         JMP LOOP4

FINAL: HALT
