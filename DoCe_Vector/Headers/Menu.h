#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stddef.h>
#define CONDJUGAR 'A'
#define CONDVERRANKING 'B'
#define CONDSALIR 'C'

typedef int (*Cond) (const void*);

void registrarInput(char *buffer, size_t tamBuffer, Cond cond);
int limpiarBuffer();

int condIgual3(const void *Buffer);

void mostrarMenu();
int menu(char opcion);

#endif // MENU_H_INCLUDED
