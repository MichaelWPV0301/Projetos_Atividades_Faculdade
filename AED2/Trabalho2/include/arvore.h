#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_iNCLUDED

#include "../include/vet.h"

typedef struct Arvore{
    struct Arvore* esquerda;
    struct Arvore* direita;
    int dado;
} Arvore;

void inicializa(Arvore** raiz);
void insereArvoreBinaria(Arvore** ptrRaiz, int valor);
void caminhaPos(Arvore* raiz);
void caminhaPre(Arvore* raiz);
void caminhaCentral(Arvore* raiz);
void vetorEmArvore(Vetor vetor, Arvore** ptrRaiz, int tam);

#endif