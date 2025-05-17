#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../include/vet.h"
#include "../include/arvore.h"

#define TAM 20
#define LIMITE 200

int main(){

    srand(time(NULL));  // Inicializa a seed para geração de números aleatórios

    Vetor vetor;        // Declara vetor de inteiros
    ArvoreBin* arvore;  // Declara ponteiro para árvore binária

    inicializa(&arvore);            // Inicializa a árvore binária (ponteiro NULL)
    criaVetor(&vetor, TAM);         // Aloca memória para vetor com TAM elementos
    populaVetorAleatorio(vetor, LIMITE, TAM); // Preenche vetor com valores aleatórios entre 0 e LIMITE
    vetorEmArvoreBin(vetor, &arvore, TAM,0); // Insere os elementos do vetor na árvore binária

    // Imprime percurso pré-ordem da árvore binária
    printf("\nCaminhamento de Forma Pre Fixada pela Arvore Binaria: {");
    caminhaPre(arvore);
    printf("]\n");    

    // Imprime percurso em ordem (central) da árvore binária
    printf("\nCaminhamento de Forma Ordenada pela Arvore Binaria: {");
    caminhaCentral(arvore);
    printf("}\n");
    
    // Imprime percurso pós-ordem da árvore binária
    printf("\nCaminhamento de Forma Pos Fixada pela Arvore Binaria: {");
    caminhaPos(arvore);
    printf("}\n");   
    
    liberaVetor(&vetor);    // Libera memória do vetor
    liberaArvore(arvore);   // Libera memória da árvore binária

    return 0;               // Finaliza programa com sucesso
}
