#include <stdio.h>
#include <math.h>

typedef struct pontos
{
    float x;
    float y;
} pontos;

pontos *criarPonto(float x, float y){
    pontos *novo = (pontos*)malloc(sizeof(pontos));
    novo->x = x;
    novo->y =y;
    return novo;
}


void deletarPonto(pontos *p){
    free(p);
}


float distanciaDoisPontos(pontos *p1, pontos *p2){
    float distancia = pow((pow((p1->x)-(p2->x),2) +(pow((p1->y)-(p2->y),2))),1/2);
    return distancia;
}


void mudarCoordenadaX(pontos *p, float xNovo){
    p->x =xNovo;
}

void mudarCoordenadaY(pontos *p, float yNovo){
    p->y = yNovo;
}


void mudarCoordenadas(pontos *p, float xNovo, float yNovo){
    p->x = xNovo;
    p->y = yNovo;
}

