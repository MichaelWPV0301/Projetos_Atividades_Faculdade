#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../include/vet.h"
#include "../include/arvore.h"

#define TAM 20
#define LIMITE 200

int main(){

    srand(time(NULL));

    Vetor vetor;
    ArvoreBin* arvore;

    inicializa(&arvore);
    criaVetor(&vetor, TAM);
    populaVetorAleatorio(vetor, LIMITE, TAM);
    vetorEmArvoreBin(vetor, &arvore, TAM,0);

    printf("\nCaminhamento de Forma Pre Fixada pela Arvore Binaria: {");
    caminhaPre(arvore);
    printf("]\n");    

    printf("\nCaminhamento de Forma Ordenada pela Arvore Binaria: {");
    caminhaCentral(arvore);
    printf("}\n");
    
    printf("\nCaminhamento de Forma Pos Fixada pela Arvore Binaria: {");
    caminhaPos(arvore);
    printf("}\n");   
    
    liberaVetor(&vetor);
    liberaArvore(arvore);

    return 0;
}