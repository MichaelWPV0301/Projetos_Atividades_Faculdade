#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "listaEncadeada.h"

typedef struct{
    Lista *tabHash;
    unsigned tamanhoTabHash;
    unsigned numElem;
} tipoHash;

void criaHash(tipoHash *h,unsigned tamanho);
void insereNoHash(tipoHash *h, Registro novo, int numeroRegistros);
int removeHash(tipoHash *h, int chave);
int buscaNoHash(tipoHash *h, int chave);
tipoHash* vetorEmHash(Registro alunos[], tipoHash* hash, int qtd);
#endif