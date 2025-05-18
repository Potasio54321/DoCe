#include <stdio.h>
#include <stdlib.h>
#include "Headers/Menu.h"
int main()
{
    char Input[3];
    mostrarMenu();
    do
    {
        registrarInput(Input,sizeof(Input),condIgual3);
    } while (menu(Input[0])!=CONDSALIR);

    return 0;
}
