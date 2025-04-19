//Grupo:Letícia Souza de Souza, Marcos Paulo Vieira Pedrosa, Mikaelle Costa de Santana, Michael Willian Pereira Vieira 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ferramentas.h"
#include "../include/vet.h"

#define TAM 100000 //Tamanho dos vetores
#define NUM_TESTES 10 //Número de execuções


int main(){
    
    // Criando arquivo.csv para guardar os dados
    FILE *arquivo = fopen("dados_3.csv", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, ", Bolha, SelectionSort, InserctionSort, QuickSort, MergeSort\n");

    //Declarando as variáveis do programa
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
    
    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));

    //cria os vetores dinamicamente
    criaVetor(&vetor, TAM);
    criaVetor(&auxiliar, TAM);

    for(int i=1; i <= NUM_TESTES; i++){

        printf("\nExecucao %d\n", i);

        //Popula o vetor com elementos aleatórios
        populaVetorAleatorio(vetor, TAM);

        //Para cada ordenação, copia o vetor original no auxiliar
        //Medindo o tempo do bolha
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_1 = clock();
        bolha(auxiliar, TAM);
        tempoFinal_1 = clock();

        //Medindo o tempo do selectionSort
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_2 = clock();
        selectionSort(auxiliar, TAM);
        tempoFinal_2 = clock();

        //Medindo o tempo do insertionSort
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_3 = clock();
        insertionSort(auxiliar, TAM);
        tempoFinal_3 = clock();

        //Medindo o tempo do quickSort
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_4 = clock();
        quickSort(auxiliar, TAM);
        tempoFinal_4 = clock();

        //Medindo o tempo do mergeSort
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_5 = clock();
        mergeSort(auxiliar, TAM);
        tempoFinal_5 = clock();

        //Calculando o tempo das ordenações
        tempoTotal_1 = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_2 = calculaTempo(tempoInicial_2, tempoFinal_2);
        tempoTotal_3 = calculaTempo(tempoInicial_3, tempoFinal_3);
        tempoTotal_4 = calculaTempo(tempoInicial_4, tempoFinal_4);
        tempoTotal_5 = calculaTempo(tempoInicial_5, tempoFinal_5);

        //Guardando os tempos desta execução nos vetores de tempo
        temposBolha[i-1] = tempoTotal_1;
        temposSelecao[i-1] = tempoTotal_2;
        temposInsercao[i-1] = tempoTotal_3;
        temposQuick[i-1] = tempoTotal_4;
        temposMerge[i-1] = tempoTotal_5;

        //Escrevendo no arquivo
        fprintf(arquivo, "Tempos Execucao %d,       %f,         %f,         %f,         %f,         %f\n", i, tempoTotal_1, tempoTotal_2, tempoTotal_3, tempoTotal_4, tempoTotal_5);
        
        // Mostrando os valores das ordenações
        printf("O tempo do Bolha foi %f segundos\n", tempoTotal_1);
        printf("O tempo do Selection foi %f segundos\n", tempoTotal_2);
        printf("O tempo do Insertion foi %f segundos\n", tempoTotal_3);
        printf("O tempo do Quicksort foi %f segundos\n", tempoTotal_4);
        printf("O tempo do Mergesort foi %f segundos\n", tempoTotal_5);

    }

    //Calculando a média de cada ordenação
    media1 = calculaMedia(temposBolha, NUM_TESTES);
    media2 = calculaMedia(temposSelecao, NUM_TESTES);
    media3 = calculaMedia(temposInsercao, NUM_TESTES);
    media4 = calculaMedia(temposQuick, NUM_TESTES);
    media5 = calculaMedia(temposMerge, NUM_TESTES);

    //Mostrando as médias das ordenações
    printf("\nmédia do Bolha: %f\n", media1);
    printf("média da Seleção: %f\n", media2);
    printf("média da Inserção: %f\n", media3);
    printf("média do Quicksort: %f\n", media4);
    printf("média do MergeSort: %f\n", media5);

    fprintf(arquivo, "Medias,       %f,       %f,       %f,       %f,       %f\n", media1, media2, media3, media4, media5);
    
    //Liberando os vetores da memória
    liberaVetor(&vetor);
    liberaVetor(&auxiliar);

    //Fechando o arquivo
    fclose(arquivo);
    return 0;
}