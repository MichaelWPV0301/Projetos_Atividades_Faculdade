#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "../include/vet.h"

typedef struct ArvoreAvl ArvoreAvl;

int altura(ArvoreAvl *arvoreAvl);

int fator_balanceamento(ArvoreAvl *arvoreAvl);

int max(int ha, int hb);

void atualizar_altura(ArvoreAvl *avl);
void caminhaPos(ArvoreAvl *raiz);
void caminhaPre(ArvoreAvl *raiz);
void caminhaCentral(ArvoreAvl *raiz);
void inicializaAvl(ArvoreAvl **raiz);
void vetorEmAvl(Vetor vetor, ArvoreAvl **ptrRaiz, int tam);

ArvoreAvl *rotacao_simples_direita(ArvoreAvl *arvore1);
ArvoreAvl *rotacao_simples_esquerda(ArvoreAvl *arvore1);

ArvoreAvl *rotacao_dupla_direita(ArvoreAvl *arvore1);
ArvoreAvl *rotacao_dupla_esquerda(ArvoreAvl *arvore1);

ArvoreAvl *inserirAvl(ArvoreAvl *avl, int chave);

#endif