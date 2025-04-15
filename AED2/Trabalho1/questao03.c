#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"

#define TAM 100000
#define NUM_TESTES 10


int main(){

    clock_t tempoInicial_1, tempoInicial_2, tempoInicial_3, tempoInicial_4, tempoInicial_5; 
    clock_t tempoFinal_1, tempoFinal_2, tempoFinal_3, tempoFinal_4, tempoFinal_5;
    double tempoTotal_1, tempoTotal_2, tempoTotal_3, tempoTotal_4, tempoTotal_5;
    double media1, media2, media3, media4, media5;

    Vetor vetor;
    Vetor auxiliar;

    double temposBolha[NUM_TESTES];
    double temposSelecao[NUM_TESTES];
    double temposInsercao[NUM_TESTES];
    double temposQuick[NUM_TESTES];
    double temposMerge[NUM_TESTES];

    //cria os vetores dinamicamente
    criaVetor(&vetor, TAM);
    criaVetor(&auxiliar, TAM);

    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));

    FILE *arquivo = fopen("dados_3.csv", "a");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, ", Bolha, SelectionSort, InserctionSort, QuickSort, MergeSort\n");
    
    for(int i=1; i <= NUM_TESTES; i++){

        printf("\nExecucao %d\n", i);

        populaVetorAleatorio(vetor, TAM);

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_1 = clock();
        bolha(auxiliar, TAM);
        tempoFinal_1 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_2 = clock();
        selectionSort(auxiliar, TAM);
        tempoFinal_2 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_3 = clock();
        insertionSort(auxiliar, TAM);
        tempoFinal_3 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_4 = clock();
        quickSort(auxiliar, TAM);
        tempoFinal_4 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_5 = clock();
        mergeSort(auxiliar, TAM);
        tempoFinal_5 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal_1 = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_2 = calculaTempo(tempoInicial_2, tempoFinal_2);
        tempoTotal_3 = calculaTempo(tempoInicial_3, tempoFinal_3);
        tempoTotal_4 = calculaTempo(tempoInicial_4, tempoFinal_4);
        tempoTotal_5 = calculaTempo(tempoInicial_5, tempoFinal_5);


        temposBolha[i-1] = tempoTotal_1;
        temposSelecao[i-1] = tempoTotal_2;
        temposInsercao[i-1] = tempoTotal_3;
        temposQuick[i-1] = tempoTotal_4;
        temposMerge[i-1] = tempoTotal_5;


        fprintf(arquivo, "Tempos Execucao %d,       %f,         %f,         %f,         %f,         %f\n", i, tempoTotal_1, tempoTotal_2, tempoTotal_3, tempoTotal_4, tempoTotal_5);
        
        printf("O tempo do Bolha foi %f segundos\n", tempoTotal_1);
        printf("O tempo do Selection foi %f segundos\n", tempoTotal_2);
        printf("O tempo do Insertion foi %f segundos\n", tempoTotal_3);
        printf("O tempo do Quicksort foi %f segundos\n", tempoTotal_4);
        printf("O tempo do Mergesort foi %f segundos\n", tempoTotal_5);

    }

    media1 = calculaMedia(temposBolha, NUM_TESTES);
    media2 = calculaMedia(temposSelecao, NUM_TESTES);
    media3 = calculaMedia(temposInsercao, NUM_TESTES);
    media4 = calculaMedia(temposQuick, NUM_TESTES);
    media5 = calculaMedia(temposMerge, NUM_TESTES);

    printf("\nmédia do Bolha: %f\n", media1);
    printf("média da Seleção: %f\n", media2);
    printf("média da Inserção: %f\n", media3);
    printf("média do Quicksort: %f\n", media4);
    printf("média do MergeSort: %f\n", media5);
    fprintf(arquivo, "Medias,       %f,       %f,       %f,       %f,       %f\n", media1, media2, media3, media4, media5);
    fclose(arquivo);
    return 0;
}