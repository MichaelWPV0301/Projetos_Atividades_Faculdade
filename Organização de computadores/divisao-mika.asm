OUT ADDR, R0
    ; Configura o registrador de endereco de saida para o dispositivo padrao.

DATA R0, 0x2F
    ; Define um byte de controle, que representa o caractere '/'.

DATA R3, 0x30
    ; Carrega o valor ASCII do digito '0' para manipulacao.
DATA R2, 0x01
    ; Define uma constante unitaria.
NOT R3, R3
    ; Executa o complemento de um do valor em R3.
ADD R2, R3
    ; Conclui o complemento de dois, resultando em -0x30.

; === ESTAGIO DE CAPTURA DO DADO INICIAL ===
IN DATA, R1
    ; Obtem o primeiro caractere da sequencia de entrada.

CMP R1, R0
    ; Compara o caractere capturado com o byte de controle.
JE ROTA_DE_ERRO
    ; Desvia se o primeiro caractere for o byte de controle.

; === ESTAGIO DE CAPTURA DO DADO SECUNDARIO ===
IN DATA, R2
    ; Obtem o segundo caractere da sequencia de entrada.

JMP PROCESSO_DE_VALORES
    ; Inicia a sequencia de ajuste dos valores de entrada.

; === FLUXO DE PROCESSAMENTO DE VALORES ===
PROCESSO_DE_VALORES:
    ADD R3, R1
        ; Converte o primeiro dado de entrada de ASCII para seu formato binario.

    CMP R2, R0
        ; Verifica se o segundo dado e o byte de controle.
    JE TRATAR_DADO_SIMPLES
        ; Desvia se o valor e composto por um unico digito.

    ADD R3, R2
        ; Converte o segundo dado de entrada de ASCII para seu formato binario.

    DATA R0, 0x01
        ; Define R0 como o valor unitario.
    DATA R3, 0x01
        ; Define R3 como o valor unitario.
    NOT R3, R3
        ; Transforma R3 em -1.
    ADD R0, R3
        ; Zera R0 (1 + -1).

; === CADEIA ITERATIVA DE CALCULO ===
CADEIA_ITERATIVA_CALCULO:
    DATA R0, 0x00
        ; Zera R0 para a condicao de parada da cadeia.
    CMP R1, R0
        ; Compara o primeiro dado (dezena) com zero.
    JE AVANCAR_PARA_SEGUNDA_ENTRADA
        ; Se zero, a cadeia de calculo de dezenas termina.

    DATA R0, 0x0A
        ; Carrega a constante dez em R0.
    ADD R0, R2
        ; Acumula o produto da dezena por dez no registrador R2.
    ADD R3, R1
        ; Decrementa o valor da dezena (R1 = R1 - 1, ja que R3 e -1).
    JMP CADEIA_ITERATIVA_CALCULO
        ; Continua a cadeia.

; === MANIPULACAO DE VALORES DE DIGITO UNICO ===
TRATAR_DADO_SIMPLES:
    MOVE R1, R2
        ; Move o valor unico (ja em R2) para R1.
    DATA R1, 0x30
        ; Carrega o valor ASCII '0' em R1.
        ; AVISO: Isso pode corromper o valor numerico que R1 ja possui.
    ADD R1, R2
        ; Ajusta R1. Pode ser uma operacao redundante ou incorreta.
    JMP PROCESSO_DE_VALORES
        ; Retorna ao inicio do processo de valores. RISCO DE LOOP INDESEJADO!

; === PREPARACAO PARA A PROXIMA LEITURA (DIVISOR) ===
AVANCAR_PARA_SEGUNDA_ENTRADA:
    MOVE R2, R0
        ; Move o valor total acumulado para R2.
    DATA R3, 0x00
        ; Zera R3 para reutilizacao.

    DATA R2, 0x2F
        ; Recarrega o byte de controle ('/') em R2.

CADEIA_LEITURA_DIVISOR:
    IN DATA, R1
        ; Obtem o caractere que representa o divisor.
    CMP R1, R3
        ; Compara o divisor com zero.
    JE ROTA_DE_ERRO
        ; Desvia se o divisor for nulo.

    CMP R1, R2
        ; Compara o divisor com o byte de controle.
    JE CADEIA_LEITURA_DIVISOR
        ; Ignora o byte de controle e continua a leitura.

    DATA R2, 0xD0
        ; Carrega uma constante de ajuste para ASCII (-0x30).
    ADD R2, R1
        ; Converte o divisor (R1) de ASCII para binario.
    JMP INICIAR_PROCEDIMENTO_MATEMATICO
        ; Prossegue para o procedimento de calculo.

