#include <stdio.h>


void quickSortR(int v[], int inicio, int fim){
    int pivot, i, j, meio, aux;
    i = inicio;
    j = fim;
    meio = (i+j)/2;
    pivot = v[meio];
    while(i<=j){
        while(v[i]<pivot){i++;}
        while(v[j]>pivot){j--;}
        if(i<=j){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }
    if(inicio<j){quickSortR(v, inicio, j);}
    if(i<fim){quickSortR(v, i, fim);}
}


void quickSort(int v[], int tamVet){
    if(tamVet>1){
        quickSortR(v, 0, tamVet-1);
    }
}


int main(){
    int v[10] = {8,7,3,6,2,4,1,5,10,9};

    printf("array desordenado: ");
    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

    printf("\narray ordenado a partir do quicksort: ");
    quickSort(v, 10);

    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

}