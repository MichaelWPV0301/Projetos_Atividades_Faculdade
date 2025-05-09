#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../include/vet.h"
#include "../include/arvore.h"

#define TAM 100
#define LIMITE 50

typedef struct Pacote{
    int id;
    int dado;
}Pacote;

int main(){

    srand(time(NULL));

    Vetor vetor;
    ArvoreBin* arvore;

    inicializa(&arvore);
    criaVetor(&vetor, TAM);
    populaVetorParcialmenteOrdenado(vetor, LIMITE, TAM);
    printf("Vetor: ");
    mostraVetor(vetor, TAM);
    vetorEmArvoreBin(vetor, &arvore, TAM);

    FILE* fp;
    fp = fopen("../entrada.txt", "r+");
    if (fp == NULL){
        perror("Erro ao abrir o arquivo:");
        return 1;
    }
    
    int tam;
    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(char);
    fseek(fp, 0, SEEK_SET);
    
    Pacote pacotes[2*tam];
    char temp;
    while (fread(&temp, sizeof(char), 1, fp) == 1){
        //Cria vetor de pacotes parcialmente ordenado com até duas duplicatasa cada (pensar no esquema de porcentagem)
    }
    return 0;
}