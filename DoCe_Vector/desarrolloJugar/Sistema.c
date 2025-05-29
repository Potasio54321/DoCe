#include "Sistema.h"
void limpiarPantalla(void)
{
    system("cls");
}

void pausarPantalla(void)
{
    system("pause");
}

void limpiarBuffer(void)
{
    char cararterInvalido;
    while((cararterInvalido = getchar()) != '\n' && cararterInvalido != EOF);
}
