#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED
#include "vet.h"

typedef struct TipoNo TipoNo;
typedef struct Lista Lista;

void criaListaEncadeada(Lista **lista);

void insereNaLista(Lista *lista, int valor);

void vetorEmListaEncadeada(Lista *lista, Vetor vetor, int tamanhoVetor);

int buscaSequencialLista(Lista *lista, int valor);

#endif