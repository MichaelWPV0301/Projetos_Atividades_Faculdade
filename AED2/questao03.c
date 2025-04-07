#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "vet.h"

#define TAM 100000
#define NUM 10
#define CalculaTempo(inicial,final) (double) (final - inicial)/CLOCKS_PER_SEC


int main(){

    clock_t tempoInicial_1, tempoInicial_2, tempoInicial_3, tempoInicial_4, tempoInicial_5; 
    clock_t tempoFinal_1, tempoFinal_2, tempoFinal_3, tempoFinal_4, tempoFinal_5;
    double tempoTotal_1, tempoTotal_2, tempoTotal_3, tempoTotal_4, tempoTotal_5;
    double media1, media2, media3, media4, media5;

    Vetor_int vetor;
    Vetor_int auxiliar;

    Vetor_double temposBolha;
    Vetor_double temposSelecao;
    Vetor_double temposInsercao;
    Vetor_double temposQuick;
    Vetor_double temposMerge;

    //cria os vetores dinamicamente
    criaVetorInt(&vetor, TAM);
    criaVetorInt(&auxiliar, TAM);
    criaVetorDouble(&temposBolha, NUM);
    criaVetorDouble(&temposSelecao, NUM);
    criaVetorDouble(&temposInsercao, NUM);
    criaVetorDouble(&temposQuick, NUM);
    criaVetorDouble(&temposMerge, NUM);


    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
    
    for(int i=0; i<10; i++){

        printf("\nExecução %d\n", i);

        populaVetorAleatorio(vetor, TAM);

        
        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_1 = clock();
        //ordenacao1
        tempoFinal_1 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_2 = clock();
        //ordenacao2
        tempoFinal_2 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_3 = clock();
        //ordenacao3
        tempoFinal_3 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_4 = clock();
        //ordenacao4
        tempoFinal_4 = clock();

        copiaVetor(auxiliar, vetor, TAM);
        tempoInicial_5 = clock();
        //ordenacao5
        tempoFinal_5 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal_1 = CalculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_2 = CalculaTempo(tempoInicial_2, tempoFinal_2);
        tempoTotal_3 = CalculaTempo(tempoInicial_3, tempoFinal_3);
        tempoTotal_4 = CalculaTempo(tempoInicial_4, tempoFinal_4);
        tempoTotal_5 = CalculaTempo(tempoInicial_5, tempoFinal_5);

        insereDoubleVetor(temposBolha, i, tempoTotal_1, NUM);
        insereDoubleVetor(temposSelecao, i, tempoTotal_2, NUM);
        insereDoubleVetor(temposInsercao, i, tempoTotal_3, NUM);
        insereDoubleVetor(temposQuick, i, tempoTotal_4, NUM);
        insereDoubleVetor(temposMerge, i, tempoTotal_5, NUM);

        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_1);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_2);
        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_3);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_4);
        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_5);

    }
    media1 = calculaMediaDouble(temposBolha, NUM);
    media2 = calculaMediaDouble(temposSelecao, NUM);
    media3 = calculaMediaDouble(temposInsercao, NUM);
    media4 = calculaMediaDouble(temposQuick, NUM);
    media5 = calculaMediaDouble(temposMerge, NUM);

    printf("média do Bolha: %f\n", media1);
    printf("média da Seleção: %f\n", media2);
    printf("média da Inserção: %f\n", media3);
    printf("média do Quicksort: %f\n", media4);
    printf("média do MergeSort: %f\n", media5);

    return 0;
}