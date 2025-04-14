#ifndef FERRAMENTAS_INCLUDED
#define FERRAMENTAS_INCLUDED

#include <time.h>
#include <stdio.h>

double calculaTempo(clock_t inicial, clock_t final);

double calculaMedia(double *tempos, int tamanho);

double calculaDesvioPadrao(double *tempos, double media, int tamanho);

void mostraVetorDouble(double* vetor, int tamanho);

#endif