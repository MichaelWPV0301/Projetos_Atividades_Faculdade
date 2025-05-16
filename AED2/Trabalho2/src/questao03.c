#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vet.h"
#include "../include/arvore.h"
#include "../include/ferramentas.h"

#define TAM 10000000
#define NUM_TESTES 30


int main(){
    srand(time(NULL));
    
    ArvoreBin* arvore;
    Vetor vetor;
    int valorAleatorio;
    char pause;

    FILE *arquivo = fopen("dados_3.csv", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Execucao, tempo(s), valor\n");



    inicializa(&arvore);
    criaVetor(&vetor, TAM);
 
    printf("\nAperte enter para a criacao do Vetor com 1 milhão de elementos.");
    scanf("%c", &pause);
    populaVetorAleatorio(vetor, 100000000, TAM);
    
    printf("\nAperte enter para a criacao da Arvore Binaria de Pesquisa com 1 milhão de elementos(nós).");
    scanf("%c", &pause);
    vetorEmArvoreBin(vetor, &arvore, TAM);

    printf("\nAperte enter para Continuar o codigo.");    
    scanf("%c", &pause);
    
    quickSort(vetor, TAM);
    


    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vet, tempoTotal_arvore;
    double media1, media2;

    double temposVet[NUM_TESTES];
    double temposArvore[NUM_TESTES];



    for(int i=1; i<=NUM_TESTES; i++){
        printf("\nExecucao %d\n", i);
        valorAleatorio = vetor[abs(rand() % TAM)];
        
        tempoInicial_1 = clock();
        buscaArvoreBin(arvore, valorAleatorio);
        tempoFinal_1 = clock();

        tempoInicial_2 = clock();
        buscaBinariaVetor(vetor, valorAleatorio, 20);
        tempoFinal_2 = clock();


        tempoTotal_arvore = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_vet = calculaTempo(tempoInicial_2, tempoFinal_2);


        temposArvore[i-1] = tempoTotal_arvore;
        temposVet[i-1] = tempoTotal_vet;

        printf("O tempo da busca binaria no vetor foi %.9f segundos\n", tempoTotal_vet);
        printf("O tempo da busca binaria na Arvore foi %.9f segundos\n", tempoTotal_arvore);

        //Escrevendo no arquivo 
        fprintf(arquivo, "Arvore:       %d,         %.9f,         %d\n", i, tempoTotal_arvore, valorAleatorio);
        fprintf(arquivo, "Vetor:          %d,         %.9f,         %d\n", i, tempoTotal_vet, valorAleatorio);

    }
    
    media1 = calculaMedia(temposVet, NUM_TESTES);
    media2 = calculaMedia(temposArvore, NUM_TESTES);

    printf("\nMedia da Busca no vetor: %.9f\n", media1);
    printf("\nMedia da Busca na Arvore: %.9f\n", media2);

    fprintf(arquivo, "Media vetor:         %.9f\n", media1);
    fprintf(arquivo, "Media arvore:         %.9f\n", media2);
    
    liberaVetor(&vetor);

    fclose(arquivo);
    return 0;

}