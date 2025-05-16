#include <stdio.h>
#include <stdlib.h>
#include "../include/avl.h"
#include "../include/arvore.h"
#include "../include/vet.h"
#include "../include/tempo.h"

#define TAM 1000000
#define NUM_TESTES 10

int main()
{
    srand(time(NULL));
    
    ArvoreBin *arvoreBin;
    ArvoreAvl *avl;
    Vetor vetor;
    int valorAleatorio, alturaArvBin, alturaArvAvl;

    FILE *arquivo = fopen("dados1_4.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Tipo, Execucao, tempo da Criação(s), Altura\n");

    inicializa(&arvoreBin);
    inicializaAvl(&avl);

    criaVetor(&vetor, TAM); 

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_ArvBin, tempoTotal_Avl, media1, media2;

    double temposCriaArvBin[NUM_TESTES];
    double temposCriaAvl[NUM_TESTES];

    for (int i = 1; i <= NUM_TESTES; i++)
    {
        inicializa(&arvoreBin);
        inicializaAvl(&avl);
        
        printf("\nExecucao %d:\n", i);
        populaVetorParcialmenteOrdenado(vetor, 10, TAM, 20);
                
        tempoInicial_1 = clock();
        vetorEmArvoreBin(vetor, &arvoreBin, TAM);
        tempoFinal_1 = clock();
        
        tempoInicial_2 = clock();
        vetorEmAvl(vetor, &avl, TAM);
        tempoFinal_2 = clock();

        tempoTotal_ArvBin = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Avl = calculaTempo(tempoInicial_2, tempoFinal_2);
        temposCriaArvBin[i-1] = tempoTotal_ArvBin;
        temposCriaAvl[i-1] = tempoTotal_Avl;
        
        
        alturaArvBin =  altura(arvoreBin);
        alturaArvAvl =  alturaAvl(avl);

        printf("Altura arvBin: %d\n", alturaArvBin);
        printf("Altura arvAvl: %d\n", alturaArvAvl);
        printf("O tempo da criacao da Arvore Binaria de Pesquisa foi %f segundos\n", tempoTotal_ArvBin);
        printf("O tempo da criacao da arvore Avl foi %f segundos\n", tempoTotal_Avl);

        fprintf(arquivo, "Arvore Binaria,       %d,         %f,         %d\n", i, tempoTotal_ArvBin, alturaArvBin);
        fprintf(arquivo, "Arvore AVL,          %d,         %f,         %d\n", i, tempoTotal_Avl, alturaArvAvl);
    
        liberaArvore(arvoreBin);
        liberaArvoreAvl(avl);
    }
    media1 = calculaMedia(temposCriaArvBin, NUM_TESTES);
    media2 = calculaMedia(temposCriaAvl, NUM_TESTES);

    printf("\nMedia da Criações das Arvores Binarias: %f\n", media1);
    printf("\nMedia da Criações das Arvores Avls: %f\n", media2);

    fprintf(arquivo, "Média Criações das Arvores Binárias:              %f\n", media1);
    fprintf(arquivo, "Média Criações das Arvores Avls:              %f\n", media2);


    liberaVetor(&vetor);
    fclose(arquivo);



    
    //Iteracao para mudar os dados
    char pause;
    printf("\nAperte enter para a parte 2 da questao 04.");
    scanf("%c", &pause);
    printf("\e[H\e[2J");



    // Parte 2 questão 4 -------------------------------------------------- 
    FILE *arquivo2 = fopen("dados2_4.csv", "w");
    if (arquivo2 == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo2, "Tipo, Execucao, tempo da Busca(s), Valor\n");

    Vetor vetor2;
    ArvoreBin *arvoreBin2;
    ArvoreAvl *avl2;
    
    inicializa(&arvoreBin2);
    inicializaAvl(&avl2);

    criaVetor(&vetor2, TAM);
    populaVetorAleatorio(vetor2, 100000000, TAM);
    vetorEmArvoreBin(vetor2, &arvoreBin2, TAM);
    vetorEmAvl(vetor2, &avl2, TAM);


    double temposBuscaArvBin[30];
    double temposBuscaArvAlv[30];

    for(int i = 1; i<=30; i++){

        inicializa(&arvoreBin2);
        inicializaAvl(&avl2);
        
        printf("\nExecucao %d\n", i);
        valorAleatorio = vetor2[abs(rand() % TAM)];

        tempoInicial_1 = clock();
        buscaArvoreBin(arvoreBin2, valorAleatorio);
        tempoFinal_1 = clock();

        tempoInicial_2 = clock();
        buscaArvoreAvl(avl2, valorAleatorio);
        tempoFinal_2 = clock();       

        tempoTotal_ArvBin = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Avl = calculaTempo(tempoInicial_2, tempoFinal_2);
        
        temposBuscaArvBin[i-1] = tempoTotal_ArvBin;
        temposBuscaArvAlv[i-1] = tempoTotal_Avl;


        printf("O tempo da busca binaria na Arvore Binaria de Pesquisa foi %.9f segundos\n", tempoTotal_ArvBin);
        printf("O tempo da busca binaria na Arvore Avl foi %.9f segundos\n", tempoTotal_Avl);

        //Escrevendo no arquivo 
        fprintf(arquivo2, "Arvore BP:,       %d,         %.9f,         %d\n", i, tempoTotal_ArvBin, valorAleatorio);
        fprintf(arquivo2, "Vetor Avl:,          %d,         %.9f,         %d\n", i, tempoTotal_Avl, valorAleatorio);
        
        liberaArvore(arvoreBin2);
        liberaArvoreAvl(avl2);
    }
    media1 = calculaMedia(temposBuscaArvBin, 30);
    media2 = calculaMedia(temposBuscaArvAlv, 30);

    printf("\nMedia das buscas das Arvores Binarias: %.9f\n", media1);
    printf("\nMedia das buscas das Arvores Avls: %.9f\n", media2);


    fprintf(arquivo2, "Média Buscas nas Arvores Binárias:              %.9f\n", media1);
    fprintf(arquivo2, "Média Buscas nas Arvores Avls:              %.9f\n", media2);


    liberaVetor(&vetor2);
    
    fclose(arquivo2);
    return 0;
}
