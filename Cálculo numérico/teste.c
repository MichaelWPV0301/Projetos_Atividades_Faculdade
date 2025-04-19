
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Executando o código em C ...\n");
     int retorno = system("python3 trabalho.py");
     if(retorno==0){
        printf("código em python executado com sucesso\n");
        }
        else{
        printf("Erro ao tentar executar o código em python\n");
    }
    return 0;
}