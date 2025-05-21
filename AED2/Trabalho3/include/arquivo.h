#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

// Inclui bibliotecas padrão
#include <stdio.h>


typedef struct Registro Registro;

FILE* abrirArquivo(const char* nomeArquivo, const char* modo);
void fecharArquivo(FILE* ponteiroArquivo);
void escreverRegistro(FILE* arquivo, Registro *reg, long offset);
void adicionarRegistro(FILE* arquivo, long offset);
Registro lerRegistro(FILE* arquivo, long offset);
Registro  lerRegistroPorNumero(FILE* arquivo, int numeroRegistro);
int obterNumeroRegistros(FILE* arquivo);



#endif