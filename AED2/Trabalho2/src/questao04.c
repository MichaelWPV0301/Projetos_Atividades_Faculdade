#include <stdio.h>
#include <stdlib.h>
#include "../include/avl.h"
#include "../include/arvore.h"
#include "../include/vet.h"
#include "../include/tempo.h"

#define TAM 1000000       // Tamanho do vetor e número de nós das árvores
#define NUM_TESTES 10     // Número de execuções para medir tempos

int main()
{
    srand(time(NULL));   // Inicializa a seed para números aleatórios
    
    ArvoreBin *arvoreBin;   // Ponteiro para árvore binária comum
    ArvoreAvl *avl;         // Ponteiro para árvore AVL
    Vetor vetor;            // Vetor de elementos para popular as árvores
    int valorAleatorio, alturaArvBin, alturaArvAvl;

    // Abre arquivo CSV para salvar resultados da criação das árvores
    FILE *arquivo = fopen("dados1_4.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    // Escreve cabeçalho do arquivo CSV
    fprintf(arquivo, "Tipo, Execucao, tempo da Criação(s), Altura\n");

    inicializa(&arvoreBin);   // Inicializa árvore binária vazia
    inicializaAvl(&avl);      // Inicializa árvore AVL vazia

    criaVetor(&vetor, TAM);   // Cria vetor de tamanho TAM

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_ArvBin, tempoTotal_Avl, media1, media2;

    double temposCriaArvBin[NUM_TESTES];  // Armazena tempos criação árvore binária
    double temposCriaAvl[NUM_TESTES];     // Armazena tempos criação árvore AVL

    // Loop para criar árvores e medir tempo e altura
    for (int i = 1; i <= NUM_TESTES; i++)
    {
        inicializa(&arvoreBin);    // Reinicializa árvore binária
        inicializaAvl(&avl);       // Reinicializa árvore AVL
        
        printf("\nExecucao %d:\n", i);
        populaVetorParcialmenteOrdenado(vetor, 10, TAM, 30);  // Preenche vetor parcialmente ordenado
        
        tempoInicial_1 = clock();
        vetorEmArvoreBin(vetor, &arvoreBin, TAM, 1);          // Constrói árvore binária com vetor
        tempoFinal_1 = clock();
        
        tempoInicial_2 = clock();
        vetorEmAvl(vetor, &avl, TAM);                          // Constrói árvore AVL com vetor
        tempoFinal_2 = clock();
        
        printf("passou");
        tempoTotal_ArvBin = calculaTempo(tempoInicial_1, tempoFinal_1);  // Calcula tempo criação árvore binária
        tempoTotal_Avl = calculaTempo(tempoInicial_2, tempoFinal_2);     // Calcula tempo criação árvore AVL
        temposCriaArvBin[i-1] = tempoTotal_ArvBin;
        temposCriaAvl[i-1] = tempoTotal_Avl;
        
        alturaArvBin =  altura(arvoreBin);      // Calcula altura da árvore binária
        alturaArvAvl =  alturaAvl(avl);         // Calcula altura da árvore AVL

        printf("Altura arvBin: %d\n", alturaArvBin);
        printf("Altura arvAvl: %d\n", alturaArvAvl);
        printf("O tempo da criacao da Arvore Binaria de Pesquisa foi %f segundos\n", tempoTotal_ArvBin);
        printf("O tempo da criacao da arvore Avl foi %f segundos\n", tempoTotal_Avl);

        // Salva os dados no arquivo CSV
        fprintf(arquivo, "Arvore Binaria,       %d,         %f,         %d\n", i, tempoTotal_ArvBin, alturaArvBin);
        fprintf(arquivo, "Arvore AVL,          %d,         %f,         %d\n", i, tempoTotal_Avl, alturaArvAvl);
    
        liberaArvore(arvoreBin);      // Libera memória da árvore binária
        liberaArvoreAvl(avl);          // Libera memória da árvore AVL
    }
    // Calcula média dos tempos de criação das árvores
    media1 = calculaMedia(temposCriaArvBin, NUM_TESTES);
    media2 = calculaMedia(temposCriaAvl, NUM_TESTES);

    printf("\nMedia da Criações das Arvores Binarias: %f\n", media1);
    printf("\nMedia da Criações das Arvores Avls: %f\n", media2);

    // Salva médias no arquivo CSV
    fprintf(arquivo, "Média Criações das Arvores Binárias:              %f\n", media1);
    fprintf(arquivo, "Média Criações das Arvores Avls:              %f\n", media2);

    liberaVetor(&vetor);       // Libera vetor
    fclose(arquivo);           // Fecha arquivo da parte 1


    // Iteração para mudar os dados (parte 2)
    char pause;
    printf("\nAperte enter para a parte 2 da questao 04.");
    scanf("%c", &pause);
    printf("\e[H\e[2J");  // Limpa a tela


    // Parte 2 da questão 4 -------------------------------------------------- 
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
    populaVetorAleatorio(vetor2, 100000000, TAM); // Popula vetor com valores aleatórios
    vetorEmArvoreBin(vetor2, &arvoreBin2, TAM, 1); // Constroi árvore binária
    vetorEmAvl(vetor2, &avl2, TAM);                 // Constroi árvore AVL


    double temposBuscaArvBin[30]; // Tempos para buscas na árvore binária
    double temposBuscaArvAlv[30]; // Tempos para buscas na árvore AVL

    // Loop para medir tempos de busca
    for(int i = 1; i<=30; i++){

        inicializa(&arvoreBin2);
        inicializaAvl(&avl2);
        
        printf("\nExecucao %d\n", i);
        valorAleatorio = vetor2[abs(rand() % TAM)]; // Valor aleatório do vetor

        tempoInicial_1 = clock();
        buscaArvoreBin(arvoreBin2, valorAleatorio);  // Busca na árvore binária
        tempoFinal_1 = clock();

        tempoInicial_2 = clock();
        buscaArvoreAvl(avl2, valorAleatorio);        // Busca na árvore AVL
        tempoFinal_2 = clock();       

        tempoTotal_ArvBin = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Avl = calculaTempo(tempoInicial_2, tempoFinal_2);
        
        temposBuscaArvBin[i-1] = tempoTotal_ArvBin;
        temposBuscaArvAlv[i-1] = tempoTotal_Avl;

        printf("O tempo da busca binaria na Arvore Binaria de Pesquisa foi %.9f segundos\n", tempoTotal_ArvBin);
        printf("O tempo da busca binaria na Arvore Avl foi %.9f segundos\n", tempoTotal_Avl);

        // Escreve resultados no arquivo CSV
        fprintf(arquivo2, "Arvore BP:,       %d,         %.9f,         %d\n", i, tempoTotal_ArvBin, valorAleatorio);
        fprintf(arquivo2, "Arvore Avl:,          %d,         %.9f,         %d\n", i, tempoTotal_Avl, valorAleatorio);
        
        liberaArvore(arvoreBin2);    // Libera memória árvore binária
        liberaArvoreAvl(avl2);       // Libera memória árvore AVL
    }
    // Calcula médias dos tempos de busca
    media1 = calculaMedia(temposBuscaArvBin, 30);
    media2 = calculaMedia(temposBuscaArvAlv, 30);

    printf("\nMedia das buscas das Arvores Binarias: %.9f\n", media1);
    printf("\nMedia das buscas das Arvores Avls: %.9f\n", media2);

    // Salva médias no arquivo CSV
    fprintf(arquivo2, "Média Buscas nas Arvores Binárias:              %.9f\n", media1);
    fprintf(arquivo2, "Média Buscas nas Arvores Avls:              %.9f\n", media2);

    liberaVetor(&vetor2);   // Libera vetor
    fclose(arquivo2);       // Fecha arquivo da parte 2

    return 0;
}
