#include<stdio.h>
#include<stdlib.h>
#include "vet.h"

void criaVetor(Vetor* v, int tamanho){
    *v = (Vetor) malloc(sizeof(int)*tamanho);
}

void populaVetorAleatorio(Vetor vetor, int tamanho){
    for (int i=0; i<tamanho; i++){
        vetor[i] = rand();
    }
}

void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho){
    vetor[0] = 0;
    for (int i=1; i<tamanho; i++){
        vetor[i] = vetor[i-1] + abs(rand()%10);
    }
}

int buscaSequencialVetor(Vetor vetor, int valor, int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        if (vetor[i] == valor){
            return i;
        }
    }
    return -1;
}

int buscaBinaria(Vetor vetor, int valor, int tamanho){
    int inicio, meio, fim;
    inicio = 0;
    fim = tamanho-1;
    while (inicio <= fim){
        meio = inicio + (fim - inicio)/2;
        if (vetor[meio] < valor){
            inicio = meio + 1;
        }
        else if (vetor[meio] > valor){
            fim = meio -1;
        }
        else{
            return meio;
        }
    }
    return -1;
}
