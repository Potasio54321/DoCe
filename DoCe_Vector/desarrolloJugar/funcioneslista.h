#ifndef FUNCIONESLISTA_H_INCLUDED
#define FUNCIONESLISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{ ///ESTRUCTURA DEL NODO Q APUNTA A OTRO NODO
    void *info;
    size_t taminfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;///LA LISTA ES PUNTERO A PUNTERO DE NODO

///PONER -> CONST VOID * DATO
void crearLista(tLista *pl); ///ES PONER EL PUNTERO EN NULL
int ponerPrimeroLista (tLista *pl, const void *dt, unsigned tam);///ES PONER DESENGANCHANDO EL PL Y ENGANCHANDO EL NUE
int sacarPrimeroLista (tLista *pl, void *dt, unsigned tam);///USA AUX VERIFICO Q HAYA ALGO, LUEGO COPIO Y DESENGANCHO Y FREE(AUX)

int ponerPosLista (tLista *pl, const void *dt, unsigned tam, unsigned pos);
int ponerUltLista (tLista *pl, const void *dt, unsigned tam);
int ponerOrdenLista(tLista *pl, const void *dt, unsigned tam, int (*cmp)(const void*, const void*));

int sacarElemLista (tLista *pl, void *dt, unsigned tam, int (*cmp)(const void*, const void*));
int sacarElemOrdenadoLista (tLista *pl, void *dt, unsigned tam, int (*cmp)(const void*, const void*));

void recorrerLista(tLista *pl, void (*accion)(void*,void*), void*param);
void mostrarENTEROLista(void *pl,void*param);


void eliminarDuplicados(tLista *pl, int (*cmp)(const void*, const void*),
                                     void (*accion)(void*,void*));


int comparaEntero(const void *a, const void *b);

void vaciarLista(tLista *pl);
///Para buscar el menor y ordenar necesito 4 funciones: llamadora con compentero, buscar menor, intercambiar
///LLAMADORA: lleva la lista y la funcion de comparacionEnteros
void ordenarSeleccionLista(tLista *pl, int (*cmp)(const void*, const void*));
///funcion que busca el menor(tiene la funcion de comparacion)
tLista *buscarMenor(tLista*nodoDesde,int (*cmp)(const void *, const void*));
///Intercambiar
void intercambiar(tLista *a, tLista *b);
#endif // FUNCIONESLISTA_H_INCLUDED
