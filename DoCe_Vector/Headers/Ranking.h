#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#define TAMNOMBRE 248
#define ERR_MEM 1
#define ERR_CURL 2
#define ERR_CJSON 3
#include <stddef.h>
typedef struct
{
    char nombre[TAMNOMBRE];
    size_t partidasGanadas;
}tJugador;
typedef struct
{
    char* respuesta;
    size_t tam;
}tMemoria;
#define URLAPI "https://algoritmosapi.azurewebsites.net/api/doce/arreglo"
int verRanking();
#endif // RANKING_H_INCLUDED
