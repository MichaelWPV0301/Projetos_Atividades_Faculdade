#include <stdio.h>
#include <time.h>
#include "../include/vet.h"
#include "../include/arvore.h"

#define TAM 1000000
#define NUM_TESTES 30


int main(){
    Arvore* arvore;
    Vetor vetor;
    int valorAleatorio;

    FILE *arquivo = fopen("dados_3.csv", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Execucao, tempo(s), valor\n");



    inicializa(&arvore);
    criaVetor(&vetor, TAM);

    
    srand(time(NULL));
    populaVetorAleatorio(vetor, TAM);
    vetorEmArvore(vetor, &arvore, TAM);



    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vet, tempoTotal_arvore;
    double media1, media2;

    double temposVet[NUM_TESTES];
    double temposArvore[NUM_TESTES];



    for(int i=1; i<=NUM_TESTES; i++){
        printf("\nExecucao %d\n", i);
        valorAleatorio = vetor[abs(rand() % TAM)];
        
        tempoInicial_1 = clock();
        buscaArvore(arvore, valorAleatorio);
        tempoFinal_1 = clock();

        tempoInicial_2 = clock();
        buscaBinariaVetor(vetor, valorAleatorio, 20);
        tempoFinal_2 = clock();


        tempoTotal_arvore = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_vet = calculaTempo(tempoInicial_2, tempoFinal_2);


        temposArvore[i-1] = tempoTotal_arvore;
        temposVet[i-1] = tempoTotal_vet;

        printf("O tempo da busca binaria no vetor foi %f segundos\n", tempoTotal_vet);
        printf("O tempo da busca binaria na Arvore foi %f segundos\n", tempoTotal_arvore);

        //Escrevendo no arquivo 
        fprintf(arquivo, "Arvore:       %d,         %f,         %d\n", i, tempoTotal_vet, valorAleatorio);
        fprintf(arquivo, "Vetor:          %d,         %f,         %d\n", i, tempoTotal_arvore, valorAleatorio);

    }
    media1 = calculaMedia(temposVet, NUM_TESTES);
    media2 = calculaMedia(temposArvore, NUM_TESTES);

    printf("\nMedia da Busca no vetor: %f\n", media1);
    printf("\nMedia da Busca na Arvore: %f\n", media2);

    liberaVetor(&vetor);

    fclose(arquivo);
    return 0;

}