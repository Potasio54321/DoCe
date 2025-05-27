#ifndef LOGICA_H_INCLUDED
#define LOGICA_H_INCLUDED
#include "PilaEstatica.h"
typedef struct
{
    char nombre[32];
    int resultado;
}tJugador;
typedef struct
{
    tJugador jugadorAPI;
    int puntaje;
    char cartas[3];
}tJugadorPartida;
int partida();
int cargaMazo(tPila *mazo);

#endif // LOGICA_H_INCLUDED
