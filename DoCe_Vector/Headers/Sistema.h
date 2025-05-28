#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define rango(n,li,ls)((n)<(li)||(n)>(ls)?0:1)
typedef int (*Cond) (const void*);
void limpiarPantalla(void);
void pausarPantalla(void);
void registrarInput(char *buffer, size_t tamBuffer, Cond cond);
int strAInt(int *numero,const char* str);
//Funciones Condicion
int condIgual3(const void *Buffer);
int condInsercionAceptable(const void *Buffer);
int esNombreValido(const char *nombre);
#endif // SISTEMA_H_INCLUDED
