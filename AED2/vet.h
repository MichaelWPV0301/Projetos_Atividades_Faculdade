#ifndef VETOR_H_INCLUDED
#define VETOR_H_INCLUDED

typedef int* Vetor_int;
typedef double* Vetor_double;


void criaVetorInt(Vetor_int* v, int tamanho);
void criaVetorDouble(Vetor_double* v, int tamanho);
void copiaVetor(Vetor_int destino, Vetor_int entrada, int tamanho);
int insereDoubleVetor(Vetor_double v, int pos, double valor, int tamanho);
void populaVetorAleatorioOrdenado(Vetor_int vetor, int tamanho);
void populaVetorAleatorio(Vetor_int vetor, int tamanho);
int buscaSequencialVetor(Vetor_int vetor,int valor, int tamanho);
int buscaBinariaVetor(Vetor_int vetor, int valor, int tamanho);
double calculaMediaDouble(Vetor_double v, int tamanho);
double calculaDesvioPadraoDouble(Vetor_double v, double media, int tamanho);
void bolha(Vetor_int v, int tamVet);
void selectionSort(Vetor_int v, int tamVet);
void insertionSort(Vetor_int v, int tamVet);
void quickSortR(Vetor_int v, int inicio, int fim);
void quickSort(Vetor_int v, int tamVet);
void mergeSortR(Vetor_int v, Vetor_int aux, int inicio, int fim);
void mergeSort(Vetor_int v, int tamVet);

#endif