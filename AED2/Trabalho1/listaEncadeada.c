#include "listaEncadeada.h"
#include "vet.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void criaListaEncadeada(Lista **lista)
{
    *lista = (Lista *)malloc(sizeof(Lista));
    (*lista)->prim = NULL;
}

void liberaLista(Lista* lista)
{
    TipoNo* atual = lista->prim;
    TipoNo* aux;

    if (atual == NULL){ return;}

    while(atual->prox)
    {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }

    free(atual);

    lista->prim = NULL;
    lista->ult = NULL;
}

void insereNaLista(Lista *lista, int valor)
{
    TipoNo *novo = (TipoNo *)malloc(sizeof(TipoNo));
    novo->valor = valor;
    novo->prox = NULL;

    TipoNo *aux = lista->ult;
    lista->ult = novo;
    if (aux == NULL)
    {
        lista->prim = novo;
        return;
    }
    aux->prox = novo;
}

void vetorEmListaEncadeada(Lista *lista, Vetor vetor, int tamanhoVetor)
{

    for (int x = 0; x < tamanhoVetor; x++)
    {
        insereNaLista(lista, vetor[x]);
    }
}

int buscaSequencialLista(Lista *lista, int valor)
{
    TipoNo *aux = lista->prim;
    while (aux)
    {
        if (aux->valor == valor)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}