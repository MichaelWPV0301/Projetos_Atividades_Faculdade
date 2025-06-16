#include "../include/listaEncadeada.h" // Inclusão do cabeçalho da lista encadeada
#include "../include/vet.h"
#include "../include/arquivo.h"           // Inclusão do cabeçalho do vetor
#include <stdlib.h>                    // Para uso de malloc e free
#include <math.h>                      // Para funções matemáticas

// Cria e inicializa uma nova lista encadeada
void criaListaEncadeada(Lista *lista)
{
    lista = (Lista *)malloc(sizeof(Lista)); // Aloca memória para a estrutura da lista
    (lista)->prim = NULL;                   // Inicializa o ponteiro para o primeiro nó como NULL
}

// Libera toda a memória alocada para a lista encadeada
void liberaLista(Lista* lista)
{
    TipoNo* atual = lista->prim;
    TipoNo* aux;

    if (atual == NULL) { return; } // Se a lista estiver vazia, não há o que liberar

    // Percorre a lista liberando os nós um a um
    while (atual->prox)
    {
        aux = atual->prox; // Guarda referência ao próximo nó
        free(atual);       // Libera o nó atual
        atual = aux;       // Avança para o próximo
    }

    free(atual); // Libera o último nó

    // Reajusta ponteiros da lista para indicar que está vazia
    lista->prim = NULL;
    lista->ult = NULL;
}



int removeLista(Lista *lista, int chave){
    TipoNo *aux = lista->prim;
    if(aux){
        if(aux->dado.atributo == chave){
            lista->prim = aux->prox;
            free(aux);
            return 1;
        }
        while(aux->prox){
            if(aux->prox->dado.atributo == chave){
                aux->prox = aux->prox->prox;
                free(aux->prox);
                return 1;
            }
        }
    }
    return 0;
}



// Insere um novo valor ao final da lista encadeada
void insereNaLista(Lista *lista, TipoDado dadoNovo)
{
    TipoNo *novo = (TipoNo *)malloc(sizeof(TipoNo)); // Cria novo nó
    novo->dado = dadoNovo; // Atribui o valor
    novo->prox = NULL;   // Novo nó será o último, então prox é NULL

    TipoNo *aux = lista->ult; // Pega o último nó atual da lista
    lista->ult = novo;        // Atualiza o último nó para o novo nó

    if (aux == NULL)
    {
        // Lista estava vazia: o novo nó é também o primeiro
        lista->prim = novo;
        return;
    }

    aux->prox = novo; // Liga o nó anterior ao novo nó
}

// Transforma um vetor em uma lista encadeada, inserindo todos os elementos
/*
void vetorEmListaEncadeada(Lista *lista, Vetor vetor, int tamanhoVetor)
{
    for (int x = 0; x < tamanhoVetor; x++)
    {
        insereNaLista(lista, vetor[x]); // Insere cada elemento do vetor na lista
    }
}
*/

// Realiza busca sequencial (linear) na lista encadeada
int buscaPorIndentificador(Lista *lista, int chave)
{
    TipoNo *aux = lista->prim; // Começa pelo primeiro nó da lista
    while ((aux) && (aux->dado.atributo != chave))
    {
        aux = aux->prox;
    }
    if (aux)
    {
        return aux->dado.numeroRegistro; // Retorna o índice (posição) do valor encontrado
    }

    return -1; // Valor não encontrado
}
