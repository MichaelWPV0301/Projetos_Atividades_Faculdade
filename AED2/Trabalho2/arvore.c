#include "arvore.h"
#include <stdlib.h>


Arvore* inicializa(){
    return NULL;
}

Arvore* insereArvoreBinaria(Arvore** raiz, int valor){
    if(raiz==NULL){
        Arvore* novo = (Arvore*) malloc(sizeof(Arvore));
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        raiz = novo;
    }
    if(valor>=raiz->valor){
        insereArvoreBinaria(raiz->direita, valor);
    }
    else{
        insereArvoreBinaria(raiz->esquerda, valor);
    }
}

Arvore* caminhaPos(Arvore* raiz){
    caminhaPos(raiz->esquerda);
    caminhaPos(raiz->direita); 
    printf(raiz->valor);
}

Arvore* caminhaPre(Arvore* raiz){
    printf(raiz->valor);
    caminhaPre(raiz->esquerda);
    caminhaPre(raiz->direita); 
}

Arvore* caminhaCentral(Arvore* raiz){
    caminhaCentral(raiz->esquerda);
    printf(raiz->valor);
    caminhaCentral(raiz->direita); 
}
