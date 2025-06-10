#include "../include/hash.h"
#include "../include/listaEncadeada.h"

void criaHash(tipoHash *h, unsigned tamanho){
    h->tabHash = (Lista*) malloc(sizeof(Lista)*tamanho)
    for(int x=0; x<tamanho; x++){
        criaListaEncadeada(&(h->tabHash[x]));
    }
    h->numElem = 0;
    h->tamanhoTabHash = tamanho;

}

void insereNoHash(tipoHash *h, Registro novo){
    unsigned pos = novo.matricula % h->tamanhoTabHash;

    if(buscaPorIndentificador(&(h->tabHash[pos]), novo.matricula) == NULL){
        insereNaLista(tabHash[pos], novo);
    }
}