#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"

#define TAM 1000000
#define NUM_TESTES 30

int main()
{

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_Seq, tempoTotal_Bin;
    double media1, desvioPadrao1, media2, desvioPadrao2;

    double temposSeq[NUM_TESTES];
    double temposBin[NUM_TESTES];

    int valorAleatorio1, valorAleatorio2;
    Vetor vetor;
    Vetor vetorOrdenado;

    // cria os vetores dinamicamente
    criaVetor(vetor, TAM);
    criaVetor(vetorOrdenado, TAM);

    // Populando os dois vetores
    populaVetorAleatorio(vetor, TAM);
    populaVetorAleatorioOrdenado(vetorOrdenado, TAM);

    // mudando a seed do rand() de acordo com o horário
    srand(time(NULL));

    for (int i = 1; i <= TAM; i++)
    {

        printf("\nExecução %d\n", i);

        // 15 casos dentro do vetor, 15 casos podendo estar fora
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
        buscaSequencialVetor(vetor, valorAleatorio1, TAM);
        tempoFinal_1 = clock();

        // Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        buscaBinariaVetor(vetorOrdenado, valorAleatorio2, TAM);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_Seq = CalculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Bin = CalculaTempo(tempoInicial_2, tempoFinal_2);

        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_Seq);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_Bin);
    }
    media1 = calculaMedia(temposSeq, NUM_TESTES);
    desvioPadrao1 = calculaDesvioPadrao(temposSeq, media1, NUM_TESTES);
    media2 = calculaMedia(temposBin, NUM_TESTES);
    desvioPadrao2 = calculaDesvioPadrao(temposBin, media2, NUM_TESTES);

    printf("média da busca Sequencial: %f\n", media1);
    printf("desvio padrão da busca Sequencial: %f\n", desvioPadrao1);
    printf("média da busca Binária: %f\n", media2);
    printf("desvio padrão da busca Binária: %f\n", desvioPadrao2);

    return 0;
}