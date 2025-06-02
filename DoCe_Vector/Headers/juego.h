#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "PilaEstatica.h"
//Dificultades
#define FACIL 1
#define NORMAL 2
#define DIFICIL 3
//Estado PostJugadas
#define JUGOESPEJO 2
#define GANAR 1
#define PERDER 0
#define TURNONORMAL -1
//Cartas
#define SUMA2 'a'
#define SUMA1 'b'
#define RESTA1 'c'
#define RESTA2 'd'
#define REPITE 'e'
#define ESPEJO 'f'
//IA
#define CERCAGANAR 8
typedef struct{
    char nombre[20];
    int puntos;
    char mazo[4];
}tJugador;
typedef struct{
    char nombre[20];
    char cartaJugada;
    int turno;
}tTurno;

typedef int (*ACT)(void*,void*);

typedef struct{
    tJugador* jugador;
    tJugador* oponente;
    tPila* mazo;
    tPila* descartes;
    ACT decision;
}tRonda;

int iniciarJuego();
int imprimoRanking(void *d1, void *d2);
#endif // JUEGO_H_INCLUDED
