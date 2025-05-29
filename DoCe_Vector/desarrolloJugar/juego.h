#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <ctype.h>
#include "stdlib.h"
#include "stdio.h"
#include "funcioneslista.h"
#include "Sistema.h"
#define GANAR 1
#define PERDER 0


typedef struct{
    char nombre[20];
    int puntos;
    char mazo[3];  ///preguntar
}tJugador;

typedef struct{
    char nombre[20];
    char cartaJugada;
    int turno;
}tTurno;

void selectdificultad(int *d);

int iniciarJuego();

int jugar(tLista *list_turnos, tJugador *jugador, int *puntosIA);

int ingresoJugador(tJugador *jugador);

void generarInforme(tLista *list_turnos,tJugador jugador, char* ganador,int puntosIA);

int esNombreValido(const char *nombre);

void selectdificultad(int *d);

int finalizaJuego(tLista *list_turnos, tJugador *jugador, tJugador *maquina, int opc, int dificultad);

int jugarTurno(tLista *list_turnos, tJugador *jugador, tJugador *maquina,int opc, int dificultad);


void grafica(int opc);

#endif // JUEGO_H_INCLUDED
