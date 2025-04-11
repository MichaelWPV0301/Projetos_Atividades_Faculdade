#include "ferramentas.h"
#include <time.h>
#include <math.h>

double calculaTempo(clock_t inicial, clock_t final)
{
    return (double)(final - inicial) / CLOCKS_PER_SEC;
}

double calculaMedia(double *vetor, int tamanho)
{
    double media = 0;
    for (int x = 0; x < tamanho; x++)
    {
        media += vetor[x];
    }
    if (tamanho)
    {
        return media / tamanho;
    }
    return -1;
}

double calculaDesvioPadrao(double *vetor, double media, int tamanho)
{
    double soma = 0;
    for (int x = 0; x < tamanho; x++)
    {
        soma += pow(vetor[x] - media, 2);
    }
    if (tamanho)
    {
        return sqrt(soma / tamanho);
    }
    return -1;
}
