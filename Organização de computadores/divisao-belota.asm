; Configura a porta de saída padrão para o dispositivo de exibição
OUT ADDR, R0

; Define o valor do separador de entrada (caractere '/')
DATA R0, 0x2F ; Constante: Caractere barra (/) para delimitação de entrada

; Inicializa o registrador auxiliar para conversão de ASCII para binário
DATA R3, 0x30 ; Valor ASCII do dígito zero ('0')
DATA R2, 0x01 ; Constante: Unidade (para operações de complemento de dois)
NOT R3, R3    ; Calcula o complemento de um de 0x30
ADD R2, R3    ; Finaliza o complemento de dois (resulta em -0x30)

; === Processamento do Primeiro Componente Numérico ===
IN DATA, R1 ; Obtém o primeiro caractere da entrada (alta ordem ou único dígito)

; Valida o primeiro caractere de entrada
CMP R1, R0  ; Compara o caractere lido com o delimitador
JE ERRO_DE_SINAL ; Desvia se o caractere for um delimitador inesperado

; === Processamento do Segundo Componente Numérico ===
IN DATA, R2 ; Obtém o segundo caractere da entrada (baixa ordem ou delimitador)

; Inicia a rotina de ajuste de valor binário
JMP PREPARAR_VALOR

; === Rotina de Preparação de Valores Numéricos ===
PREPARAR_VALOR:
    ; Converte o primeiro componente (R1) de ASCII para seu valor binário
    ADD R3, R1 ; Subtrai 0x30 (R3 = -0x30) de R1

    ; Determina a quantidade de dígitos no valor
    CMP R2, R0 ; Compara o segundo componente (R2) com o delimitador (R0)
    JE VALOR_SIMPLES ; Se o segundo componente é o delimitador, trata como valor de um dígito

    ; Se a execução chega aqui, o valor possui dois dígitos
    ADD R3, R2 ; Converte o segundo componente (R2) de ASCII para seu valor binário (R2 = R2 - 0x30)

    ; Prepara registradores para cálculo de valor composto (dezena * 10)
    DATA R0, 0x01 ; Define R0 como unidade (temporário)
    DATA R3, 0x01 ; Define R3 como unidade (temporário)
    NOT R3, R3    ; Converte R3 para -1
    ADD R0, R3    ; Define R0 como zero (1 + (-1))

; === Ciclo para Acumulação de Dezenas ===
CICLO_DEZENA_ACUMULACAO:
    DATA R0, 0x00 ; Zera R0 para a condição de parada do ciclo
    CMP R1, R0    ; Compara o primeiro componente (dezena) com zero
    JE AVANCAR_PARA_SEGUNDO_VALOR ; Termina o ciclo se a dezena é zero

    DATA R0, 0x0A ; Carrega a constante dez (10) em R0
    ADD R0, R2    ; Adiciona 10 ao acumulador (R2)
    ADD R3, R1    ; Decrementa o primeiro componente (dezena) em R1 (R1 = R1 - 1, já que R3 é -1)
    JMP CICLO_DEZENA_ACUMULACAO

; === Tratamento de Valores Simples (Um Dígito) ===
VALOR_SIMPLES:
    MOVE R1, R2   ; Move o valor do segundo componente (R2) para R1 (destino final)
    DATA R1, 0x30 ; Carrega ASCII '0' em R1 (NOTA: Isso parece um erro lógico. Pode sobrescrever o valor numérico.)
    ADD R1, R2    ; Ajusta R1 (pode ser redundante ou incorreto)
    JMP PREPARAR_VALOR ; Retorna ao início da rotina de preparação (CUIDADO: risco de loop!)

; === Preparação para a Próxima Fase (Leitura do Divisor) ===
AVANCAR_PARA_SEGUNDO_VALOR:
    MOVE R2, R0   ; Move o valor acumulado (dezena * 10) para R2
    DATA R3, 0x00 ; Zera R3 para uso posterior

    ; Recarrega o delimitador em R2 para a próxima comparação de entrada
    DATA R2, 0x2F

CICLO_LEITURA_DIVISOR:
    IN DATA, R1   ; Obtém o caractere do divisor
    CMP R1, R3    ; Verifica se o divisor é inválido (zero ASCII ou outro erro)
    JE ERRO_DE_SINAL

    CMP R1, R2    ; Compara o divisor com o caractere delimitador ('/')
    JE CICLO_LEITURA_DIVISOR ; Ignora o delimitador e continua lendo se encontrar

    DATA R2, 0xD0 ; Constante para ajustar ASCII para binário (é equivalente a -0x30)
    ADD R2, R1    ; Converte o divisor (R1) de ASCII para binário (R1 = R1 - 0x30)
    JMP INICIAR_OPERACAO

