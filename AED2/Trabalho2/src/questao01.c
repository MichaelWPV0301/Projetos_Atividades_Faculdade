#include<stdio.h>
#include<stdlib.h>
#include "../include/vet.h"
#include "../include/arvore.h"

int main(){
    Vetor vetor;
    Arvore* ptrRaiz;
    criaVetor(&vetor, 20);
    populaVetorAleatorio(vetor, 20);
    mostraVetor(vetor, 20);
    vetorEmArvore(vetor, &ptrRaiz, 20);
    printf("\nCaminhamento de Forma Ordenada pela Arvore Binaria: [");
    caminhaCentral(ptrRaiz);
    printf("]\n");
    printf("\nCaminhamento de Forma Pre Fixada pela Arvore Binaria: [");
    caminhaPre(ptrRaiz);
    printf("]\n");    
    printf("\nCaminhamento de Forma Pos Fixada pela Arvore Binaria: [");
    caminhaPos(ptrRaiz);
    printf("]\n");        
    return 0;
}