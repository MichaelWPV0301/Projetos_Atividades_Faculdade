CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS = -lm

# Fontes comuns (sem main)
COMMON1 = src/vet.c src/arvore.c
COMMON2 = src/vet.c src/pacotes.c
COMMON3 =  src/vet.c src/arvore.c src/tempo.c
COMMON4 = src/arvore.c src/vet.c src/tempo.c src/avl.c

# Mains
QUESTAO01 = src/questao01.c
QUESTAO02 = src/questao02.c
QUESTAO03 = src/questao03.c
QUESTAO04 = src/questao04.c

# Executáveis
TARGET_QUESTAO01 = bin/questao01
TARGET_QUESTAO02 = bin/questao02
TARGET_QUESTAO03 = bin/questao03
TARGET_QUESTAO04 = bin/questao04

# Regra padrão: compila todos
all:  $(TARGET_QUESTAO01) $(TARGET_QUESTAO02) $(TARGET_QUESTAO03) $(TARGET_QUESTAO04)

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
$(TARGET_QUESTAO04): $(QUESTAO04) $(COMMON4)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(QUESTAO04) $(COMMON4) -o $(TARGET_QUESTAO04) $(LDFLAGS)
# Limpeza
clean:
	rm -rf bin