#ifndef PILA_ESTATICA_H_INCLUDED
#define PILA_ESTATICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CANTTAMMAX 40+40*sizeof(size_t)

///Metodo Estatico
typedef struct
{
    ///Buffer de Cosas
    char pila[CANTTAMMAX];
    size_t tope;
}
tPila;

void crearPila(tPila* pPila);
void vaciarPila(tPila*pPila);

int verTopePila(const tPila*pPila,void* dato,size_t tamDato);
int ponerEnPila(tPila*pPila,const void* dato,size_t tamDato);
int sacarDePila(tPila*pPila,void* dato,size_t tamDato);

int pilaLlena(const tPila*pPila,size_t tamDato);
int pilaVacia(const tPila*pPila);
#endif // PILA_ESTATICA_H_INCLUDED
