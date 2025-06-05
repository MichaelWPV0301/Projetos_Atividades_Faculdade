#include "../include/arquivo.h"

// Inclui bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


// Função para abrir o arquivo
FILE* abrirArquivo(const char* nomeArquivo, const char* modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}

// Função para fechar o arquivo
void fecharArquivo(FILE* ponteiroArquivo) {
    if (fclose(ponteiroArquivo) != 0) {
        perror("Erro ao fechar o arquivo");
        exit(1);
    }
}

// Função para escrever um registro em uma posição específica
void escreverRegistro(FILE* arquivo, Registro *reg, long offset) {
    fseek(arquivo, offset * sizeof(Registro), SEEK_SET);
    size_t tamanhoEscrito = fwrite(reg, sizeof(Registro), 1, arquivo);
    if (tamanhoEscrito != 1) {
        perror("Erro ao escrever registro no arquivo");
        exit(1);
    }
}

// Função para adicionar um registro no final do arquivo
void adicionarRegistro(FILE* arquivo, Registro *reg) {
    fseek(arquivo, 0, SEEK_END); // Mover ponteiro para o final do arquivo
    size_t tamanhoEscrito = fwrite(reg, sizeof(Registro), 1, arquivo);
    if (tamanhoEscrito != 1) {
        perror("Erro ao adicionar registro no arquivo");
        exit(1);
    }
}

// Função para ler um registro em uma posição específica
Registro lerRegistro(FILE* arquivo, long offset) {
    Registro reg;
    fseek(arquivo, offset * sizeof(Registro), SEEK_SET);
    size_t tamanhoLido = fread(&reg, sizeof(Registro), 1, arquivo);
    if (tamanhoLido != 1) {
        perror("Erro ao ler registro do arquivo");
        exit(1);
    }
    return reg;
}

// Função para ler um registro pelo número (índice)
Registro lerRegistroPorNumero(FILE* arquivo, int numeroRegistro) {
    return lerRegistro(arquivo, numeroRegistro); // reutilizando a função de ler por offset
}

// Função para obter o número total de registros no arquivo
int obterNumeroRegistros(FILE* arquivo) {
    fseek(arquivo, 0, SEEK_END); // Mover ponteiro para o final do arquivo
    long tamanhoArquivo = ftell(arquivo); // Pega o tamanho total do arquivo
    return tamanhoArquivo / sizeof(Registro); // Retorna o número de registros
}


