#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "vet.h"


void criaVetorInt(Vetor_int* v, int tamanho){
    *v = calloc(tamanho,sizeof(int));

}

void criaVetorDouble(Vetor_double* v, int tamanho){
    *v = calloc(tamanho,sizeof(double));
}

void copiaVetor(Vetor_int destino, Vetor_int entrada, int tamanho){
    for (int x=0; x<tamanho; x++){
        destino[x] = entrada[x];
    }
}

int insereDoubleVetor(Vetor_double v, int pos, double valor, int tamanho){
    if(pos<tamanho){
        v[pos] = valor;
        return 1;
    }
    return 0;
}

void populaVetorAleatorio(Vetor_int vetor, int tamanho){
    for (int i=0; i<tamanho; i++){
        vetor[i] = rand();
    }
}

void populaVetorAleatorioOrdenado(Vetor_int vetor, int tamanho){
    vetor[0] = 0;
    for (int i=1; i<tamanho; i++){
        vetor[i] = vetor[i-1] + abs(rand()%10);
    }
}

int buscaSequencialVetor(Vetor_int vetor, int valor, int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        if (vetor[i] == valor){
            return i;
        }
    }
    return -1;
}

int buscaBinariaVetor(Vetor_int vetor, int valor, int tamanho){
    int inicio, meio, fim;
    inicio = 0;
    fim = tamanho-1;
    while (inicio <= fim){
        meio = inicio + (fim - inicio)/2;
        if (vetor[meio] < valor){
            inicio = meio + 1;
        }
        else if (vetor[meio] > valor){
            fim = meio -1;
        }
        else{
            return meio;
        }
    }
    return -1;
}
double calculaMediaDouble(Vetor_double v, int tamanho){
    double media = 0;
    for(int x=0; x<tamanho; x++){
        media += v[x];
    }
    if(tamanho){
        return media/tamanho;
    }
    return -1;
}

double calculaDesvioPadraoDouble(Vetor_double v, double media, int tamanho){
    double soma = 0;
    for(int x=0; x<tamanho; x++){
        soma += pow(v[x]-media,2);
    }
    if(tamanho){
        return sqrt(soma/tamanho);
    }
    return -1;
}

