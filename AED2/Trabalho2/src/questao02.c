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

    srand(time(NULL));  // Inicializa seed para números aleatórios

    FILE* fp;
    fp = fopen("../entrada.txt", "r+");  // Abre arquivo de entrada para leitura e escrita
    if (fp == NULL){
        perror("Erro ao abrir o arquivo de entrada:");  // Caso falha na abertura, exibe erro
        return 1;
    }
    
    int tam;
    fseek(fp, 0, SEEK_END);               // Vai até o fim do arquivo
    tam = ftell(fp)/sizeof(char);         // Obtém tamanho do arquivo em número de caracteres
    fseek(fp, 0, SEEK_SET);               // Volta para o início do arquivo
    
    Pacote pacotes[2*tam];                // Declara vetor de pacotes com tamanho 2*tam (para evitar overflow em duplicação)

    int i = 0;
    char temp;
    // Lê caracteres do arquivo e cria pacotes
    while (fread(&temp, sizeof(char), 1, fp) == 1){
        pacotes[i].id = i;                // Define ID do pacote como índice
        pacotes[i].dado = temp;           // Armazena dado lido no pacote
        // Possibilidade de duplicar pacote (PRCT_IGUAIS % de chance)
        if ((i + 1 < tam)&&(rand()%100 < PRCT_IGUAIS)){
            pacotes[i+1] = pacotes[i];   // Duplicação do pacote atual
            i++;
        }
        i++;
    }

    int ids[i];
    for (int x = 0; x < i; x++){
        ids[x] = pacotes[x].id;           // Copia IDs dos pacotes para vetor ids
    }

    int trocas = PRCT_DESORDEM * tam / 100;  // Número de trocas para desordenar pacotes
    int j = 0;
    int indice;
    Pacote aux;
    // Desordena parcialmente o vetor de pacotes trocando posições aleatoriamente
    while (j < trocas){
        indice = rand()%i;
        aux = pacotes[j];
        pacotes[j] = pacotes[indice];
        pacotes[indice] = aux;
        j++;
    }

    for (int x = 0; x < i; x++){
        ids[x] = pacotes[x].id;           // Atualiza vetor de IDs após desordenação
    }

    printf("\nVetor de IDs do fluxo de pacotes:\n\n");
    mostraVetor(ids, i);                  // Exibe vetor de IDs na tela
    printf("\n\n");

    FILE* fp2;
    fp2 = fopen("../saida.txt", "w");    // Abre arquivo de saída para escrita
    if (fp2 == NULL){
        perror("Erro ao abrir o arquivo de saida:");  // Caso falha na abertura, exibe erro
        return 1;
    }

    ArvorePacotes* arvore;
    inicializaArvPacotes(&arvore);       // Inicializa a árvore binária de pacotes
    pacotesEmArvore(pacotes, &arvore, i);  // Insere pacotes na árvore
    printf("Arquivo de saida reconstruido a partir dos pacotes:\n\n");
    caminhaCentralPacotes(arvore, fp2); // Percorre a árvore em ordem e grava
}