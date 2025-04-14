#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ferramentas.h"
#include "vet.h"
#include "listaEncadeada.h"

#define TAM 10000000
#define NUM_TESTES 30

int main(){

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vetor, tempoTotal_lista;
    double media1, media2;

    int valorAleatorio;
    Vetor vetor;
    Lista* lista;
    
    double temposVetor[NUM_TESTES];
    double temposLista[NUM_TESTES];
  
    // Cria o vetor e a lista encadeada dinamicamente
    criaVetor(&vetor, TAM);
    criaListaEncadeada(&lista);

    // Populando o vetor com elementos aleatórios
    populaVetorAleatorio(vetor, TAM);

    // Convertendo o vetor em lista encadeada//Mostrando os valores das médias e desvio padrão
    vetorEmListaEncadeada(lista, vetor, TAM);

    for (int i = 1; i <= NUM_TESTES; i++)
    {
        printf("\nExecucao %d\n", i);

        // Primeira metade dos casos de teste estão garantidamente dentro do vetor
        // A segunda metade dos casos pode estar dentro ou fora
        if (i <= NUM_TESTES / 2)
        {
            valorAleatorio = vetor[abs(rand() % TAM)];
        }
        else{
            valorAleatorio = rand();
        }
        
        // Busca Sequencial no vetor
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor, valorAleatorio, TAM);
        tempoFinal_1 = clock();

        // Busca Sequencial na lista encadeada
        tempoInicial_2 = clock();
        buscaSequencialLista(lista, valorAleatorio);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_vetor = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_lista = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando os tempos desta execução nos vetores de tempo
        temposVetor[i] = tempoTotal_vetor;
        temposLista[i] = tempoTotal_lista;

        // Mostrando os tempos dessa execução
        printf("O tempo da busca no vetor foi %f segundos\n", tempoTotal_vetor);
        printf("O tempo da busca na lista encadeada foi %f segundos\n", tempoTotal_lista);
        
    }

    // Calculando as médias dos tempos no vetor e na lista encadeada
    media1 = calculaMedia(temposVetor, NUM_TESTES);
    media2 = calculaMedia(temposLista, NUM_TESTES);
    
    // Mostrando os valores das médias e desvio padrão
    printf("\nMedia da busca no vetor foi de: %f\n", media1);
    printf("Media da busca na lista encadeada foi de: %f\n", media2);

    return 0;
}