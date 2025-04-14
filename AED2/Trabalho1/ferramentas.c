#include <stdio.h>
#include <time.h>
#include <math.h>

double calculaTempo(clock_t inicial, clock_t final)
{
    return (double)(final - inicial) / CLOCKS_PER_SEC;
}

double calculaMedia(double *tempos, int tamanho)
{
    double media = 0;
    for (int x = 0; x < tamanho; x++)
    {
        media += tempos[x];
    }
    if (tamanho)
    {
        return media / tamanho;
    }
    return -1;
}

double calculaDesvioPadrao(double *tempos, double media, int tamanho)
{
    double soma = 0;
    for (int x = 0; x < tamanho; x++)
    {
        soma += pow(tempos[x] - media, 2);
    }
    if (tamanho)
    {
        return sqrt(soma / tamanho);
    }
    return -1;
}

void mostraVetorDouble(double* vetor, int tamanho)
{   
    printf("[");

    if (tamanho)
    {
        printf("%f", vetor[0]);
    }

    for (int x = 1; x < tamanho; x++)
    {
        printf(", %f", vetor[x]);
    }

    printf("]");
}
