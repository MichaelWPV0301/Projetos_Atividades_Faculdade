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

void insereArvoreLeft(TipoNo* no, int valor){
    TipoNo* novo = (TipoNo*) malloc(sizeof(TipoNo));
    no->esquerda = novo;
    novo->valor = valor;
    novo->direita = NULL;    valor = 2;

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
    int filhos;
    TipoNo* no = arvore->raiz;
    if(filho>filhos){
        return arvore->raiz;
    }
    else{
        while(nivel>2){
            filhos = pow(2,nivel-1);
            if(filho<=filhos/2){
                    no = no->esquerda;
                }
            else{
                no = no->direita;
            }   

            nivel--;
            filhos = filhos/2;
        }
        return no;
    }
}


int main(){
    Arvore* arvore;
    TipoNo* no;
    TipoNo novo;
    int valor, nivel, filho;
    criaArvore(arvore);
    nivel = 1;
    while(nivel!=0){
        filho = 0;
        printf("Sua arvore tem %d niveis\nEm qual nivel novo ou não e filho você quer inserir o elemento:", nivel);
        scanf("Nivel %d", &nivel);
        scanf("Filho %d", &filho);
        no = buscaElemento(arvore, nivel, filho);
        scanf("Qual o valor para seu novo nó %d", &valor);
        novo.valor = valor;
        if(filho%2){
            no->esquerda = &novo;
        }
        else{
            no->direita = &novo;
        }
    }

}