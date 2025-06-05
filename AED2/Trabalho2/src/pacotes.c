#include <stdio.h>
#include <stdlib.h>
#include "../include/pacotes.h"

// Definição da estrutura da árvore binária de pacotes
typedef struct ArvorePacotes{
    struct ArvorePacotes* esquerda; // Ponteiro para o filho esquerdo
    struct ArvorePacotes* direita;  // Ponteiro para o filho direito
    Pacote pacote;                  // Dado armazenado do tipo Pacote
} ArvorePacotes;

// Inicializa a árvore de pacotes com NULL
void inicializaArvPacotes(ArvorePacotes** raiz){
    *raiz = NULL;
}

// Insere um pacote na árvore binária de forma ordenada (sem duplicatas)
void inserePacoteArv(ArvorePacotes** ptrRaiz, Pacote pacote){

    ArvorePacotes* aux = *ptrRaiz;
    while((aux)){
        // Navega para a esquerda se o ID for menor
        if (aux->pacote.id > pacote.id){
            ptrRaiz = &(aux->esquerda);
        }
        // Navega para a direita se o ID for maior
        else if (aux->pacote.id < pacote.id){
            ptrRaiz = &(aux->direita);
        }
        // Não insere se o ID já existir
        else{ return; }
        aux = *ptrRaiz;
    }

    // Aloca novo nó e inicializa filhos
    *ptrRaiz = (ArvorePacotes*) malloc(sizeof(ArvorePacotes));
    inicializaArvPacotes(&((*ptrRaiz)->esquerda));
    inicializaArvPacotes(&((*ptrRaiz)->direita));
    (*ptrRaiz)->pacote = pacote;
}

// Percorre a árvore em ordem central (in-order), imprime e grava os dados no arquivo
void caminhaCentralPacotes(ArvorePacotes* raiz, FILE* fp){
    if (raiz == NULL) return;
    caminhaCentralPacotes(raiz->esquerda, fp);
    printf("%c", raiz->pacote.dado); // Imprime o dado (caractere)
    fwrite(&(raiz->pacote.dado), sizeof(char), 1, fp); // Grava no arquivo
    caminhaCentralPacotes(raiz->direita, fp); 
}

// Insere um vetor de pacotes na árvore
void pacotesEmArvore(Pacote* pacotes, ArvorePacotes** ptrRaiz, int tam){
    for (int i = 0; i < tam; i++){
        inserePacoteArv(ptrRaiz, pacotes[i]);
    }
}

// Libera toda a memória alocada pela árvore de pacotes (pós-ordem)
void liberaArvorePacotes(ArvorePacotes *raiz)
{
    if (raiz == NULL)
        return;
    liberaArvorePacotes(raiz->esquerda);
    liberaArvorePacotes(raiz->direita);
    free(raiz);
}
