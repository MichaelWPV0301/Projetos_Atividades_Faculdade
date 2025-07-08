; Exibe endereço inicial
OUT ADDR, R0

; Define o caractere '/' (0x2F) como separador
DATA R0, 0x2F

; Preparação: converte ASCII para valor numérico (−0x30)
DATA R3, 0x30            ; base ASCII '0'
DATA R2, 0x01            ; usado para complemento de dois
NOT R3, R3               ; inverte bits de 0x30
ADD R2, R3               ; R2 agora tem -0x30

; ---------- Leitura do primeiro número (dezena) ----------
LE_DIG1: IN DATA, R1          ; lê primeiro caractere
    CMP R1, R0
    JE ERRO_INPUT        ; se for '/', formato incorreto

; ---------- Leitura do segundo caractere (unidade) ----------
LE_DIG2: IN DATA, R2          ; tenta ler segundo caractere
    CMP R0, R2
    JMP CONVERTE_ASCII   ; se for '/', só 1 dígito

; ---------- Converte dois dígitos ASCII para inteiro ----------
CONVERTE_ASCII: ADD R3, R1           ; converte 1º dígito
    CMP R2, R0
    JE VALOR_UNICO
    ADD R3, R2           ; soma 2º dígito
    DATA R0, 0x01
    DATA R3, 0x01
    NOT R3, R3
    ADD R0, R3

REP_MULTIPLICA10: DATA R0, 0x00
    CMP R1, R0
    JE LE_DIVISOR
    DATA R0, 0x0A
    ADD R0, R2
    ADD R3, R1
    JMP REP_MULTIPLICA10

; ---------- Caso de um único dígito ----------
VALOR_UNICO: MOVE R1, R2
    DATA R1, 0x30
    ADD R1, R2           ; tira o 0x30
    JMP CONVERTE_ASCII

; ---------- Lê valor após o '/' ----------
LE_DIVISOR: MOVE R2, R0
    DATA R3, 0x00
    DATA R2, 0x2F        ; prepara pra pular '/'
BUSCA_DIVISOR: IN DATA, R1
    CMP R1, R3
    JE ERRO_INPUT        ; fim de entrada sem divisor
    CMP R1, R2
    JE BUSCA_DIVISOR     ; pula se ainda for '/'
    DATA R2, 0xD0
    ADD R2, R1           ; converte divisor ASCII p/ número
    JMP EXEC_DIV

; ---------- Mensagem de erro ----------
ERRO_INPUT: DATA R0, 0x21        ; caractere '!'
    DATA R1, 0x01
    OUT ADDR, R1
    OUT DATA, R0
    JMP ENCERRA

; ---------- Realiza divisão por subtrações ----------
EXEC_DIV: DATA R2, 0x00        ; inicializa quociente
    CMP R1, R2
    JE ERRO_INPUT        ; divisão por zero
    DATA R3, 0x01        ; usado como +1 em complemento

DIV_LOOP: CMP R1, R0
    JA MOSTRA_SAIDA
    NOT R1, R1
    ADD R1, R0
    ADD R3, R0
    NOT R1, R1
    ADD R3, R2
    JMP DIV_LOOP

; ---------- Impressão do resultado ----------
MOSTRA_SAIDA: MOVE R2, R0
    DATA R2, 0x09
    DATA R3, 0x0A
    DATA R1, 0x01
    NOT R3, R3
    ADD R1, R3
    DATA R1, 0x00

IMPRIME_LOOP: CMP R0, R2
    JA CONVERTE_DEZ
    DATA R2, 0x01
    OUT ADDR, R2
    DATA R3, 0x30
    ADD R3, R1
    ADD R3, R0
    OUT DATA, R1
    OUT DATA, R0
    JMP ENCERRA

; ---------- Conversão para duas casas ----------
CONVERTE_DEZ: ADD R3, R0
    DATA R2, 0x01
    ADD R2, R1
    DATA R2, 0x09
    JMP IMPRIME_LOOP

; ---------- Fim do programa ----------
ENCERRA: HALT
