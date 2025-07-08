; INSTRUÇÕES INICAIS
DATA R1, 0X00
OUT ADDR,R1
DATA R0, 0x2f; 0x2f="/"
DATA R2, 0x30; para subtrair
DATA R3, 0x01; somar um do complemento de dois
NOT R2,R2; negação do 0x30
ADD R2, R3
IN DATA,R1  
CMP R1,R0
JE INVALID
IN DATA, R2
CMP R0, R2
JMP FIRST 




;CONJUNTO DE INSTRUÇÕES QUE CONVERTE NUMEROS EM ASCII COM DOIS DIGITOS PARA HEXADECIMAL
FIRST:      ADD R3, R1
            CMP R2, R0
            JE ONLYUNIT
            ADD R3, R2
            DATA R0, 0x01
            DATA R3, 0x01
            NOT R3,R3
            ADD R0, R3
FIRST1:         DATA R0, 0x00
                CMP R1,R0
                JE SECOND
                DATA R0, 0x0a
                ADD R0, R2
                ADD R3, R1
                JMP FIRST1
ONLYUNIT:       MOVE R1, R2
                DATA R1, 0x30
                ADD R1, R2; pois ele vai tirar os 30 denovo
                JMP FIRST 







;CONJUNTO DE INSTRUÇÕES QUE CONVERTE NUMEROS EM ASCII COM UM DIGITO PARA HEXADECIMAL
SECOND:         MOVE R2, R0
                DATA R2, 0x00
                DATA R3, 0x2f
SECOND1:        IN DATA, R1
                CMP R1, R2
                JE INVALID
                CMP R1, R3
                JE SECOND1
                DATA R2, 0xd0
                ADD R2, R1
                JMP DIVISION




;CONJUNTO DE INSTRUÇÕES CASO FORNEÇA UMA DIVISAO ERRADA
INVALID:  DATA R3, 0x01
          OUT ADDR, R3
          DATA R0, 0x49
          OUT DATA, R0
          DATA R0, 0x4E
          OUT DATA, R0
          DATA R0, 0x56
          OUT DATA, R0
          DATA R0, 0x41
          OUT DATA, R0
          DATA R0, 0x4C
          OUT DATA, R0
          DATA R0, 0x49
          OUT DATA, R0
          DATA R0, 0x44
          OUT DATA, R0
          DATA R0, 0x4F
          OUT DATA, R0
          JMP END






;CONJUNTO DE INSTRUÇÕES RESPONSAVEIS PELA DIVISAO COM SUBTRAÇÕES SUCESSIVAS
DIVISION: DATA R2, 0x00
          CMP R1, R2
          JE INVALID
          DATA R3, 0x01 ; valor fixo (complemento de dois e incrementação)
DIVISION1:      CMP R1, R0
                JA MONITOR
                NOT R1, R1
                ADD R1, R0
                ADD R3, R0
                NOT R1, R1
                ADD R3, R2
                JMP DIVISION1
         



; CONJUNTO DE INSTRUÇÕES RESPONSAVEIS POR MOSTRAR NO DISPLAY
MONITOR:        MOVE R2, R0
                DATA R2, 0x09
                DATA R3, 0x0a
                DATA R1, 0x01
                NOT R3, R3
                ADD R1, R3
                DATA R1, 0x00
TENS1:          CMP R0, R2
                JA TENS
                DATA R2, 0x01
                OUT ADDR, R2
                DATA R3, 0x30
                ADD R3, R1
                ADD R3, R0
                OUT DATA, R1
                OUT DATA, R0
                JMP END
;CONJUNTO DE INSTRUÇÕES RESPONSAVEIS PELO ALGORISMO DA DEZENA DO RESULTADO FINAL
TENS:   ADD R3, R0
        DATA R2, 0x01
        ADD R2, R1
        DATA R2, 0x09
        JMP TENS1


END: HALT
