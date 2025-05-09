#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_iNCLUDED

#include "../include/vet.h"

typedef struct ArvoreBin{
    struct ArvoreBin* esquerda;
    struct ArvoreBin* direita;
    int dado;
} ArvoreBin;

ArvoreBin* buscaArvoreBin(ArvoreBin* raiz, int dado)
void inicializa(ArvoreBin** raiz);
void insereArvoreBinaria(ArvoreBin** ptrRaiz, int valor);
void caminhaPos(ArvoreBin* raiz);
void caminhaPre(ArvoreBin* raiz);
void caminhaCentral(ArvoreBin* raiz);
void vetorEmArvoreBin(Vetor vetor, ArvoreBin** ptrRaiz, int tam);

#endif