#include "../include/arvore.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>


void inicializa(Arvore** raiz){
    *raiz = NULL;
}

void insereArvoreBinaria(Arvore** ptrRaiz, int valor){

    while((*ptrRaiz)){
        if ((*ptrRaiz)->dado > valor){
            ptrRaiz = &((*ptrRaiz)->esquerda);
        }
        else{
            ptrRaiz = &((*ptrRaiz)->direita);
        }
    }

    *ptrRaiz = (Arvore*) malloc(sizeof(Arvore));
    inicializa(&((*ptrRaiz)->esquerda));
    inicializa(&((*ptrRaiz)->direita));
    (*ptrRaiz)->dado = valor;
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
