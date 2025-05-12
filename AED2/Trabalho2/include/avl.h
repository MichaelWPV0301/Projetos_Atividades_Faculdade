#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct ArvoreAvl{
    struct ArvoreAvl* esquerda;
    struct ArvoreAvl* direita;
    int dado;
    int altura;
}ArvoreAvl;

int altura(ArvoreAvl* arvoreAvl);

int fator_balanceamento(ArvoreAvl* arvoreAvl);

int max(int ha,int hb);

void atualizar_altura(ArvoreAvl* avl);
void caminhaPos(ArvoreAvl* raiz);
void caminhaPre(ArvoreAvl* raiz);
void caminhaCentral(ArvoreAvl* raiz);
void inicializa(ArvoreAvl** raiz);


ArvoreAvl* rotacao_simples_direita(ArvoreAvl* arvore1);
ArvoreAvl* rotacao_simples_esquerda(ArvoreAvl* arvore1);


ArvoreAvl* rotacao_dupla_direita(ArvoreAvl* arvore1);
ArvoreAvl* rotacao_dupla_esquerda(ArvoreAvl* arvore1);

ArvoreAvl* inserirAvl(ArvoreAvl* avl, int chave);



#endif