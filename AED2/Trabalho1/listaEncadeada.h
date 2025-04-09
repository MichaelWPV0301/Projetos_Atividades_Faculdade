#ifndef LISTA_ENCADEADA
#define LISTA_ENCADEADA
#include "vet.h"

typedef struct TipoNo TipoNo;
typedef struct Lista Lista;


void criaListaEncadeada(Lista** lista);
void insereNaLista(Lista* lista, int valor);
void vetorEmListaEncadeada(Lista* lista, Vetor_int vetor, int tamanhoVetor);
int buscaSequencialLista(Lista* lista, int valor);

#endif