#ifndef ARVORE_PACOTES__H_INCLUDED
#define ARVORE_PACOTES_H_iNCLUDED

#include <stdlib.h>

typedef struct Pacote{
    int id;
    char dado;
}Pacote;

typedef struct ArvorePacotes ArvorePacotes;

void inicializaArvPacotes(ArvorePacotes** raiz);
void inserePacoteArv(ArvorePacotes** ptrRaiz, Pacote pacote);
void caminhaCentralPacotes(ArvorePacotes* raiz, FILE* fp);
void pacotesEmArvore(Pacote* pacotes, ArvorePacotes** ptrRaiz, int tam);

#endif