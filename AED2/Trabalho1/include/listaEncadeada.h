#ifndef LISTA_ENCADEADA_H_INCLUDED  // Evita múltiplas inclusões do mesmo cabeçalho
#define LISTA_ENCADEADA_H_INCLUDED
#include "vet.h"  // Inclui definições relacionadas a Vetor 

// Define o nó da lista encadeada
typedef struct TipoNo
{
    struct TipoNo *prox;  // Ponteiro para o próximo nó
    int valor;            // Valor armazenado no nó
} TipoNo;

// Define a estrutura da lista encadeada
typedef struct Lista
{
    TipoNo *prim;  // Ponteiro para o primeiro nó da lista
    TipoNo *ult;   // Ponteiro para o último nó da lista
} Lista;

// Cria e inicializa uma lista encadeada vazia
void criaListaEncadeada(Lista **lista);

// Libera toda a memória alocada para a lista e seus nós
void liberaLista(Lista* lista);

// Insere um novo valor no final da lista
void insereNaLista(Lista *lista, int valor);

// Converte um vetor em uma lista encadeada, inserindo os elementos do vetor na lista
void vetorEmListaEncadeada(Lista *lista, Vetor vetor, int tamanhoVetor);

// Realiza busca sequencial por um valor na lista encadeada
// Se encontrar, retorna a posição do valor 
// Se não encontrar, retorna -1
int buscaSequencialLista(Lista *lista, int valor);

#endif  // Fim da diretiva de inclusão condicional
