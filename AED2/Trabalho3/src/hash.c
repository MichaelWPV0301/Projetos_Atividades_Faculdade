#include "../include/hash.h"
#include "../include/listaEncadeada.h"
#include <stdlib.h>

void criaHash(tipoHash *h, unsigned tamanho){
    h->tabHash = (Lista*) malloc(sizeof(Lista)*tamanho);
    for(int x=0; x<tamanho; x++){
        criaListaEncadeada(&(h->tabHash[x]));
    }
    h->numElem = 0;
    h->tamanhoTabHash = tamanho;
}

void insereNoHash(tipoHash *h, Registro novo, int numeroReg){
    unsigned pos = novo.matricula % h->tamanhoTabHash;

    //buscaPorIndentificador: Vai verificar se existe alguém com a chave especificada, se não tiver retorna NULL
    if(buscaPorIndentificador(&(h->tabHash[pos]), novo.matricula) == NULL){
        TipoDado dadoNovo;
        dadoNovo.atributo = novo.matricula;
        dadoNovo.numeroRegistro = numeroReg;
        insereNaLista(&(h->tabHash[pos]), dadoNovo);
    }
}

int removeHash(tipoHash *h, int chave ){
    unsigned pos = chave % h->tamanhoTabHash;

    return  removeLista(&(h->tabHash[pos]), chave);
    //tem que fazer a remove da lista encadeada.
}

int buscaNoHash(tipoHash *h, int chave ){
    unsigned pos = chave % h->tamanhoTabHash;

    //buscaPorIndentificador: Vai verificar se existi alguém com a chave especificada, se não tiver retorna NULL
    return buscaPorIndentificador(&(h->tabHash[pos]), chave);
}

tipoHash* vetorEmHash(Registro* alunos, tipoHash* hash, int qtd){
    for(int x = 0; x<qtd; x++){
        insereNoHash(hash, alunos[x], x);
    }
}