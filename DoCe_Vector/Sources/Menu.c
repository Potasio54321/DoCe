#include "..\Headers\Menu.h"
#include "..\Headers\Logica.h"
#define TAMBUFFER 256
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// Registro
void registrarInput(char *buffer, size_t tamBuffer, Cond cond)
{
    fgets(buffer, tamBuffer, stdin);
    while(!cond(buffer) || limpiarBuffer(buffer))
    {
        puts("Ingreso Invalido");
        fgets(buffer, tamBuffer, stdin);
    }
}
int limpiarBuffer(char *bufferOriginal)
{
    char bufferLimpieza[TAMBUFFER];
    if(strchr(bufferOriginal,'\n')!=NULL)
        return 0;
    while (strchr(bufferLimpieza,'\n')==NULL)
    {
        fgets(bufferLimpieza, TAMBUFFER, stdin);
    }
    return 1;
}
// Condiciones
int condIgual3(const void *Buffer)
{
    const char *buffer = Buffer;
    return buffer[2] == '\0';
}
int menu(char opcion)
{
    system("cls");
    mostrarMenu();
    switch (opcion)
    {
    case CONDJUGAR:
        puts("Estas Jugando");
        partida();
        system("pause");
        system("cls");
        mostrarMenu();
        break;
    case CONDVERRANKING:
        puts("Estas viendo el Ranking");
        break;
    case CONDSALIR:
        puts("Saliendo del programa...");
        break;
    default:
        puts("Opcion no valida, por favor intente de nuevo.");
    }
    return opcion;
}
void mostrarMenu()
{
    puts("=============== MENU ===============");
    printf("%c) Jugar.\n",CONDJUGAR);
    printf("%c) Ver Ranking.\n",CONDVERRANKING);
    printf("%c) Salir.\n",CONDSALIR);
    puts("Ingrese solo un Caracter");
}
