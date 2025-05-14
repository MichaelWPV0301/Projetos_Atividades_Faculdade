#include <stdio.h>
#include <stdlib.h>
#include "../include/pacotes.h"

typedef struct ArvorePacotes{
    struct ArvorePacotes* esquerda;
    struct ArvorePacotes* direita;
    Pacote pacote;
} ArvorePacotes;

void inicializaArvPacotes(ArvorePacotes** raiz){
    *raiz = NULL;
}

void inserePacoteArv(ArvorePacotes** ptrRaiz, Pacote pacote){

    ArvorePacotes* aux = *ptrRaiz;
    while((aux)){
        if (aux->pacote.id > pacote.id){
            ptrRaiz = &(aux->esquerda);
        }
        else if (aux->pacote.id < pacote.id){
            ptrRaiz = &(aux->direita);
        }
        else{ return; }
        aux = *ptrRaiz;
    }

    *ptrRaiz = (ArvorePacotes*) malloc(sizeof(ArvorePacotes));
    inicializaArvPacotes(&((*ptrRaiz)->esquerda));
    inicializaArvPacotes(&((*ptrRaiz)->direita));
    (*ptrRaiz)->pacote = pacote;
}

void caminhaCentralPacotes(ArvorePacotes* raiz, FILE* fp){
    if (raiz == NULL) return;
    caminhaCentralPacotes(raiz->esquerda, fp);
    printf("%c", raiz->pacote.dado);
    fwrite(&(raiz->pacote.dado), sizeof(char), 1, fp);
    caminhaCentralPacotes(raiz->direita, fp); 
}

void pacotesEmArvore(Pacote* pacotes, ArvorePacotes** ptrRaiz, int tam){
    for (int i = 0; i < tam; i++){
        inserePacoteArv(ptrRaiz, pacotes[i]);
    }
}