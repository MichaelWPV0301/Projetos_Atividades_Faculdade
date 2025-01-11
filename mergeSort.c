#include <stdio.h>
#include <stdlib.h>


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
    int v[10] = {8,7,3,6,2,4,1,5,10,9};

    printf("array desordenado: ");  
    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

    printf("\narray ordenado a partir do mergeSort: ");
    mergeSort(v, 10);

    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

}