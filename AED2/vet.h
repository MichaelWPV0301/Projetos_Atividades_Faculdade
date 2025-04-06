#ifndef VETOR_H_INCLUDED
#define VETOR_H_INCLUDED

typedef int* Vetor_int;
typedef double* Vetor_double;


void criaVetorInt(Vetor_int* v, int tamanho);
void criaVetorDouble(Vetor_double* v, int tamanho);
int insereDoubleVetor(Vetor_double v, int pos, double valor, int tamanho);
void populaVetorAleatorioOrdenado(Vetor_int vetor, int tamanho);
void populaVetorAleatorio(Vetor_int vetor, int tamanho);
int buscaSequencialVetor(Vetor_int vetor,int valor, int tamanho);
int buscaBinariaVetor(Vetor_int vetor, int valor, int tamanho);
double calculaMediaDouble(Vetor_double v, int tamanho);
double calculaDesvioPadraoDouble(Vetor_double v, double media, int tamanho);



#endif