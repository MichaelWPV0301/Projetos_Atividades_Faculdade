CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS = -lm

# Fontes comuns (sem main)
COMMON1 = src/vet.c src/ferramentas.c
COMMON2 = src/listaEncadeada.c src/vet.c src/ferramentas.c
COMMON3 =  src/vet.c src/ferramentas.c
COMMON5 = src/listaEncadeada.c src/vet.c src/ferramentas.c

# Mains
QUESTAO01 = src/questao01.c
QUESTAO02 = src/questao02.c
QUESTAO03 = src/questao03.c
QUESTAO05 = src/questao05.c

# Executáveis
TARGET_QUESTAO01 = bin/questao01
TARGET_QUESTAO02 = bin/questao02
TARGET_QUESTAO03 = bin/questao03
TARGET_QUESTAO05 = bin/questao05

# Regra padrão: compila todos
all:  $(TARGET_QUESTAO01) $(TARGET_QUESTAO02) $(TARGET_QUESTAO03) $(TARGET_QUESTAO05)

# Compilar cada main com os arquivos comuns
$(TARGET_QUESTAO01): $(QUESTAO01) $(COMMON1)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(QUESTAO01) $(COMMON1) -o $(TARGET_QUESTAO01) $(LDFLAGS)
$(TARGET_QUESTAO02): $(QUESTAO02) $(COMMON2)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(QUESTAO02) $(COMMON2) -o $(TARGET_QUESTAO02) $(LDFLAGS)
$(TARGET_QUESTAO03): $(QUESTAO03) $(COMMON3)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(QUESTAO03) $(COMMON3) -o $(TARGET_QUESTAO03) $(LDFLAGS)
$(TARGET_QUESTAO05): $(QUESTAO05) $(COMMON5)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(QUESTAO05) $(COMMON5) -o $(TARGET_QUESTAO05) $(LDFLAGS)
# Limpeza
clean:
	rm -rf bin

