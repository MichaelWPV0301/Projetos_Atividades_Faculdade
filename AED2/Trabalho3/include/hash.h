#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "listaEncadeada.h"

typedef struct{
    Lista *tabHash;
    unsigned tamanhoTabHash;
    unsigned numElem;
} tipoHash;

void criaHash(unsigned tamanho);
void insereNoHash(tipoHash *h, Registro novo);

#endif