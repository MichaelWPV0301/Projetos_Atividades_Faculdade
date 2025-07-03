typedef struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** aresta;
    float** pesos;
    int* grau;
} Grafo;

Grafo* criaGrafo(int nro_vertices, int grau_max, int eh_ponderado);
void liberaGrafo(Grafo* grafo);

