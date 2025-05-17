#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_iNCLUDED

#include "../include/vet.h"

typedef struct ArvoreBin ArvoreBin;

ArvoreBin* buscaArvoreBin(ArvoreBin* raiz, int dado);
int altura(ArvoreBin *arvore);
void inicializa(ArvoreBin** raiz);
void insereArvoreBinaria(ArvoreBin** ptrRaiz, int valor);
void caminhaPos(ArvoreBin* raiz);
void caminhaPre(ArvoreBin* raiz);
void caminhaCentral(ArvoreBin* raiz);
void vetorEmArvoreBin(Vetor vetor, ArvoreBin** ptrRaiz, int tam);
void liberaArvore(ArvoreBin* raiz);
void vetorOrdenadoEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int inicio, int fim);

#endif