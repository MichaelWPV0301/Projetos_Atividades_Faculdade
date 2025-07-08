; saída inicial
OUT ADDR, R0

; define separador '/'
DATA R0, 0x2F

; ajusta ASCII '0' para valor numérico
DATA R3, 0x30
DATA R2, 0x01
NOT R3, R3
ADD R2, R3

; ~ primeira leitura ~
LER_VALOR1: IN DATA, R1
    CMP R1, R0
    JE FALHA_FORMATO

; ~ possível segundo caractere ~
LER_VALOR2: IN DATA, R2
    CMP R0, R2
    JMP AJUSTAR_NUM

; ~ transforma dois ASCII em número ~
AJUSTAR_NUM: ADD R3, R1
    CMP R2, R0
    JE DIGITO_SOZINHO
    ADD R3, R2
    DATA R0, 0x01
    DATA R3, 0x01
    NOT R3, R3
    ADD R0, R3

MULT10_LOOP: DATA R0, 0x00
    CMP R1, R0
    JE PULAR_BARRA
    DATA R0, 0x0A
    ADD R0, R2
    ADD R3, R1
    JMP MULT10_LOOP

; ~ trata número único ~
DIGITO_SOZINHO: MOVE R1, R2
    DATA R1, 0x30
    ADD R1, R2
    JMP AJUSTAR_NUM

; ~ ignora separador '/' ~
PULAR_BARRA: MOVE R2, R0
    DATA R3, 0x00
    DATA R2, 0x2F
LER_DIVISOR: IN DATA, R1
    CMP R1, R3
    JE FALHA_FORMATO
    CMP R1, R2
    JE LER_DIVISOR
    DATA R2, 0xD0
    ADD R2, R1
    JMP INICIO_DIV

; ~ erro de entrada ~
FALHA_FORMATO: DATA R0, 0x21
    DATA R1, 0x01
    OUT ADDR, R1
    OUT DATA, R0
    JMP FIM_PROG

; ~ divisão sucessiva ~
INICIO_DIV: DATA R2, 0x00
    CMP R1, R2
    JE FALHA_FORMATO
    DATA R3, 0x01

REPETE_SUB: CMP R1, R0
    JA MOSTRAR
    NOT R1, R1
    ADD R1, R0
    ADD R3, R0
    NOT R1, R1
    ADD R3, R2
    JMP REPETE_SUB

; ~ mostra quociente e resto ~
MOSTRAR: MOVE R2, R0
    DATA R2, 0x09
    DATA R3, 0x0A
    DATA R1, 0x01
    NOT R3, R3
    ADD R1, R3
    DATA R1, 0x00

PRINT_LOOP: CMP R0, R2
    JA AJUSTAR_SAIDA
    DATA R2, 0x01
    OUT ADDR, R2
    DATA R3, 0x30
    ADD R3, R1
    ADD R3, R0
    OUT DATA, R1
    OUT DATA, R0
    JMP FIM_PROG

; ~ caso quociente com dois dígitos ~
AJUSTAR_SAIDA: ADD R3, R0
    DATA R2, 0x01
    ADD R2, R1
    DATA R2, 0x09
    JMP PRINT_LOOP

; ~ fim do programa ~
FIM_PROG: HALT
