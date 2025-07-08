OUT ADDR, R0  ; Configura R0 como o registrador de endereço de saída.

; --- Setup: Constantes e Auxiliar de Conversão ASCII ---
DATA R0, 0x2F    ; R0 armazena o caractere '/' (0x2F).
DATA R3, 0x30    ; R3 carrega ASCII '0' (0x30).
DATA R2, 0x01    ; R2 temporariamente carrega 1.

NOT R3, R3       ; R3 = NOT(R3). (Resultado em R3)
ADD R2, R3       ; R3 = R2 + R3. Agora R3 contém -0x30 (complemento de dois). (Resultado em R3)
                 ; R2 mantém 0x01.

; --- Leitura do Dividendo (Primeiro Número) ---
IN DATA, R1      ; Lê o primeiro caractere (dígito da dezena) para R1.

CMP R1, R0       ; Compara o primeiro dígito (R1) com '/' (R0).
JE INVALID_INPUT ; Salta para o erro se a entrada começar com '/'.

IN DATA, R2      ; Lê o segundo caractere (dígito da unidade ou delimitador) para R2.

JMP PROCESS_DIVIDEND ; Prossegue para processar o valor do dividendo.

; --- Processamento do Valor do Dividendo ---
PROCESS_DIVIDEND: ADD R3, R1 ; R1 = R3 + R1. Converte (R1) deASCII para  numérico. 
                     ; R1 agora contém o dígito da dezena numérico.

    CMP R2, R0       ; Compara o segundo caractere (R2) com '/' (R0).
    JE HANDLE_SINGLE_DIGIT ; Se for '/', o dividendo é de um único dígito.

    ADD R3, R2       ; R2 = R3 + R2. Converte o dígito da unidade (R2) de ASCII para seu valor numérico. (Resultado em R2)
                     ; R2 agora contém o dígito da unidade numérico.

    ; --- Calcular o Valor Verdadeiro do Dividendo (Dezena * 10 + Unidade) ---
    ; R1: Dígito da dezena (será decrementado)
    ; R2: Dígito da unidade (acumulará o valor final)
    ; R0: Usado para 10 e para o 0 de comparação
    ; R3: Usado para -1

    DATA R0, 0x0A    ; R0 carrega 10.
    DATA R3, 0x01    ; R3 temporariamente carrega 1.
    NOT R3, R3       ; R3 = NOT(R3). Agora R3 contém -1. (Resultado em R3)


    ; Precisamos comparar R1 (dezena) com 0.

LOOP_MULTIPLY_TEN: DATA R0, 0x00    ; R0 carrega 0 para a comparação.
    CMP R1, R0       ; Compara o dígito da dezena (R1) com 0 (R0).
    JE END_DIVIDEND_CALC ; Sai do loop se o dígito da dezena for 0.

    DATA R0, 0x0A    ; R0 carrega 10 novamente.
    ADD R0, R2       ; R2 = R0 + R2. Adiciona 10 (R0) ao acumulador da unidade (R2). (Resultado em R2)

    DATA R0, 0x01    ; R0 carrega 1.
    DATA R3, 0x01
    NOT R0, R0       ; R0 = NOT(R0). R0 se torna -1. (Resultado em R0)
    ADD R3, R0
    ADD R0, R1       ; R1 = R0 + R1. Decrementa o dígito da dezena (R1 = R1 - 1). (Resultado em R1)
    JMP LOOP_MULTIPLY_TEN ; Continua o loop.

END_DIVIDEND_CALC: MOVE R2, R0      ; R0 = R2. Move o valor final do dividendo (de R2) para R0. (Destino R0)
    JMP PREPARE_DIVISOR ; Prossegue para preparar a entrada do divisor.

; --- Manipulação de Dividendo de Um Dígito ---
HANDLE_SINGLE_DIGIT: MOVE R1, R0      ; R0 = R1. Move o dígito único (de R1) para R0. (Destino R0)
    JMP PREPARE_DIVISOR ; Prossegue para preparar a entrada do divisor.

; --- Preparar e Ler Divisor ---
PREPARE_DIVISOR: DATA R3, 0x30    ; R3 carrega ASCII '0'.
    DATA R2, 0x01    ; R2 carrega 1.
    NOT R3, R3       ; R3 = NOT(R3).
    ADD R2, R3       ; R3 = R2 + R3. R3 agora contém -0x30 (para conversão ASCII do divisor). (Resultado em R3)
                     ; R2 é 0x01.


