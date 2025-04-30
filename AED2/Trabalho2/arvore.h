#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_iNCLUDED

typedef struct Arvore{
    struct Arvore* esquerda;
    struct Arvore* direita;
    int valor;
} Arvore;

Arvore* inicializa();
Arvore* insereArvoreBinaria(Arvore** raiz, int valor);
Arvore* caminhaPos(Arvore* raiz);
Arvore* caminhaPre(Arvore* raiz);
Arvore* caminhaCentral(Arvore* raiz);


#endif