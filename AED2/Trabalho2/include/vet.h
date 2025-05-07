#ifndef VETOR_H_INCLUDED  // Evita inclusões múltiplas desse cabeçalho
#define VETOR_H_INCLUDED

typedef int* Vetor;  // Define um tipo Vetor como ponteiro para int

// Aloca dinamicamente um vetor com o tamanho especificado
void criaVetor(Vetor* vetor, int tamanho);

// Libera a memória alocada para o vetor
void liberaVetor(Vetor* vetor);

// Copia os elementos de um vetor de entrada para um vetor de destino
void copiaVetor(Vetor destino, Vetor entrada, int tamanho);

// Exibe os elementos do vetor na tela
void mostraVetor(Vetor vetor, int tamanho);

// Preenche o vetor com números aleatórios em ordem crescente (positivos)
void populaVetorAleatorioOrdenado(Vetor vetor, int limite, int tamanho);

void populaVetorParcialmenteOrdenado(Vetor vetor, int limite, int tamanho);

// Preenche o vetor com números aleatórios (sem ordem)
void populaVetorAleatorio(Vetor vetor, int limite, int tamanho);

// Realiza busca sequencial por um valor no vetor
// Se encontrar, retorna a posição do valor 
// Se não encontrar, retorna -1
int buscaSequencialVetor(Vetor vetor, int valor, int tamanho);

// Realiza busca binária por um valor no vetor (pressupõe vetor ordenado)
// Se encontrar, retorna a posição do valor 
// Se não encontrar, retorna -1
int buscaBinariaVetor(Vetor vetor, int valor, int tamanho);

// Ordena o vetor usando o algoritmo Bubble Sort
void bolha(Vetor vetor, int tamVet);

// Ordena o vetor usando o algoritmo Selection Sort
void selectionSort(Vetor vetor, int tamVet);

// Ordena o vetor usando o algoritmo Insertion Sort
void insertionSort(Vetor vetor, int tamVet);

// Função recursiva auxiliar para Quick Sort
void quickSortR(Vetor vetor, int inicio, int fim);

// Interface principal para Quick Sort
void quickSort(Vetor vetor, int tamVet);

// Função recursiva auxiliar para Merge Sort
void mergeSortR(Vetor vetor, Vetor aux, int inicio, int fim);

// Interface principal para Merge Sort
void mergeSort(Vetor vetor, int tamVet);

#endif  // Fim da diretiva de inclusão condicional
