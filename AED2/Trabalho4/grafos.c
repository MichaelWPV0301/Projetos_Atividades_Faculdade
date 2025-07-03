#include "../include/grafos.h"

Grafo* criaGrafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo* gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr){
        int i;
        gr->nro_vertices  = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = eh_ponderado;
        gr->grau = (int*) calloc(nro_vertices, sizeof(int));
        gr->aresta = (int**) malloc(nro_vertices*sizeof(int*));
        for(i ; i<nro_vertices; i++){}

    }
}