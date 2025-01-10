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
