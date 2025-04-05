#ifndef VETOR_H_INCLUDED
#define VETOR_H_INCLUDED

typedef int* Vetor;

void criaVetor(Vetor* v, int tamanho);
void populaVetorAleatorio(Vetor vetor, int tamanho);
void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho);
int buscaSequencialVetor(Vetor vetor,int valor, int tamanho);
int buscaBinaria(Vetor vetor, int valor, int tamanho);


#endif