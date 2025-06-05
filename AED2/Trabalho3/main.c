//#include "include/avl.h"
#include "include/arquivo.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#define N 30

        Registro novo ;
void gerarArquivo(const char * nomeArquivo, int num){
    FILE *fp  = fopen(nomeArquivo, "wb");
    if(!fp){
        perror("Erro ao criar arquivo de dados");
    }
    
    
    srand((unsigned) time(NULL));
    for(int i=1;i<=N;i++){

    }

}
int main(){}

