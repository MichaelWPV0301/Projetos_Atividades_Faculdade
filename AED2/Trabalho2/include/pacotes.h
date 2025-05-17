#ifndef ARVORE_PACOTES__H_INCLUDED
#define ARVORE_PACOTES_H_iNCLUDED

#include <stdlib.h>

// Estrutura que representa um pacote com um identificador e um dado (caractere)
typedef struct Pacote{
    int id;       // Identificador único do pacote
    char dado;    // Dado armazenado (um caractere)
} Pacote;

// Definição opaca da estrutura da árvore de pacotes
typedef struct ArvorePacotes ArvorePacotes;

// Inicializa a árvore de pacotes (define o ponteiro raiz como NULL)
void inicializaArvPacotes(ArvorePacotes** raiz);

// Insere um pacote na árvore binária de forma ordenada (sem duplicatas)
void inserePacoteArv(ArvorePacotes** ptrRaiz, Pacote pacote);

// Percorre a árvore em ordem central (in-order), imprime e grava os dados em um arquivo
void caminhaCentralPacotes(ArvorePacotes* raiz, FILE* fp);

// Insere todos os pacotes de um vetor na árvore binária
void pacotesEmArvore(Pacote* pacotes, ArvorePacotes** ptrRaiz, int tam);

// Libera a memória alocada para a árvore de pacotes (pós-ordem)
void liberaArvorePacotes(ArvorePacotes *raiz);

#endif