LOOP_READ_DIVISOR: IN DATA, R1      ; Lê o caractere do divisor para R1.

    DATA R2, 0x00    ; R2 temporariamente contém 0 para comparação.
    CMP R1, R2       ; Compara o divisor (R1) com 0 (R2).
    JE INVALID_INPUT ; Erro se o divisor for 0.

    DATA R2, 0x2F    ; R0 carrega '/' para comparação.    
    CMP R1, R2       ; Compara o divisor (R1) com '/' (R0).
    JE LOOP_READ_DIVISOR ; Ignora '/' se lido como divisor, lê novamente.

    ADD R3, R1       ; R1 = R3 + R1. Converte o divisor (R1) de ASCII para seu valor numérico. (Resultado em R1)
    MOVE R1, R2      ; R2 = R1. Move o divisor convertido (de R1) para R2. (Destino R2)
    JMP START_DIVISION ; Inicia o processo de divisão.

; --- Manipulador de Erro ---
INVALID_INPUT: DATA R0, 0x21    ; R0 = '!' (caractere de erro).
    DATA R1, 0x01    ; R1 = endereço de saída para o monitor.
    OUT ADDR, R1
    OUT DATA, R0     ; Exibe o caractere de erro.
    JMP END_PROGRAM

; --- Divisão por Subtrações Sucessivas ---
START_DIVISION: DATA R3, 0x00    ; R3 = 0 (este registrador armazenará o quociente).
    CMP R2, R3       ; Verifica se o divisor (R2) é zero (R3).
    JE INVALID_INPUT ; Erro se o divisor for zero.

    DATA R1, 0x01    ; R1 = 1 (para incrementar o quociente).

LOOP_DIVISION: CMP R2, R0       ; Compara dividendo (R0) com divisor (R2).
    JA DISPLAY_RESULT ; Se dividendo < divisor, a divisão está completa.

    ; Realiza subtração (R0 = R0 - R2) usando complemento de dois
    NOT R2, R2       ; R2 = NOT(R2). (Resultado em R2)
    ADD R2, R0       ; R0 = R2 + R0. (R0 = R0 - divisor). (Resultado em R0)
    DATA R1, 0x01    ; R1 carrega 1.
    ADD R1, R0       ; R0 = R1 + R0. (R0 = R0 + 1 para completar o complemento de dois). (Resultado em R0)

    ADD R1, R3       ; R3 = R1 + R3. Incrementa o quociente (R3). (Resultado em R3)
    NOT R2, R2
    JMP LOOP_DIVISION ; Continua o loop.

; --- Exibição do Resultado ---
DISPLAY_RESULT: MOVE R3, R0      ; R0 = R3. Move o quociente (de R3) para R0. (Destino R0)

    DATA R3, 0x00    ; R3 = 0 (contador de dezenas para a saída).
    DATA R1, 0x09    ; R1 = 9 (limite para dígito único na saída).
    DATA R2, 0x0A    ; R2 = 10 (para decompor o resultado em dígitos).

LOOP_DISPLAY: CMP R0, R1       ; Compara o quociente (R0) com 9 (R1).
    JA ADJUST_TENS ; Se o quociente > 9, ele tem dezenas.

    ; Saída do resultado: (Dígito da dezena) (Dígito da unidade)
    DATA R1, 0x01    ; R1 = endereço de saída para o monitor.
    OUT ADDR, R1

    DATA R1, 0x30    ; R0 carrega ASCII '0'.
    ADD R1, R3       ; R3 = R3 + R1. Agora R1 contém contador de dezenas (R3). (Resultado em R3)
    OUT DATA, R3     ; Exibe o dígito da dezena.

    ADD R1, R0       ; R0 = R0 + R1. (Assumindo R0 tem o dígito da unidade original)
    OUT DATA, R0     ; Exibe o dígito da unidade.
    JMP END_PROGRAM

ADJUST_TENS: DATA R1, 0x01    ; R1 carrega 1
    NOT R2, R2       ; R2 = NOT(R2). R2 agora é -10. (Resultado em R2)
    ADD R1, R2
    ADD R2, R0       ; R0 = R2 + R0. R0 = R0 - 10 (reduz o quociente). (Resultado em R0)
    ADD R1, R3       ; R3 = R1 + R3. Incrementa o contador de dezenas (R3). (Resultado em R3)
    DATA R1, 0x09    ; R1 restaura 9.
    JMP LOOP_DISPLAY ; Continua o loop de exibição.

; --- Terminação do Programa ---
END_PROGRAM: HALT            ; Interrompe a execução.