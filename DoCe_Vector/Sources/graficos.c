#include "../Headers/Grafica.h"
#include "../Headers/Sistema.h"
#include "../Headers/Juego.h"
#include "../Headers/API.h"
#include <stdio.h>
#include <stdlib.h>

void grafica(int opc)
{
    switch(opc)
    {
    case INTRODUCCION:
        printf("\n\t\t***************************************************************************");
        printf("\n\t\t///////////////////////////////////////////////////////////////////////////");
        printf("\n\t\t**\t                                                      ________   **");
        printf("\n\t\t**\t                                                     |+12     || **");
        printf("\n\t\t**\t     _____      _______    ________    ____      ____|___     || **");
        printf("\n\t\t**\t    |     \\    /  ___  \\  /    ___|| |  __||    | D      ||   || **");
        printf("\n\t\t**\t    |  __  \\   | |   | || |   ||     |  |       |   O    ||+12|| **");
        printf("\n\t\t**\t    | |  |  || | |   | || |   ||     |  __||    |     C  ||___|| **");
        printf("\n\t\t**\t    | |__|  || | |___| || |   ||__   |  |       |       E||      **");
        printf("\n\t\t**\t    |______//  |_______||  \\______|| |____||    |________||      **");
        printf("\n\t\t**                                                                       **");
        printf("\n\t\t**                                                                       **");
        printf("\n\t\t///////////////////////////////////////////////////////////////////////////");
        printf("\n\t\t***************************************************************************\n\n\n");
        printf("\t\tUn desarrollo de \"VECTOR\" ");
        printf("\n\t\t\t - DELGADO MAILEN ");
        printf("\n\t\t\t - MAMANI LUCAS ");
        printf("\n\t\t\t - LOPEZ MANUEL \n\n");
        pausarPantalla();
        break;

    case VICTORIA: //victoria
        limpiarPantalla();
        printf("\n\t************************************************************************************************");
        printf("\n\t////////////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                            **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**     ___    ___   __    _______    _________    ______    ______     __        __           **");
        printf("\n\t**     \\  \\  /  // |  || /    ___|| |___   ___|| /  __  \\  ||  _  \\   |  ||     /  \\\\         **");
        printf("\n\t**      \\  \\/  //  |  || |   ||         |  ||    | |  | || || |_| ||  |  ||    /    \\\\        **");
        printf("\n\t**       \\    //   |  || |  ||          |  ||    | |  | || |     //   |  ||   / /__\\ \\\\       **");
        printf("\n\t**        \\  //    |  || |   ||___      |  ||    | |__| || ||  |\\  \\  |  ||  /   __   \\\\      **");
        printf("\n\t**         \\//     |__||  \\______||     |__||    |______|| ||__| \\__\\ |__|| /___/  \\___\\\\     **");
        printf("\n\t**                                                                                            **");
        printf("\n\t////////////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t************************************************************************************************\n\n\n");
        printf("\t\t\t Felicitaciones. Te has impuesto con maestria ante la IA.\n\n");
        break;
    case DERROTA://Derrota
        limpiarPantalla();
        printf("\n\t*****************************************************************************************");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                     **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**     _____      ____     _____      _____     _______    _________       __          **");
        printf("\n\t**    |     \\    |  __|| ||  _  \\   ||  _  \\   /  ___  \\  |___   ___||    /  \\\\        **");
        printf("\n\t**    |  __  \\   |  |_   || |_| ||  || |_| ||  | |   | ||     |  ||      /    \\\\       **");
        printf("\n\t**    | |  |  || |  __|| ||     //  ||     //  | |   | ||     |  ||     / /__\\ \\\\      **");
        printf("\n\t**    | |__|  || |  |_   ||  |\\  \\  ||  |\\  \\  | |___| ||     |  ||    /   __   \\\\     **");
        printf("\n\t**    |______//  |____|| ||__| \\__\\ ||__| \\__\\ |_______||     |__||   /___/  \\___\\\\    **");
        printf("\n\t**                                                                                     **");
        printf("\n\t**                                                                                     **");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t*****************************************************************************************\n\n\n");
        printf("\t\t\t Tu oponente se impone. Vuelve a intentarlo.\n\n");
        break;
 case MAZOMEZCLADO: // Mazo mezclado
        limpiarPantalla();
        printf("\n\t*********************************************************************************");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                        ¡El mazo ha sido mezclado!                          **");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t*********************************************************************************\n\n\n");
        break;

    case RANKING: //Ranking
        limpiarPantalla();
        printf("\n\t*****************************************************************************************");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t**                                                                                     **");
        printf("\n\t**     _____          __        __     __     __   __     __   __     __    _______    **");
        printf("\n\t**    ||  _  \\       /  \\\\     |  \\   |  ||  |  | /  // |  || |  \\   |  || /   ____||  **");
        printf("\n\t**    || |_| ||     /    \\\\    |   \\  |  ||  |  |/  //  |  || |   \\  |  || |  | ____   **");
        printf("\n\t**    ||     //    / /__\\ \\\\   |  |\\\\ |  ||  |     \\\\   |  || |  |\\\\ |  || |  ||__  || **");
        printf("\n\t**    ||  |\\  \\   /   __   \\\\  |  |\\     ||  |      \\\\  |  || |  |\\     || |  |___| || **");
        printf("\n\t**    ||__| \\__\\ /___/  \\___\\\\ |__| \\____||  |__|\\___\\\\ |__|| |__| \\____|| \\_______//  **");
        printf("\n\t**                                                                                     **");
        printf("\n\t**                                                                                     **");
        printf("\n\t/////////////////////////////////////////////////////////////////////////////////////////");
        printf("\n\t*****************************************************************************************\n\n\n");
        printf("\t\t\t Cada punto cuenta, cada victoria te acerca a la cima.\n\n");
        break;
    case MENU:
        limpiarPantalla();
        printf("\n\n");
        printf("\t*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+\n");
        printf("\t||    __    ___   _____    __   _    __   __      ||\n");
        printf("\t||   |  \\  /  || |   __|| |  \\ | || | |  | ||     ||\n");
        printf("\t||   |   \\/   || |  ||_   |   \\| || | |  | ||     ||\n");
        printf("\t||   | |\\  /| || |    _|| | |\\   || | |  | ||     ||\n");
        printf("\t||   | | \\/ | || |  ||_   | | \\  || |  \\_/ ||     ||\n");
        printf("\t||   |_|    |_|| |_____|| |_|  \\_||  \\____//      ||\n");
        printf("\t||                                                ||\n");
        printf("\t|| %c) Jugar.                                      ||\n",CONDJUGAR);
        printf("\t|| %c) Ver Ranking.                                ||\n",CONDVERRANKING);
        printf("\t|| %c) Salir.                                      ||\n",CONDSALIR);
        printf("\t||             Ingrese solo un Caracter           ||\n");
        printf("\t*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+\n");
        break;
    case INGRESOJUGADOR:
        limpiarPantalla();
        printf("\n\t\t ========================================================");
        printf("\n\t\t|\t\t   INGRESO DE JUGADOR                    |");
        printf("\n\t\t|\t\t   --------------------                  |");
        printf("\n\t\t|\t Ingrese su nombre o 0 para volver al menu.      |");
        printf("\n\t\t ========================================================\n\n");
        printf("Jugador: ");
        break;

    case INGRESODIFICULTAD:
        limpiarPantalla();
        printf("\n\t\t =======================================================");
        printf("\n\t\t|\t\t   DIFICULTAD                          |");
        printf("\n\t\t|\t\t   ----------                          |");
        printf("\n\t\t|\t [1] FACIL                                     |");
        printf("\n\t\t|\t [2] MEDIO                                     |");
        printf("\n\t\t|\t [3] DIFICIL                                   |");
        printf("\n\t\t =======================================================\n\n");
        printf("Seleccione nivel de dificultad: ");
        break;
    case JUEGAJUGADOR:
        limpiarPantalla();
        printf("\nTurno de Usted.\n");
        printf("-------------------------\n");
        printf("=====================================================\n");
        break;
    case JUEGAMAQUINA:
        limpiarPantalla();
        printf("\nTurno de la Maquina.\n");
        printf("-------------------------\n");
        printf("=====================================================\n");
        break;
    }
}
int menu(char opcion)
{
    system("cls");
    switch (opcion)
    {
    case CONDJUGAR:
        iniciarJuego();
        break;
    case CONDVERRANKING:
        grafica(RANKING);
        recuperar_de_api();
        break;
    case CONDSALIR:
        puts("Saliendo del programa...");
        break;
    default:
        puts("Opcion no valida, por favor intente de nuevo.");
    }
    system("pause");
    system("cls");
    return opcion;
}
void print_carta_mas1() {

    printf(" _____\n");
    printf("|+1   |\n");
    printf("|     |\n");
    printf("|   +1|\n");
    printf("|_____|\n");

}

// Carta -1
void print_carta_menos1() {

    printf("\t _____\n");
    printf("\t|-1   |\n");
    printf("\t|     |\n");
    printf("\t|   -1|\n");
    printf("\t|_____|\n");

}

// Carta +2
void print_carta_mas2() {

   printf("\t _____\n");
    printf("\t|+2   |\n");
    printf("\t|     |\n");
    printf("\t|   +2|\n");
    printf("\t|_____|\n");
}

// Carta -2
void print_carta_menos2() {

    printf("\t _____\n");
    printf("\t|-2   |\n");
    printf("\t|     |\n");
    printf("\t|   -2|\n");
   printf("\t|_____|\n");

}

// Carta REPETIR
void print_carta_repetir() {

    printf("\t _____\n");
    printf("\t|REP  |\n");
    printf("\t| <-> |\n");
    printf("\t|  REP|\n");
    printf("\t|_____|\n");

}

// Carta ESPEJO
void print_carta_espejo() {

    printf("\t _____\n");
    printf("\t|ES   |\n");
    printf("\t| PE  |\n");
    printf("\t|   JO|\n");
   printf("\t|_____|\n");
}
