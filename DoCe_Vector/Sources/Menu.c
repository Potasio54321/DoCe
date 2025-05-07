#include "..\Headers\Menu.h"
#include <stdio.h>
int menu()
{
    char opcion;
    char buffer[TAMBUFFER];
    do
    {
        puts("=============== MENU ===============");
        puts("A) Jugar.");
        puts("B) Ver Ranking.");
        puts("C) Salir.");
        fgets(buffer, sizeof(buffer), stdin);
        if(buffer[2]!= '\0')
            opcion = '\0';
        else
            opcion = buffer[0];
        switch (opcion)
        {
            case 'A':
                puts("Estas Jugando");
                break;
            case 'B':
                puts("Estas viendo el Ranking");
                break;
            case FINCOND:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida, por favor intente de nuevo.\n");
        }
    } while (opcion != FINCOND);
    return 0;
}
