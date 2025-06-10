#include "main.h"
int main()
{
    char Input[3];
    grafica(INTRODUCCION);
    do
    {
        grafica(MENU);
        registrarInput(Input,sizeof(Input),condIgual3);
    } while (menu(Input[0])!=CONDSALIR);
    return 0;
}
