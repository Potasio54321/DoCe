#include <stdio.h>
#include <stdlib.h>
#include "Headers/Grafica.h"
#include "Headers/Sistema.h"
int main()
{
    char Input[3];
    grafica(0);
    do
    {
        grafica(5);
        registrarInput(Input,sizeof(Input),condIgual3);
    } while (menu(Input[0])!=CONDSALIR);

    return 0;
}
