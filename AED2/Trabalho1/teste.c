// =============QUESTAO 03=================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"
#include "listaEncadeada.h"

int main(){

    int TAM_INICIAL = 10000;
    int TAM_FINAL = 100000;
    int PASSO = 10000;
    int NUM_TESTES = 10;

    clock_t tempoInicial1, tempoInicial2, tempoInicial3, tempoInicial4, tempoInicial5; 
    clock_t tempoFinal1, tempoFinal2, tempoFinal3, tempoFinal4, tempoFinal5;
    double tempoTotal1, tempoTotal2, tempoTotal3, tempoTotal4, tempoTotal5;

    double temposBolha[NUM_TESTES];
    double temposSelecao[NUM_TESTES];
    double temposInsercao[NUM_TESTES];
    double temposQuick[NUM_TESTES];
    double temposMerge[NUM_TESTES];

    FILE *arquivo = fopen("dados_5.csv", "a");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "\nElementos, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000");
    
    for (int TAM = TAM_INICIAL; TAM <= TAM_FINAL; TAM = TAM + PASSO)
    {
        Vetor auxiliar;
        Vetor vetor3;

        //cria os vetores dinamicamente
        criaVetor(&vetor3, TAM);
        criaVetor(&auxiliar, TAM);

        populaVetorAleatorio(vetor3, TAM);

        copiaVetor(auxiliar, vetor3, TAM);
        tempoInicial1 = clock();
        bolha(auxiliar, TAM);
        tempoFinal1 = clock();

        copiaVetor(auxiliar, vetor3, TAM);
        tempoInicial2 = clock();
        selectionSort(auxiliar, TAM);
        tempoFinal2 = clock();

        copiaVetor(auxiliar, vetor3, TAM);
        tempoInicial3 = clock();
        insertionSort(auxiliar, TAM);
        tempoFinal3 = clock();

        copiaVetor(auxiliar, vetor3, TAM);
        tempoInicial4 = clock();
        quickSort(auxiliar, TAM);
        tempoFinal4 = clock();

        copiaVetor(auxiliar, vetor3, TAM);
        tempoInicial5 = clock();
        mergeSort(auxiliar, TAM);
        tempoFinal5 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal1 = calculaTempo(tempoInicial1, tempoFinal1);
        tempoTotal2 = calculaTempo(tempoInicial2, tempoFinal2);
        tempoTotal3 = calculaTempo(tempoInicial3, tempoFinal3);
        tempoTotal4 = calculaTempo(tempoInicial4, tempoFinal4);
        tempoTotal5 = calculaTempo(tempoInicial5, tempoFinal5);

        temposBolha[TAM/PASSO - 1] = tempoTotal1;
        temposSelecao[TAM/PASSO - 1] = tempoTotal2;
        temposInsercao[TAM/PASSO - 1] = tempoTotal3;
        temposQuick[TAM/PASSO - 1] = tempoTotal4;
        temposMerge[TAM/PASSO - 1] = tempoTotal5;

        printf("Com %d elementos:\n", TAM);
        printf("O tempo do Bolha foi %f segundos\n", tempoTotal1);
        printf("O tempo do Selection foi %f segundos\n", tempoTotal2);
        printf("O tempo do Insertion foi %f segundos\n", tempoTotal3);
        printf("O tempo do Quicksort foi %f segundos\n", tempoTotal4);
        printf("O tempo do Mergesort foi %f segundos\n\n", tempoTotal5);
        printf("libera o cu: %p e %p\n", vetor3, auxiliar);

        fprintf(arquivo, "\n");
        fprintf(arquivo, "TemposBolha");    
        for(int i=0; i<NUM_TESTES; i++){
            fprintf(arquivo, ",%f", temposBolha[i]);
        }

        fprintf(arquivo, "\n");
        fprintf(arquivo, "TemposSelecao");    
        for(int i=0; i<NUM_TESTES; i++){
            fprintf(arquivo, ",%f", temposSelecao[i]);
        }


        fprintf(arquivo, "\n");
        fprintf(arquivo, "TemposInsercao");    
        for(int i=0; i<NUM_TESTES; i++){
            fprintf(arquivo, ",%f", temposInsercao[i]);
        }



        fprintf(arquivo, "\n");
        fprintf(arquivo, "TemposQuick");    
        for(int i=0; i<NUM_TESTES; i++){
            fprintf(arquivo, ",%f", temposQuick[i]);
        }
        
        fprintf(arquivo, "\n");
        fprintf(arquivo, "TemposMerge");    
        for(int i=0; i<NUM_TESTES; i++){
            fprintf(arquivo, ",%f", temposMerge[i]);
        }

    }
    fclose(arquivo);

    return 0;
}