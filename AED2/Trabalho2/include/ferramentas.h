#ifndef FERRAMENTAS_INCLUDED  // Evita múltiplas inclusões desse cabeçalho
#define FERRAMENTAS_INCLUDED

#include <time.h>   // Necessário para trabalhar com clock_t e medir tempo
#include <stdio.h>  // Para funções de entrada e saída como printf

Arvore* buscaArvore(Arvore* raiz, int dado);
// Calcula o tempo decorrido entre dois instantes (em segundos)
double calculaTempo(clock_t inicial, clock_t final);

// Calcula a média dos valores de um vetor de doubles
double calculaMedia(double *tempos, int tamanho);

// Calcula o desvio padrão dos valores de um vetor de doubles
double calculaDesvioPadrao(double *tempos, double media, int tamanho);

// Exibe os elementos de um vetor de doubles na tela
void mostraVetorDouble(double* vetor, int tamanho);

#endif  // Fim da diretiva de inclusão condicional
