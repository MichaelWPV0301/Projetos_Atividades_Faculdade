#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TAM 1000000
#define CalculaTempo(inicial,final) (double) (final - inicial)/CLOCKS_PER_SEC

typedef struct TipoNo{
    struct TipoNo* prox;
    int valor;
}TipoNo;

typedef struct Lista{
    TipoNo* prim;
    int tamanho;
}Lista;

typedef int* Vetor;

void criaVetor(Vetor* v, int tamanho){
    *v = (Vetor) malloc(sizeof(int)*tamanho);
}

void populaVetorAleatorio(Vetor vetor, int tamanho){
    for (int i=0; i<tamanho; i++){
        vetor[i] = rand();
    }
}

void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho){
    vetor[0] = 0;
    for (int i=1; i<tamanho; i++){
        vetor[i] = vetor[i-1] + abs(rand()%10);
    }
}

int buscaSequencialVetor(Vetor vetor, int valor, int tamanho){
    int i;
    for(i=0; i<tamanho; i++){
        if (vetor[i] == valor){
            return i;
        }
    }
    return -1;
}

int buscaBinaria(Vetor vetor, int valor, int tamanho){
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

    clock_t tempoInicial_1, tempoInicial_2, tempoFinal_1, tempoFinal_2;
    double tempoTotal_Seq, tempoTotal_Bin;

    int valorAleatorio1, valorAleatorio2;
    Vetor vetor;
    Vetor vetorOrdenado;

    //cria os vetores dinamicamente
    criaVetor(&vetor, TAM);
    criaVetor(&vetorOrdenado, TAM);

    //Populando os dois vetores
    populaVetorAleatorio(vetor, TAM);
    populaVetorAleatorioOrdenado(vetorOrdenado, TAM);

    //mudando a seed do rand() de acordo com o horário
    srand(time(NULL));
    
    for(int i=0; i<30; i++){

        printf("\nExecução %d\n", i);

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
        tempoInicial_1 = clock();
        buscaSequencialVetor(vetor, valorAleatorio1, TAM);
        tempoFinal_1 = clock();

        //Busca Binária no vetor ordenado
        tempoInicial_2 = clock();
        buscaBinaria(vetor, valorAleatorio2, TAM);
        tempoFinal_2 = clock();

        //Calculando o tempo das duas buscas
        tempoTotal_Seq = CalculaTempo(tempoInicial_1, tempoFinal_1);
        tempoTotal_Bin = CalculaTempo(tempoInicial_2, tempoFinal_2);

        printf("O tempo da busca sequencial foi %f segundos\n", tempoTotal_Seq);
        printf("O tempo da busca binaria foi %f segundos\n", tempoTotal_Bin);
        
    }

    return 0;
}