#include <stdio.h>

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

int main(){
    int tamVet, result, chave;
    scanf("%d%*c", &tamVet);
    int v[tamVet];
    for(int x=0;x<tamVet;x++){
        scanf("%d", &v[x]);
    }

    scanf("%d%*c", &chave);
    result = buscaBinaria(v, chave, tamVet);
    
    if(result){
        printf("Chave encontrada no vetor");
    }
    else{
        printf("Chave nao encontrada no vetor");
    }
}