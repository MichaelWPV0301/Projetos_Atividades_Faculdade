#include "../include/grafos.h"
struct Grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** aresta;
    float* pesos;
    int* grau;
};

Grafo* criaGrafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo* gr = (Grafo*) malloc(sizeof(struct Grafo));
    if(gr){
        int i;
        gr->nro_vertice  = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = eh_ponderado;

    }
}