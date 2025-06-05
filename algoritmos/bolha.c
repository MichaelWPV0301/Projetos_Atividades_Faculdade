#include <stdio.h>

void bolha(int v[], int tamVet) {
    int x, y, aux;
    
    for(x = 0; x < tamVet - 1; x++) {
        for(y = 0; y < tamVet - 1 - x; y++) {
            if(v[y] > v[y + 1]) {
                aux = v[y];
                v[y] = v[y + 1];
                v[y + 1] = aux;
            }
        }
    }
}



 int main(){
    int v[10] = {8,7,3,6,2,4,1,5,10,9};

    printf("array desordenado: ");  
    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

    printf("\narray ordenado a partir do bolha: ");
    bolha(v, 10);

    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

}