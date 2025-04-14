#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"

#define TAM 10000000
#define NUM_TESTES 30

int main()
{

    FILE *arquivo = fopen("dados_1.csv", "a");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Execucao, tempo(s), pos, valor\n");

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_Seq, tempoTotal_Bin;
    double media1, desvioPadrao1, media2, desvioPadrao2;

    double temposSeq[NUM_TESTES];
    double temposBin[NUM_TESTES];

    int valorAleatorio1, valorAleatorio2;
    int indice1, indice2;
    Vetor vetor;
    Vetor vetorOrdenado;

    // cria os vetores dinamicamente
    criaVetor(&vetor, TAM);
    criaVetor(&vetorOrdenado, TAM);

    // Populando os dois vetores
    populaVetorAleatorio(vetor, TAM);
    populaVetorAleatorioOrdenado(vetorOrdenado, TAM);

    // mudando a seed do rand() de acordo com o horário
    srand(time(NULL));

    for (int i = 1; i <= NUM_TESTES; i++)
    {

        printf("\nExecucao %d\n", i);

        // Primeira metade dos casos de teste estão garantidamente dentro do vetor
        // A segunda metade dos casos pode estar dentro ou fora
        if (i <= NUM_TESTES / 2)
        {
            valorAleatorio1 = vetor[abs(rand() % TAM)];
            valorAleatorio2 = vetorOrdenado[abs(rand() % TAM)];
        }
        else
        {
            valorAleatorio1 = rand();
            valorAleatorio2 = rand();
        }

        // Busca Sequencial no vetor desordenado
        tempoInicial_1 = clock();
        indice1 = buscaSequencialVetor(vetor, valorAleatorio1, TAM);
        tempoFinal_1 = clock();

        // Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        indice2 = buscaBinariaVetor(vetorOrdenado, valorAleatorio2, TAM);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_Seq = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Bin = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando os tempos desta execução nos vetores de tempo
        temposSeq[i-1] = tempoTotal_Seq;
        temposBin[i-1] = tempoTotal_Bin;

        //Mostrando os tempos dessa execução
        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_Seq);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_Bin);

        fprintf(arquivo, "Sequencial:       %d,         %f,         %d,         %d\n", i, tempoTotal_Seq, indice1, valorAleatorio1);
        fprintf(arquivo, "Binária:       %d,         %f,         %d,         %d\n", i, tempoTotal_Bin, indice2, valorAleatorio2);

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

    fclose(arquivo);
    return 0;
}