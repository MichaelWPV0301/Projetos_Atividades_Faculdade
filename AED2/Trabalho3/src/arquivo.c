#include "../include/arquivo.h"

// Inclui bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro
{
    int idAcesso;
    int idUsuario;
    char  dataHora[20];
    char ip[16];
    int status;


}Registro;



