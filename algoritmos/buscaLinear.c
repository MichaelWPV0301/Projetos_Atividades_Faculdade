#include <stdio.h>

int buscaLinear(int v[], int chave, int tamVet){
    int x;
    for(x=0;x<tamVet;x++){
        if(v[x]==chave){
            return 1;
        }
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
    result = buscaLinear(v, chave, tamVet);
    
    if(result){
        printf("Chave encontrada no vetor");
    }
    else{
        printf("Chave nao encontrada no vetor");
    }
}