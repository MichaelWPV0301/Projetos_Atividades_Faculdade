#include <stdio.h>


void inserctionSort(int v[], int tamVet){
    int x, y, pivot;
    x = 1;
    while(x<tamVet){
        y=x-1;
        pivot = v[x];
        while(y>=0 && pivot < v[y]){
            v[y+1] = v[y];
            y--;
        }
        v[y+1] = pivot;
        x++;
    }
}

int main(){
    int v[10] = {8,7,3,6,2,4,1,5,10,9};

    printf("array desordenado: ");  
    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

    printf("\narray ordenado a partir do inserctionSort: ");
    inserctionSort(v, 10);

    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

}