; === ROTA DE TRATAMENTO DE ERROS ===
ROTA_DE_ERRO:
    DATA R0, 0x21
        ; Caractere '!' para sinalizar um erro.
    DATA R1, 0x01
        ; Endereco de memoria para exibicao no console.
    OUT ADDR, R1
    OUT DATA, R0
    JMP FIM_DO_OPERACIONAL
        ; Finaliza a execucao do programa.

; === PROCEDIMENTO MATEMATICO PRINCIPAL (DIVISAO) ===
INICIAR_PROCEDIMENTO_MATEMATICO:
    DATA R2, 0x00
        ; Inicializa o registrador para o quociente em zero.
    CMP R1, R2
        ; Verifica se o divisor (R1) e zero.
    JE ROTA_DE_ERRO
        ; Desvia para a rota de erro se a divisao for por zero.

    DATA R3, 0x01
        ; Carrega uma constante auxiliar para incremento.

CADEIA_DE_OPERACAO:
    CMP R1, R0
        ; Compara o dividendo (R1) com o divisor (R0).
    JA RESULTADO_DE_SAIDA
        ; Se o dividendo for menor, a operacao esta concluida.

    NOT R1, R1
        ; Calcula o complemento de um do dividendo.
    ADD R1, R0
        ; Adiciona o divisor ao dividendo invertido.
        ; AVISO: Esta sequencia de operacoes NAO executa uma subtracao direta (Dividendo - Divisor).
        ; Isso pode levar a valores incorretos e loops interminaveis.

    ADD R3, R0
        ; Tenta incrementar o quociente (R3) usando R0.
        ; AVISO: R0 ainda e o divisor. Isso pode sobrescreve-lo, corrompendo o processo de divisao.
    NOT R1, R1
        ; Reverte o complemento de um do dividendo.
    ADD R3, R2
        ; Adiciona R3 a R2. A logica aqui e ambigua, pois R2 e o quociente.
    JMP CADEIA_DE_OPERACAO
        ; Continua o ciclo de operacao.

; === ROTINA DE EXIBICAO DE RESULTADO ===
RESULTADO_DE_SAIDA:
    MOVE R2, R0
        ; Move o valor final (quociente) de R0 para R2.
    DATA R2, 0x09
        ; Define um valor limite para a dezena (9).
    DATA R3, 0x0A
        ; Carrega a constante dez (10) para decomposicao.
    DATA R1, 0x01
        ; Define o endereco de saida para o console.

    NOT R3, R3
        ; Converte R3 para -10.
    ADD R1, R3
        ; Subtrai 10 do endereco de saida (R1).
        ; AVISO: Isso e um erro. R1 deveria ser o contador de dezenas para exibicao, nao um endereco.
    DATA R1, 0x00
        ; Zera R1, presumindo que seja um contador de dezenas.

CICLO_DE_MOSTRAGEM:
    CMP R0, R2
        ; Compara o quociente (R0) com o limite de dezena (9 em R2).
    JA EMITIR_DEZENAS
        ; Se o quociente for maior que 9, ha uma dezena para exibir.

    DATA R2, 0x01
        ; Define o endereco para o monitor.
    OUT ADDR, R2
    DATA R3, 0x30
        ; Carrega o valor ASCII '0'.
    ADD R3, R1
        ; Adiciona o contador de dezenas (R1) ao ASCII '0'.
    ADD R3, R0
        ; Adiciona a unidade do quociente (R0) ao ASCII '0'.
    OUT DATA, R1
        ; Exibe o caractere da dezena.
    OUT DATA, R0
        ; Exibe o caractere da unidade.
    JMP FIM_DO_OPERACIONAL
        ; Finaliza a execucao.

EMITIR_DEZENAS:
    ADD R3, R0
        ; Reduz o quociente (R0) em 10 (R3 e -10).
    DATA R2, 0x01
        ; Define R2 como o valor unitario.
    ADD R2, R1
        ; Incrementa o contador de dezenas (R1).
    DATA R2, 0x09
        ; Restaura R2 para 9.
    JMP CICLO_DE_MOSTRAGEM
        ; Continua o ciclo de exibicao.

; === PONTO DE FINALIZACAO ===
FIM_DO_OPERACIONAL:
    HALT
        ; Interrompe a execucao do programa.