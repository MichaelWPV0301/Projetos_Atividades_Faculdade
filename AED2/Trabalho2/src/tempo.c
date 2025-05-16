#include <stdio.h>   // Para funções de entrada/saída como printf
#include <time.h>    // Para medir tempo usando clock_t
#include <math.h>    // Para funções matemáticas como pow e sqrt

// Calcula o tempo decorrido (em segundos) entre dois instantes de clock
double calculaTempo(clock_t inicial, clock_t final)
{
    return (double)(final - inicial) / CLOCKS_PER_SEC;
}

// Calcula a média dos valores de um vetor de doubles
double calculaMedia(double *tempos, int tamanho)
{
    double media = 0;
    for (int x = 0; x < tamanho; x++)
    {
        media += tempos[x];  // Soma todos os valores
    }
    if (tamanho)
    {
        return media / tamanho;  // Retorna a média aritmética
    }
    return -1;  // Retorna -1 caso o tamanho seja zero
}

// Calcula o desvio padrão dos valores de um vetor de doubles
double calculaDesvioPadrao(double *tempos, double media, int tamanho)
{
    double soma = 0;
    for (int x = 0; x < tamanho; x++)
    {
        soma += pow(tempos[x] - media, 2);  // Soma dos quadrados das diferenças
    }
    if (tamanho)
    {
        return sqrt(soma / tamanho);  // Raiz quadrada da média das diferenças quadradas
    }
    return -1;  // Retorna -1 caso o tamanho seja zero
}

// Exibe os valores de um vetor de doubles no formato [x, y, z, ...]
void mostraVetorDouble(double* vetor, int tamanho)
{   
    printf("[");  // Início do vetor

    if (tamanho)
    {
        printf("%f", vetor[0]);  // Imprime o primeiro elemento sem vírgula
    }

    for (int x = 1; x < tamanho; x++)
    {
        printf(", %f", vetor[x]);  // Imprime os demais separados por vírgula
    }

    printf("]");  // Fim do vetor
}
