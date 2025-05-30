 #include <stdio.h>
 
void selectionSort(int v[], int tamVet){
    int x, y, menor, aux;
    x = 0;
    while(x<tamVet-1){
        menor = x;  y = x + 1;
        while(y<tamVet){
            if(v[y]<v[menor]){
                menor = y;
            }
            y++;
        }
        aux = v[x];
        v[x] = v[menor];
        v[menor] = aux;
        x++;
    }
}


 int main(){
    int v[10] = {8,7,3,6,2,4,1,5,10,9};

    printf("array desordenado: ");  
    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

    printf("\narray ordenado a partir do selectionSort: ");
    selectionSort(v, 10);

    for(int x=0;x<10;x++){
        printf("%d ", v[x]);
    }

}