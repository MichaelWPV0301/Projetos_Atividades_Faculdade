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

    double temposSeq[NUM_TESTES];
    double temposBin[NUM_TESTES];

    int valorAleatorio1, valorAleatorio2;
    Vetor vetor;
    Vetor vetorOrdenado;
    
    FILE *arquivo = fopen("dados_5.csv", "a");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Elementos, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000\n");

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

        liberaVetor(&vetor);
        liberaVetor(&vetorOrdenado);

    }


    //montagem do arquivo csv para montar o grafico:
    fprintf(arquivo, "temposSeq");
    for(int i=0; i<NUM_TESTES; i++){
        fprintf(arquivo, ",%f", temposSeq[i]);
    }
    fprintf(arquivo, "\n");
    fprintf(arquivo, "temposBin");
    for(int i=0; i<NUM_TESTES; i++){
        fprintf(arquivo, ",%f", temposBin[i]);
    }

    //Iteracao para mudar os dados
    char pause;
    printf("\nAperte enter para a parte 2 da questao 05.");
    scanf("%c", &pause);
    printf("\e[H\e[2J");



    // =============QUESTAO 02=================

    NUM_TESTES = 10;

    double tempoTotal_lista;
    double tempoTotal_vetor;

    Vetor vetor2;
    Lista* lista;
    
    double temposLista[NUM_TESTES];
    double temposVetor[NUM_TESTES];
    

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
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor2, valorAleatorio1, TAM);
        tempoFinal_1 = clock();        
        
        // Busca Sequencial na lista encadeada
        tempoInicial_2 = clock();
        buscaSequencialLista(lista, valorAleatorio1);
        tempoFinal_2 = clock();



        // Calculando o tempo das duas buscas
        tempoTotal_vetor = calculaTempo(tempoInicial_1, tempoFinal_1);        
        tempoTotal_lista = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando o tempo desta execução no vetor de tempo
        temposLista[TAM/PASSO - 1] = tempoTotal_lista;
        temposVetor[TAM/PASSO -1] = tempoTotal_vetor;

        // Mostrando os tempos dessa execução
        printf("\nO tempo da busca sequencial na lista encadeada com %d elementos foi %f segundos\n", TAM, tempoTotal_lista);

        liberaVetor(&vetor2);
        liberaLista(lista);
    }
    fprintf(arquivo, "\n");
    fprintf(arquivo, "TemposLista");    
    for(int i=0; i<NUM_TESTES; i++){
        fprintf(arquivo, ",%f", temposLista[i]);
    }

    fprintf(arquivo, "\n");
    fprintf(arquivo, "TemposVetor");    
    for(int i=0; i<NUM_TESTES; i++){
        fprintf(arquivo, ",%f", temposVetor[i]);
    }




    //Iteracao para mudar os dados
    printf("\nAperte enter para a parte 3 da questao 05.");
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

    double temposBolha[NUM_TESTES];
    double temposSelecao[NUM_TESTES];
    double temposInsercao[NUM_TESTES];
    double temposQuick[NUM_TESTES];
    double temposMerge[NUM_TESTES];


    fprintf(arquivo, "\nElementos, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000");
    
    for (int TAM = TAM_INICIAL; TAM <= TAM_FINAL; TAM = TAM + PASSO)
    {
        Vetor auxiliar;
        Vetor vetor3;

        //cria os vetores dinamicamente
        criaVetor(&vetor3, TAM);
        criaVetor(&auxiliar, TAM);

        //popula o vetor com elementos aleatórios
        populaVetorAleatorio(vetor3, TAM);

        //copia o vetor no auxiliar, e mede o tempo das 5 ordenações
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
    }

    //montagem do arquivo csv para montar os graficos:

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

    fclose(arquivo);

    return 0;
}