#include<stdio.h>
#include<stdlib.h>

#define TAM 1000000

typedef struct tipoNo{
    struct tipoNo* prox;
    int valor;
}tipoNo;

typedef struct tipoLista{
    tipoNo* prim;
    int tamanho;
}Lista;

void populaVetorAleatorio(int* vetor, int tamanho){
    for (int i=0; i<tamanho; i++){
        vetor[i] = rand();
    }
}

void populaVetorAleatorioOrdenado(int* vetor, int tamanho){
    vetor[0] = 0;
    for (int i=1; i<tamanho; i++){
        vetor[i] = vetor[i-1] + abs(rand()%10);
    }
}

int buscaSequencialVetor(int* vetor, int valor, int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        if (vetor[i] == valor){
            return i;
        }
    }
    return -1;
}

int buscaBinaria(int* vetor, int valor, int tamanho){
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

int main(){
    int valorAleatorio1, valorAleatorio2, indice;
    int vetor[TAM];
    int vetorOrdenado[TAM];
    populaVetorAleatorio(vetor, TAM);
    populaVetorAleatorioOrdenado(vetorOrdenado, TAM);

    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
    
    for(int i=0; i<30; i++){

        //15 casos dentro do vetor, 15 casos podendo estar fora
        if (i < 15){
            valorAleatorio1 = vetor[abs(rand()%TAM)];
            valorAleatorio2 = vetorOrdenado[abs(rand()%TAM)];
        }
        else{
            valorAleatorio1 = rand();
            valorAleatorio2 = rand();
        }
        
        //Busca Sequencial no vetor desordenado
        indice = buscaSequencialVetor(vetor, valorAleatorio1, TAM);
    
        //Busca Binária no vetor ordenado
        indice = buscaBinaria(vetor, valorAleatorio2, TAM);

    }

    return 0;
}