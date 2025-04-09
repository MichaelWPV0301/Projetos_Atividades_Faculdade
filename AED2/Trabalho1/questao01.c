#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "vet.h"

#define TAM 1000000
#define NUM 30
#define CalculaTempo(inicial,final) (double) (final - inicial)/CLOCKS_PER_SEC



int main(){

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_Seq, tempoTotal_Bin;
    double media1, desvioPadrao1, media2, desvioPadrao2;

    int valorAleatorio1, valorAleatorio2;
    Vetor_int vetor;
    Vetor_int vetorOrdenado;
    
    Vetor_double temposSeq;
    Vetor_double temposBin;
  

    //cria os vetores dinamicamente
    criaVetorInt(&vetor, TAM);
    criaVetorInt(&vetorOrdenado, TAM);
    criaVetorDouble(&temposSeq, NUM);
    criaVetorDouble(&temposBin, NUM);


    //Populando os dois vetores
    populaVetorAleatorio(vetor, TAM);
    populaVetorAleatorioOrdenado(vetorOrdenado, TAM);

    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
    
    for(int i=0; i<30; i++){

        printf("\nExecução %d\n", i);

        //15 casos dentro do vetor, 15 casos podendo estar fora
        if (i < 15){
           valorAleatorio1 = vetor[abs(rand()%TAM)];
            valorAleatorio2 = vetorOrdenado[abs(rand()%TAM)];
        }
        else{
            valorAleatorio1 = rand();
            valorAleatorio2 = rand();
        }
        
        //Busca Sequencial no vetor desordenado
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor, valorAleatorio1, TAM);
        tempoFinal_1 = clock();

        //Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        buscaBinariaVetor(vetorOrdenado, valorAleatorio2, TAM);
        tempoFinal_2 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal_Seq = CalculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Bin = CalculaTempo(tempoInicial_2, tempoFinal_2);
        insereDoubleVetor(temposSeq, i, tempoTotal_Seq, NUM);
        insereDoubleVetor(temposBin, i, tempoTotal_Bin, NUM);

        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_Seq);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_Bin);
        
    }
    media1 = calculaMediaDouble(temposSeq, NUM);
    desvioPadrao1 = calculaDesvioPadraoDouble(temposSeq, media1, NUM);
    media2 = calculaMediaDouble(temposBin, NUM);
    desvioPadrao2 = calculaDesvioPadraoDouble(temposBin, media2, NUM);
    
    printf("média da busca Sequencial: %f\n", media1);
    printf("desvio padrão da busca Sequencial: %f\n", desvioPadrao1);
    printf("média da busca Binária: %f\n", media2);
    printf("desvio padrão da busca Binária: %f\n", desvioPadrao2);

    return 0;
}