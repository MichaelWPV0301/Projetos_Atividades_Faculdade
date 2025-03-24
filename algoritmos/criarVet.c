#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

int buscaBinaria(int v[], int chave, int tamVet){
    int inicio, fim, meio;
    inicio = 0;
    fim=tamVet-1;
    while(inicio<=fim){
        meio = (inicio+fim)/2;
        if(chave<v[meio]){ fim = meio-1; }
        else if(chave>v[meio]){ inicio = meio+1; }
        else{ return 1;}
    }
    return 0;
}
void mergeSortR(int v[], int aux[], int inicio, int fim){
   int a,b,k;
    if(inicio<fim){
        int meio = (inicio+fim)/2;
        mergeSortR(v, aux, inicio, meio);
        mergeSortR(v, aux, meio+1, fim);
        a=inicio; b=meio+1; k=inicio;
    
    while(a<=meio && b<=fim){
        if(v[a]<v[b]){ aux[k] = v[a]; a++;}
        else         { aux[k] = v[b]; b++; }
        k++;        
    }
    while(a<=meio){aux[k] = v[a];  a++;  k++;}
    while(b<=fim){aux[k] = v[b];   b++;  k++;}
    
    for(k=inicio; k<=fim; k++){
        v[k] = aux[k];
        }
    }
}


void mergeSort(int v[], int tamVet){
    int *aux;
    aux = (int*) malloc(sizeof(int)*tamVet);
    mergeSortR(v, aux, 0, tamVet-1);
    free(aux);
}
int main(){
    int *vet = (int *)malloc(sizeof(int) * 1000000);
    int inicio, fim, chave;
    double tempo;
    inicio = clock();
    srand(time(NULL));
    for(int x=0;x<1000000;x++){
        vet[x] = rand() %1000000+1;
    }
    fim = clock();
    tempo = ((double)fim-inicio)/CLOCKS_PER_SEC;
    printf("O tempo de execução foi de: %f\n", tempo);
    inicio = clock();
    mergeSort(vet, 1000000);
    fim = clock();
    tempo = ((double)fim-inicio)/CLOCKS_PER_SEC;
    printf("O tempo de execução da ordenação foi de: %f\n", tempo);
    inicio = clock();
    buscaBinaria(vet, vet[0],1000000);
    fim = clock();
    printf("O tempo de execução da busca linear foi de: %f\n", tempo);
}