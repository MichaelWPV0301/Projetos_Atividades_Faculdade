#include<stdio.h>
#include<stdlib.h>
#include "../include/vet.h"
#include "../include/arvore.h"

int main(){
    Vetor vetor;
    criaVetor(&vetor, 1000000);
    populaVetorParcialmenteOrdenado(vetor, 1000000);
    mostraVetor(vetor, 1000000);
    return 0;
}