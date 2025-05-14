#include <stdio.h>
#include <stdlib.h>
#include "../include/avl.h"
#include "../include/arvore.h"
#include "../include/ferramentas.h"

#define TAM 1000000
#define NUM_TESTES 10

int main()
{
    srand(time(NULL));
    ArvoreBin *arvoreBin;
    ArvoreAvl *avl;
    Vetor vetor;
    int valorAleatorio;

    FILE *arquivo = fopen("dados_4.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    fprintf(arquivo, "Execucao, tempo da Criação(s), tempo da Busca(s), Dado buscado\n");

    inicializa(&arvoreBin);
    inicializaAvl(&avl);

    criaVetor(&vetor, TAM);

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_ArvBin, tempoTotal_Avl;

    double temposArvBin[NUM_TESTES];
    double temposAvl[NUM_TESTES];

    for (int i = 1; i <= NUM_TESTES; i++)
    {
        printf("\nExecucao %d\n", i);
        populaVetorAleatorio(vetor, 1000000, TAM);

        valorAleatorio = vetor[abs(rand() % TAM)];

        tempoInicial_1 = clock();
        vetorEmArvoreBin(vetor, arvoreBin, TAM);
        tempoFinal_1 = clock();

        tempoInicial_2 = clock();
        vetorEmAvl(vetor, &avl, TAM);
        tempoFinal_2 = clock();
    }
}
