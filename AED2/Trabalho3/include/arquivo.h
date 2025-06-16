 #ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

// Inclui bibliotecas padrão
#include <stdio.h>

#define NOME_TAM 50
#define CURSO_TAM 30

typedef struct {
    int matricula;             // chave primária (única)
    char nome[NOME_TAM];       // nome do aluno
    char curso[CURSO_TAM];     // curso (ex: Engenharia, Direito)
    int idade;                 // usado nas buscas com <, >, etc.
    float coeficiente;         // coeficiente de rendimento (CR)
    int anoIngresso;           // ano de ingresso
} Registro;

FILE* abrirArquivo(const char* nomeArquivo, const char* modo);
void fecharArquivo(FILE* ponteiroArquivo);
void escreverRegistro(FILE* arquivo, Registro *reg, long offset);
void adicionarRegistro(FILE* arquivo, Registro *reg);
Registro lerRegistro(FILE* arquivo, long offset);
Registro lerRegistroPorNumero(FILE* arquivo, int numeroRegistro);
int obterNumeroRegistros(FILE* arquivo);
void geraAlunos(Registro alunos[], int qtd);
void imprimeAlunos(Registro alunos[], int qtd);
void vetorEmArquivo(Registro alunos[], const char* nomeArquivo, int qtd);


#endif