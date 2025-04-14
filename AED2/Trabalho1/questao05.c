#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"
#include "listaEncadeada.h"

int main()
{
    // mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
     
     
     // =============QUESTAO 01=================


    int TAM_INICIAL = 100000;
    int TAM_FINAL = 1000000;
    int PASSO = 100000;
    int NUM_TESTES = 10;

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_Seq, tempoTotal_Bin;
    double media1, desvioPadrao1, media2, desvioPadrao2;

    double temposSeq[NUM_TESTES];
    double temposBin[NUM_TESTES];

    int valorAleatorio1, valorAleatorio2;
    Vetor vetor;
    Vetor vetorOrdenado;

    for (int TAM = TAM_INICIAL; TAM <= TAM_FINAL; TAM = TAM + PASSO)
    {

        // cria os vetores dinamicamente
        criaVetor(&vetor, TAM);
        criaVetor(&vetorOrdenado, TAM);

        // Populando os dois vetores
        populaVetorAleatorio(vetor, TAM);
        populaVetorAleatorioOrdenado(vetorOrdenado, TAM);


        // Primeira metade dos casos de teste estão garantidamente dentro do vetor
        // A segunda metade dos casos pode estar dentro ou fora
        valorAleatorio1 = vetor[abs(rand() % TAM)];
        valorAleatorio2 = vetorOrdenado[abs(rand() % TAM)];

        // Bus// =============QUESTAO 02=================ca Sequencial no vetor desordenado
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor, valorAleatorio1, TAM);
        tempoFinal_1 = clock();

        // Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        buscaBinariaVetor(vetorOrdenado, valorAleatorio2, TAM);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_Seq = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Bin = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando os tempos desta execução nos vetores de tempo
        temposSeq[TAM/PASSO - 1] = tempoTotal_Seq;
        temposBin[TAM/PASSO - 1] = tempoTotal_Bin;

        //Mostrando os tempos dessa execução
        printf("\nO tempo da busca sequencial com %d elementos foi %f segundos\n", TAM , tempoTotal_Seq);
        printf("O tempo da busca binaria com %d elementos foi %f segundos\n", TAM, tempoTotal_Bin);
    }

    //Calculando a média e desvio padrão dos tempos da busca sequencial
    media1 = calculaMedia(temposSeq, NUM_TESTES);
    desvioPadrao1 = calculaDesvioPadrao(temposSeq, media1, NUM_TESTES);

    //Calculando a média e desvio padrão dos tempos da busca binária
    media2 = calculaMedia(temposBin, NUM_TESTES);
    desvioPadrao2 = calculaDesvioPadrao(temposBin, media2, NUM_TESTES);

    //Mostrando os valores das médias e desvio padrão
    printf("\nMedia da Busca Sequencial: %f\n", media1);
    printf("Desvio padrão da Busca Sequencial: %f\n\n", desvioPadrao1);
    printf("Media da Busca Binaria: %f\n", media2);
    printf("Desvio padrão da Busca Binaria: %f\n", desvioPadrao2);






    char pause;
    scanf("%c", &pause);
    printf("\e[H\e[2J");



    // =============QUESTAO 02=================

    NUM_TESTES = 10;

    double tempoTotal_lista;
    double media3;

    Vetor vetor2;
    Lista* lista;
    
    double temposLista[NUM_TESTES];


    for (int TAM = TAM_INICIAL; TAM <= TAM_FINAL; TAM = TAM + PASSO)
    {
        
        // Cria o vetor e a lista encadeada dinamicamente
        criaVetor(&vetor2, TAM);
        criaListaEncadeada(&lista);

        // Populando o vetor com elementos aleatórios
        populaVetorAleatorio(vetor2, TAM);

        // Convertendo o vetor em lista encadeada//Mostrando os valores das médias e desvio padrão
        vetorEmListaEncadeada(lista, vetor2, TAM);

        valorAleatorio1 = vetor2[abs(rand() % TAM)];

        // Busca Sequencial na lista encadeada
        tempoInicial_2 = clock();
        buscaSequencialLista(lista, valorAleatorio1);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_lista = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando o tempo desta execução no vetor de tempo
        temposLista[TAM/PASSO - 1] = tempoTotal_lista;

        // Mostrando os tempos dessa execução
        printf("\nO tempo da busca sequencial na lista encadeada com %d elementos foi %f segundos\n", TAM, tempoTotal_lista);

        liberaVetor(vetor2);
        liberaLista(lista);
    }

    // Calculando as médias dos tempos no vetor e na lista encadeada
    media3 = calculaMedia(temposLista, NUM_TESTES);
    
    // Mostrando os valores das médias e desvio padrão
    printf("\nMedia da busca na lista encadeada foi de: %f\n", media3);



    scanf("%c", &pause);
    printf("\e[H\e[2J");



    // =============QUESTAO 03=================

    TAM_INICIAL = 10000;
    TAM_FINAL = 100000;
    PASSO = 10000;
    NUM_TESTES = 10;

    clock_t tempoInicial1, tempoInicial2, tempoInicial3, tempoInicial4, tempoInicial5; 
    clock_t tempoFinal1, tempoFinal2, tempoFinal3, tempoFinal4, tempoFinal5;
    double tempoTotal1, tempoTotal2, tempoTotal3, tempoTotal4, tempoTotal5;
    double media4, media5;

    Vetor vetor3;
    Vetor auxiliar;

    double temposBolha[NUM_TESTES];
    double temposSelecao[NUM_TESTES];
    double temposInsercao[NUM_TESTES];
    double temposQuick[NUM_TESTES];
    double temposMerge[NUM_TESTES];
    
    for (int TAM = TAM_INICIAL; TAM <= TAM_FINAL; TAM = TAM + PASSO)
    {
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

        liberaVetor(vetor3);
        liberaVetor(auxiliar);
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

    return 0;
}