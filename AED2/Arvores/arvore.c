#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct TipoNo{
    int valor;
    struct TipoNo* esquerda;
    struct TipoNo* direita;
}TipoNo;

typedef struct Arvore{
    TipoNo* raiz;
}Arvore;


void criaNo(TipoNo* no, int valor){
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
}


void criaArvore(Arvore* arvore){
    arvore->raiz = NULL;
}

TipoNo* insereArvoreBinaria(TipoNo* raiz, int valor){
    if(raiz==NULL){
        TipoNo* novo = (TipoNo*) malloc(sizeof(TipoNo));
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->valor = valor;
        return novo;
    }
    if(valor<=raiz->valor){
        raiz->esquerda = insereArvoreBinaria(raiz->esquerda, valor);
    }
    else{
        raiz->direita = insereArvoreBinaria(raiz->direita, valor);
    }
    return raiz;
}

void insereArvoreLeft(TipoNo* no, int valor){
    TipoNo* novo = (TipoNo*) malloc(sizeof(TipoNo));
    no->esquerda = novo;
    novo->valor = valor;
    novo->direita = NULL;  
    novo->esquerda = NULL;
}

void insereArvoreRight(TipoNo* no, int valor){
    TipoNo* novo = (TipoNo*) malloc(sizeof(TipoNo));
    no->direita = novo;
    novo->valor = valor;
    novo->direita = NULL;
    novo->esquerda = NULL;
}


TipoNo* buscaElemento(Arvore* arvore, int nivel, int filho){
    int filhos = pow(2,nivel-1);
    TipoNo* no = arvore->raiz;

    if(filho>filhos){
        return arvore->raiz;
    }
    while(nivel>2){
        filhos = filhos/2;
        if(filho<=filhos/2){
                no = no->esquerda;
            }
        else{
            no = no->direita;
        }   
        if(!no ) return NULL;
        nivel--;
    }
    return no;
}


void mostraArvoreOrdenada(TipoNo* raiz){
    if(raiz!=NULL){
        mostraArvoreOrdenada(raiz->esquerda);
        printf("%d", raiz->valor);
        mostraArvoreOrdenada(raiz->direita);
    }
}


int main(){
    int valor;
    Arvore arvore;
    criaArvore(&arvore);
    valor = 0;
    while(valor!=-1){
        printf("Qual valor do novo nó você quer adicionar na árvore binária? [-1] se não quiser\n");
        scanf("%d\n", &valor);
        insereArvoreBinaria(arvore.raiz, valor);
    }
    mostraArvoreOrdenada(arvore.raiz);
}