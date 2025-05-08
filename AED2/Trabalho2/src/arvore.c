#include "../include/arvore.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>


void inicializa(Arvore** raiz){
    *raiz = NULL;
}

void insereArvoreBinaria(Arvore** ptrRaiz, int valor){

    Arvore* aux = *ptrRaiz;
    while((aux)){
        if (aux->dado > valor){
            ptrRaiz = &(aux->esquerda);
        }
        else{
            ptrRaiz = &(aux->direita);
        }
        aux = *ptrRaiz;
    }

    *ptrRaiz = (Arvore*) malloc(sizeof(Arvore));
    inicializa(&((*ptrRaiz)->esquerda));
    inicializa(&((*ptrRaiz)->direita));
    (*ptrRaiz)->dado = valor;
}

Arvore* buscaArvore(Arvore* raiz, int dado){
    Arvore* aux = raiz;
    while(aux!=NULL){
        if(aux->dado>dado){
            aux = aux->esquerda;
        }
        else if(aux->dado<dado){
            aux = aux->direita;
        }
        else{
            return aux;
        }
    }
    return NULL;
}

void caminhaPos(Arvore* raiz){
    if (raiz == NULL) return;
    caminhaPos(raiz->esquerda);
    caminhaPos(raiz->direita); 
    printf("%d ", raiz->dado);
}

void caminhaPre(Arvore* raiz){
    if (raiz == NULL) return;
    printf("%d ", raiz->dado);
    caminhaPre(raiz->esquerda);
    caminhaPre(raiz->direita); 
}

void caminhaCentral(Arvore* raiz){
    if (raiz == NULL) return;
    caminhaCentral(raiz->esquerda);
    printf("%d ", raiz->dado);
    caminhaCentral(raiz->direita); 
}

void vetorEmArvore(Vetor vetor, Arvore** ptrRaiz, int tam){
    for (int i = 0; i < tam; i++){
        insereArvoreBinaria(ptrRaiz, vetor[i]);
    }
}
