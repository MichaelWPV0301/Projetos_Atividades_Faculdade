#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/vet.h"
#include "../include/arvore.h"
#include "../include/tempo.h"

#define TAM 1000000       // Tamanho do vetor e número de nós da árvore
#define NUM_TESTES 30     // Número de execuções para medir o tempo

int main(){

    srand(time(NULL));    // Inicializa a seed para números aleatórios
    
    ArvoreBin* arvore;
    Vetor vetor;
    int valorAleatorio;
    char pause;

    // Abre arquivo CSV para salvar os resultados dos testes
    FILE *arquivo = fopen("dados_3.csv", "w");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    // Escreve o cabeçalho do arquivo CSV
    fprintf(arquivo, "Execucao, tempo(s), valor\n");

    inicializa(&arvore);  // Inicializa a árvore binária vazia
    criaVetor(&vetor, TAM);  // Aloca vetor de tamanho TAM

    // Aguarda o usuário pressionar Enter para criar o vetor ordenado
    printf("\nPressione Enter para a criacao do Vetor com 1 milhao de elementos: ");
    scanf("%c", &pause);
    populaVetorAleatorioOrdenado(vetor, 100, TAM);  // Preenche vetor com valores ordenados aleatórios
    printf("\n--vetor criado com sucesso--\n");
    
    // Aguarda o usuário pressionar Enter para criar a árvore binária a partir do vetor ordenado
    printf("\nPressione Enter para a criacao da Arvore Binaria de Pesquisa com 1 milhao de elementos(nós): ");
    scanf("%c", &pause);
    vetorOrdenadoEmArvoreBin(vetor, &arvore, 0, TAM-1);  // Constrói árvore binária de pesquisa balanceada
    printf("\n--arvore criada com sucesso--\n");

    // Aguarda o usuário pressionar Enter para iniciar os testes de busca
    printf("\nPressione Enter para realizar as buscas: ");    
    scanf("%c", &pause);

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_vet, tempoTotal_arvore;
    double media1, media2;

    double temposVet[NUM_TESTES];    // Array para armazenar tempos de busca no vetor
    double temposArvore[NUM_TESTES]; // Array para armazenar tempos de busca na árvore

    // Loop para realizar múltiplas execuções e medir o tempo das buscas
    for(int i=1; i<=NUM_TESTES; i++){
        printf("\nExecucao %d\n", i);
        valorAleatorio = vetor[abs(rand() % TAM)];  // Escolhe um valor aleatório do vetor
        
        // Mede o tempo de busca na árvore binária
        tempoInicial_1 = clock();
        buscaArvoreBin(arvore, valorAleatorio);
        tempoFinal_1 = clock();

        // Mede o tempo de busca binária no vetor
        tempoInicial_2 = clock();
        buscaBinariaVetor(vetor, valorAleatorio, 20);
        tempoFinal_2 = clock();

        // Calcula o tempo total das buscas em segundos
        tempoTotal_arvore = calculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_vet = calculaTempo(tempoInicial_2, tempoFinal_2);

        // Armazena os tempos em arrays para cálculo posterior da média
        temposArvore[i-1] = tempoTotal_arvore;
        temposVet[i-1] = tempoTotal_vet;

        // Exibe os tempos obtidos para cada execução
        printf("O tempo da busca binaria no vetor foi %.9f segundos\n", tempoTotal_vet);
        printf("O tempo da busca binaria na Arvore foi %.9f segundos\n", tempoTotal_arvore);

        // Escreve os resultados no arquivo CSV
        fprintf(arquivo, "Arvore:       %d,         %.9f,         %d\n", i, tempoTotal_arvore, valorAleatorio);
        fprintf(arquivo, "Vetor:          %d,         %.9f,         %d\n", i, tempoTotal_vet, valorAleatorio);

    }
    
    // Calcula a média dos tempos para as buscas no vetor e na árvore
    media1 = calculaMedia(temposVet, NUM_TESTES);
    media2 = calculaMedia(temposArvore, NUM_TESTES);

    // Exibe as médias calculadas na tela
    printf("\nMedia da Busca no vetor: %.9f\n", media1);
    printf("\nMedia da Busca na Arvore: %.9f\n", media2);

    // Salva as médias no arquivo CSV
    fprintf(arquivo, "Media vetor:         %.9f\n", media1);
    fprintf(arquivo, "Media arvore:         %.9f\n", media2);
    
    liberaVetor(&vetor);     // Libera a memória alocada para o vetor
    liberaArvore(arvore);    // Libera a memória da árvore binária

    fclose(arquivo);         // Fecha o arquivo de saída

    return 0;                // Finaliza o programa com sucesso

}
