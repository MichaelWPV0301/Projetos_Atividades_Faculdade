#include"listaEncadeada.h"
#include"vet.h"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

typedef struct TipoNo{
    struct TipoNo* prox;
    int valor;
}TipoNo;

typedef struct Lista{
    TipoNo* prim;
    TipoNo* ult;
}Lista;


void criaListaEncadeada(Lista** lista){
    *lista = (Lista*) malloc(sizeof(Lista));
    (*lista )->prim = NULL;
}


void insereNaLista(Lista* lista, int valor){
    TipoNo* novo = (TipoNo*) malloc(sizeof(TipoNo));
    novo->valor = valor;
    novo->prox = NULL;

    TipoNo* aux = lista->ult;
    lista->ult = novo;
    if(aux==NULL){
        lista->prim = novo;
        return;
    }
    aux->prox = novo;


}
void vetorEmListaEncadeada(Lista* lista, Vetor_int vetor, int tamanhoVetor){
    
    for(int x=0; x<tamanhoVetor; x++){
        insereNaLista(lista, vetor[x]);
    }
}

int buscaSequencialLista(Lista* lista, int valor){
    TipoNo* aux = lista->prim;
    while(aux){
        if(aux->valor==valor){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}