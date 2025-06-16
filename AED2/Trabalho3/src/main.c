//#include "include/avl.h"
#include "../include/arquivo.h"
#include "../include/hash.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 30
#define QTD_ALUNOS 1000
#define PRCT_DESORDEM 50

int main(){
    char nomeArquivo[20];
    scanf("%[^\n]%*c", nomeArquivo);  
    abrirArquivo(nomeArquivo, "w+");

    srand(time(NULL));

    Registro alunos[QTD_ALUNOS];
    geraAlunos(alunos, QTD_ALUNOS);

    int trocas = PRCT_DESORDEM * QTD_ALUNOS / 100;  // Número de trocas para desordenar registros
    int j = 0;
    int indice;
    Registro aux;
    // Desordena parcialmente o vetor de registros trocando posições aleatoriamente
    while (j < trocas){
        indice = rand()%QTD_ALUNOS;
        aux = alunos[j];
        alunos[j] = alunos[indice];
        alunos[indice] = aux;
        j++;
    }

    imprimeAlunos(alunos, QTD_ALUNOS);
    vetorEmArquivo(alunos, nomeArquivo, QTD_ALUNOS);
    
    tipoHash hash;
    criaHash(&(hash), QTD_ALUNOS);
    vetorEmHash(alunos, &(hash), QTD_ALUNOS);
    return 0;
}