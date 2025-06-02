#include "../include/arquivo.h"

// Inclui bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define NOME_TAM 50
#define CURSO_TAM 30

// Definição da estrutura de registro
typedef struct {
    int matricula;             // chave primária (única)
    char nome[NOME_TAM];       // nome do aluno
    char curso[CURSO_TAM];     // curso (ex: Engenharia, Direito)
    int idade;                 // usado nas buscas com <, >, etc.
    float coeficiente;         // coeficiente de rendimento (CR)
    int anoIngresso;           // ano de ingresso
} Registro;

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

int main() {
    // Criando ou abrindo o arquivo em modo leitura e escrita binária
    FILE *arquivo = abrirArquivo("cadastro_alunos.dat", "r+b");

    // Adicionando um novo aluno
    Registro aluno1 = {12345, "João Silva", "Engenharia", 20, 8.5, 2022};
    adicionarRegistro(arquivo, &aluno1);

    // Obter o número de registros
    int numRegistros = obterNumeroRegistros(arquivo);
    printf("Número de registros no arquivo: %d\n", numRegistros);

    // Ler o primeiro registro (offset 0)
    Registro alunoLido = lerRegistro(arquivo, 0);
    printf("Matricula: %d, Nome: %s, Curso: %s, Idade: %d\n", alunoLido.matricula, alunoLido.nome, alunoLido.curso, alunoLido.idade);

    // Fechar o arquivo
    fecharArquivo(arquivo);

    return 0;
}
