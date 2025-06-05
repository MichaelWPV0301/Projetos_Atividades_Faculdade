//Grupo:Letícia Souza de Souza, Marcos Paulo Vieira Pedrosa, Mikaelle Costa de Santana, Michael Willian Pereira Vieira 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ferramentas.h"
#include "../include/vet.h"
#include "../include/listaEncadeada.h"


#define TAM 10000000 //Tamanho do vetor e da lista encadeada
#define NUM_TESTES 30 //Número de execuções

int main(){
    
    // Criando arquivo.csv para guardar os dados
    FILE *arquivo = fopen("dados_2.csv", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Execucao, tempo(s), pos, valor\n");

    //Declarando as variáveis do programa
    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vetor, tempoTotal_lista;
    double media1, media2;

    int valorAleatorio;
    int indice1, indice2;
    Vetor vetor;
    Lista* lista;
    
    double temposVetor[NUM_TESTES];
    double temposLista[NUM_TESTES];
    
    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));

    // Cria o vetor e a lista encadeada dinamicamente
    criaVetor(&vetor, TAM);
    criaListaEncadeada(&lista);

    // Populando o vetor com elementos aleatórios
    populaVetorAleatorio(vetor, TAM);

    // Convertendo o vetor em lista encadeada
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
        indice1 = buscaSequencialVetor(vetor, valorAleatorio, TAM);
        tempoFinal_1 = clock();

        // Busca Sequencial na lista encadeada
        tempoInicial_2 = clock();
        indice2 = buscaSequencialLista(lista, valorAleatorio);
        tempoFinal_2 = clock();

        // Calculando o tempo das duas buscas
        tempoTotal_vetor = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_lista = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Guardando os tempos desta execução nos vetores de tempo
        temposVetor[i-1] = tempoTotal_vetor;
        temposLista[i-1] = tempoTotal_lista;

        // Mostrando os tempos dessa execução
        printf("O tempo da busca no vetor foi %f segundos\n", tempoTotal_vetor);
        printf("O tempo da busca na lista encadeada foi %f segundos\n", tempoTotal_lista);
        
        //Escrevendo no arquivo
        fprintf(arquivo, "Lista:       %d,         %f,         %d,         %d\n", i, tempoTotal_vetor, indice1, valorAleatorio);
        fprintf(arquivo, "Vetor:       %d,         %f,         %d,         %d\n", i, tempoTotal_lista, indice2, valorAleatorio);
    }

    // Calculando as médias dos tempos no vetor e na lista encadeada
    media1 = calculaMedia(temposVetor, NUM_TESTES);
    media2 = calculaMedia(temposLista, NUM_TESTES);
    
    // Mostrando os valores das médias
    printf("\nMedia da busca no vetor foi de: %f\n", media1);
    printf("Media da busca na lista encadeada foi de: %f\n", media2);

    fprintf(arquivo, "Media vetor: %f", media1);
    fprintf(arquivo, "Media lista: %f", media2 );

    //Liberando o vetor e a lista encadeada da memória
    liberaVetor(&vetor);
    liberaLista(lista);

    //Fechando arquivo
    fclose(arquivo);
    return 0;
}