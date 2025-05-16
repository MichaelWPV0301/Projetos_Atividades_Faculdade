#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../include/vet.h"
#include "../include/pacotes.h"


#define TAM 100
#define LIMITE 50
#define PRCT_DESORDEM 20
#define PRCT_IGUAIS 5

int main(){

    srand(time(NULL));

    FILE* fp;
    fp = fopen("../entrada.txt", "r+");
    if (fp == NULL){
        perror("Erro ao abrir o arquivo de entrada:");
        return 1;
    }
    
    int tam;
    fseek(fp, 0, SEEK_END);
    tam = ftell(fp)/sizeof(char);
    fseek(fp, 0, SEEK_SET);
    
    Pacote pacotes[2*tam];

    int i = 0;
    char temp;
    while (fread(&temp, sizeof(char), 1, fp) == 1){
        pacotes[i].id = i;
        pacotes[i].dado = temp;
        if ((i + 1 < tam)&&(rand()%100 < PRCT_IGUAIS)){
            pacotes[i+1] = pacotes[i];
            i++;
        }
        i++;
    }
    int ids[i];
    for (int x = 0; x < i; x++){
        ids[x] = pacotes[x].id;
    }

    int trocas = PRCT_DESORDEM * tam / 100;
    int j = 0;
    int indice;
    Pacote aux;
    while (j < trocas){
        indice = rand()%i;
        aux = pacotes[j];
        pacotes[j] = pacotes[indice];
        pacotes[indice] = aux;
        j++;
    }

    for (int x = 0; x < i; x++){
        ids[x] = pacotes[x].id;
    }
    printf("\nVetor de IDs do fluxo de pacotes:\n\n");
    mostraVetor(ids, i);
    printf("\n\n");

    FILE* fp2;
    fp2 = fopen("../saida.txt", "w");
    if (fp2 == NULL){
        perror("Erro ao abrir o arquivo de saida:");
        return 1;
    }

    ArvorePacotes* arvore;
    inicializaArvPacotes(&arvore);
    pacotesEmArvore(pacotes, &arvore, i);
    printf("Arquivo de saida reconstruido a partir dos pacotes:\n\n");
    caminhaCentralPacotes(arvore, fp2);

    fclose(fp);
    fclose(fp2);

    return 0;
}