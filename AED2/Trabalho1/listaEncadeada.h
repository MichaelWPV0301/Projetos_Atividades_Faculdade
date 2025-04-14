#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED
#include "vet.h"

typedef struct TipoNo
{
    struct TipoNo *prox;
    int valor;
} TipoNo;

typedef struct Lista
{
    TipoNo *prim;
    TipoNo *ult;
} Lista;

void criaListaEncadeada(Lista **lista);

void liberaLista(Lista* lista);

void insereNaLista(Lista *lista, int valor);

void vetorEmListaEncadeada(Lista *lista, Vetor vetor, int tamanhoVetor);

int buscaSequencialLista(Lista *lista, int valor);

#endif