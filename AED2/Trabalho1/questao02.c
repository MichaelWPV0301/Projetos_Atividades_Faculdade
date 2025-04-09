#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "vet.h"
#include "listaEncadeada.h"

#define TAM 1000000
#define NUM 30
#define CalculaTempo(inicial,final) (double) (final - inicial)/CLOCKS_PER_SEC


int main(){

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vetor, tempoTotal_lista;
    double media1, media2;

    int valorAleatorio;
    Vetor_int vetor;
    Lista* lista;
   
    
    Vetor_double temposVetor;
    Vetor_double temposLista;
  
    //cria os vetores e listaEncadeada dinamicamente
    criaVetorInt(&vetor, TAM);
    criaListaEncadeada(&lista);
    criaVetorDouble(&temposVetor, NUM);
    criaVetorDouble(&temposLista, NUM);


    //Populando o vetor e transformando em lista encadeada
    populaVetorAleatorio(vetor, TAM);
    vetorEmListaEncadeada(lista, vetor, TAM);
    
    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
    
    for(int i=0; i<30; i++){

        printf("\nExecução %d\n", i);

        //15 casos dentro do vetor, 15 casos podendo estar fora
        if (i < 15){
            valorAleatorio = vetor[abs(rand()%TAM)];
        }
        else{
            valorAleatorio = rand();
        }
        
        //Busca Sequencial no vetor desordenado
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor, valorAleatorio, TAM);
        tempoFinal_1 = clock();

        //Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        buscaSequencialLista(lista, valorAleatorio);
        tempoFinal_2 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal_vetor = CalculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_lista = CalculaTempo(tempoInicial_2, tempoFinal_2);
        insereDoubleVetor(temposVetor, i, tempoTotal_vetor, NUM);
        insereDoubleVetor(temposLista, i, tempoTotal_lista, NUM);

        printf("O tempo da busca no vetor foi %f segundos\n", tempoTotal_vetor);
        printf("O tempo da busca na lista encadeada foi %f segundos\n", tempoTotal_lista);
        
    }
    media1 = calculaMediaDouble(temposVetor, NUM);
    media2 = calculaMediaDouble(temposLista, NUM);
    
    printf("média da busca no vetor foi de: %f\n", media1);
    printf("média da busca na lista encadeada foi de: %f\n", media2);

    return 0;
}