; === Rotina de Manipulação de Erros de Entrada ===
ERRO_DE_SINAL:
    DATA R0, 0x21 ; Caractere '!' para indicar erro
    DATA R1, 0x01 ; Endereço de memória para exibição no monitor
    OUT ADDR, R1
    OUT DATA, R0
    JMP FINALIZAR_EXECUCAO

; === Rotina Principal de Divisão por Subtração ===
INICIAR_OPERACAO:
    DATA R2, 0x00 ; Inicializa o registrador para o quociente (começa em zero)
    CMP R1, R2    ; Verifica se o divisor (R1) é zero
    JE ERRO_DE_SINAL ; Desvia para erro se a divisão for por zero

    DATA R3, 0x01 ; Constante auxiliar (para incremento de quociente)

CICLO_DE_DIVISAO:
    CMP R1, R0    ; Compara o dividendo (R1) com o divisor (R0)
    JA APRESENTAR_RESULTADO ; Se dividendo for menor, a divisão está completa

    ; Realiza a operação de subtração (Dividendo = Dividendo - Divisor)
    NOT R1, R1    ; Calcula o complemento de um do dividendo (R1)
    ADD R1, R0    ; Adiciona o divisor (R0) ao complemento de um do dividendo
                  ; NOTA: Esta sequência (NOT R1, R1; ADD R1, R0) não resulta diretamente em R1 - R0.
                  ; Para R1 = R1 - R0, seria R1 + (~R0 + 1). O divisor (R0) está sendo usado aqui sem ser negativado.
                  ; Isso é um ponto crítico que pode causar loops infinitos.

    ADD R3, R0    ; Incrementa o quociente (NOTA: R0 ainda é o divisor. Isso pode sobrescrevê-lo.)
    NOT R1, R1    ; Inverte R1 novamente (provavelmente para tentar restaurá-lo)
    ADD R3, R2    ; Adiciona o quociente (R3) ao valor zero (R2) (NOTA: Lógica confusa, R2 é quociente?)
    JMP CICLO_DE_DIVISAO

; === Rotina de Apresentação de Resultado ===
APRESENTAR_RESULTADO:
    MOVE R2, R0   ; Move o quociente (que deveria estar em R0) para R2
    DATA R2, 0x09 ; Define o valor limite para dezenas (9)
    DATA R3, 0x0A ; Constante: Dez (10) para cálculos de dezena/unidade
    DATA R1, 0x01 ; Endereço de memória para saída

    NOT R3, R3    ; Converte R3 para -10
    ADD R1, R3    ; Subtrai 10 do endereço do monitor (R1). (NOTA: Isso é um erro. R1 deve ser o contador de dezenas.)
    DATA R1, 0x00 ; Zera R1 (deve ser o contador de dezenas para exibição)

CICLO_EXIBICAO:
    CMP R0, R2    ; Compara o quociente (R0) com o limite de dezena (9 em R2)
    JA PROCESSAR_DEZENAS ; Se quociente > 9, há dezenas para exibir

    DATA R2, 0x01 ; Define o endereço de saída para o monitor
    OUT ADDR, R2
    DATA R3, 0x30 ; Carrega ASCII '0'
    ADD R3, R1    ; Adiciona o contador de dezenas (R1) ao ASCII '0' (gera caractere da dezena)
    ADD R3, R0    ; Adiciona a unidade do quociente (R0) ao ASCII '0' (gera caractere da unidade)
    OUT DATA, R1  ; Exibe o caractere da dezena (se houver)
    OUT DATA, R0  ; Exibe o caractere da unidade
    JMP FINALIZAR_EXECUCAO

PROCESSAR_DEZENAS:
    ADD R3, R0    ; Reduz o quociente (R0) em 10 (R3 é -10)
    DATA R2, 0x01 ; Define R2 como unidade
    ADD R2, R1    ; Incrementa o contador de dezenas (R1)
    DATA R2, 0x09 ; Restaura R2 para 9
    JMP CICLO_EXIBICAO

; === Fim da Execução do Programa ===
FINALIZAR_EXECUCAO:
    HALT ; Interrompe o processador