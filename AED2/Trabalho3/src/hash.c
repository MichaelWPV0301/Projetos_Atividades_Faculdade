#include "../include/hash.h"
#include "../include/listaEncadeada.h"

void criaHash(tipoHash *h, unsigned tamanho){
    h->tabHash = (Lista*) malloc(sizeof(Lista)*tamanho);
    for(int x=0; x<tamanho; x++){
        criaListaEncadeada(&(h->tabHash[x]));
    }
    h->numElem = 0;
    h->tamanhoTabHash = tamanho;

}

void insereNoHash(tipoHash *h, Registro novo){
    unsigned pos = novo.matricula % h->tamanhoTabHash;


    //buscaPorIndentificador: Vai verificar se existi alguém com a chave especificada, se não tiver retorna NULL
    if(buscaPorIndentificador(&(h->tabHash[pos]), novo.matricula) == NULL){
        insereNaLista(&(h->tabHash[pos]), novo);
    }
}
void removeHash(tipoHash *h, int chave ){
    unsigned pos = chave % h->tamanhoTabHash;

    //tem que fazer a remove da lista encadeada.

}

Registro* buscaNoHash(tipoHash *h, int chave ){
    unsigned pos = chave % h->tamanhoTabHash;

    //buscaPorIndentificador: Vai verificar se existi alguém com a chave especificada, se não tiver retorna NULL
    return buscaPorIndentificador(&(h->tabHash[pos]), chave);

}