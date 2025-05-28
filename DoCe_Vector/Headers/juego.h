#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "funcioneslista.h"
#include "Sistema.h"
#define GANAR 1
#define PERDER 0

typedef struct{
    char nombre[20];
    int puntos;
    char mazo[4];  ///preguntar
}tJugador;

typedef struct{
    char nombre[20];
    char cartaJugada;
    int turno;
}tTurno;
typedef int (*ACT)(void*,void*);
int iniciarJuego();
int jugar(tLista *list_turnos, tJugador *jugador, tJugador *maquina);

#endif // JUEGO_H_INCLUDED
