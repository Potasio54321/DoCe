#include <stdio.h>
#include <stdlib.h>
#include "Headers/Grafica.h"
#include "Headers/Sistema.h"
int main()
{
    char Input[3];
    do
    {
        grafica(0);
        grafica(5);
        registrarInput(Input,sizeof(Input),condIgual3);
    } while (menu(Input[0])!=CONDSALIR);

    return 0;
}
//void jugarTurnoFacilIA(tJugador *maquina, int *seleccion)
//{
//    *seleccion = rand() % 3;
//}
//
//void jugarTurnoMedioIA(tJugador *maquina, int puntosJugador, int *seleccion)
//{
//    int i;
//
//    ///1- Si una carta de suma le da la victoria a maquina (llega a 12 puntos o más), jugarla.
//    if(maquina->puntos >= 10)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2 && maquina->puntos + 2 >= 12)
//            {
//                *seleccion = i;
//                return;
//            }
//            if(maquina->mazo[i]  == SUMA1 && maquina->puntos + 1 >= 12)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///2- Sumar puntos si maquina está cerca de ganar (puntos >= 8 ). Primero verifica si tiene +2 y luego +1
//    if(maquina->puntos >= 8)//en el dificil hacer que primero intente tirar +2 y luego +1
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2)
//            {
//                *seleccion = i;
//                return;
//            }
//            if(maquina->mazo[i]  == SUMA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///3- Si puntos del jugador >= 2, tira una carta aleatoria
//    if(puntosJugador >= 2)
//    {
//        *seleccion = rand() % 3;
//        return;
//    }
//    ///4- Si puntos del jugador == 1, tira la primera carta que no sea -2 (si es que hay alguna)
//    if(puntosJugador == 1)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i] != RESTA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///5- Si puntos del jugador == 0, tira la primera carta que no sea -2 y -1
//    if(puntosJugador == 0)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i] != RESTA2 && maquina->mazo[i] != RESTA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///6- Si el jugador tiene pocos puntos (2 o menos) y solo tiene cartas de -2 o -1, tira cualquiera
//    *seleccion = rand() % 3;
//
//    return;
//}
//
//void jugarTurnoDificilIA(tJugador *maquina, int puntosJugador, char cartaJugador, int *seleccion)
//{
//    int cartasBuenas = 0, i;
//
//    //cuento las cartas buneas (+2,+1,-2,-1)
//    for(i = 0; i < 3; i++)
//        if(maquina->mazo[i]  == SUMA2 || maquina->mazo[i]  == SUMA1 || maquina->mazo[i]  == RESTA2 || maquina->mazo[i]  == RESTA1)
//            cartasBuenas++;
//    ///1- Si una carta de suma le da la victoria a maquina (llega a 12 puntos o más), jugarla.
//    if(maquina->puntos >= 10)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2 && maquina->puntos + 2 >= 12)
//            {
//                *seleccion = i;
//                return;
//            }
//            if(maquina->mazo[i]  == SUMA1 && maquina->puntos + 1 >= 12)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///2- Si el jugador jugo carta negativa(-1, -2), usar espejo
//    if(cartaJugador == RESTA2 || cartaJugador == RESTA1)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == ESPEJO)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///3- si puntos del jugador >=8: usar -2, si no -1, si no REPITE(si es que tengo mas de 1 carta buena)
//    if(puntosJugador >= 8)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == RESTA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == RESTA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == REPITE && cartasBuenas >= 1)//aca me parecio que con 1 carta buena ya era suficiente para jugar un REPITE
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///4- si puntos del jugador >= 2, maquina usa la mejor carta posible: +2 -> -2 -> REPITE(con 1 buena) -> +1 -> -1 -> Repite -> Espejo
//    if(puntosJugador >= 2)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == RESTA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)//trato de buscar un +2 o -2 del mazo
//        {
//            if(maquina->mazo[i]  == REPITE && cartasBuenas >= 1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == RESTA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == REPITE)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == ESPEJO)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///5- si puntos del jugador == 1, maquina usa la mejor carta posible sin el -2: +2 -> +1 -> -1 -> Repite -> Espejo
//    if(puntosJugador == 1)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == RESTA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == REPITE)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == ESPEJO)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///6- si puntos del jugador == 0, maquina usa la mejor carta posible sin el -2 y -1: +2 -> +1 -> -1 -> Repite -> Espejo
//    if(puntosJugador == 0)
//    {
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA2)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == SUMA1)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == REPITE)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//        for(i = 0; i < 3; i++)
//        {
//            if(maquina->mazo[i]  == ESPEJO)
//            {
//                *seleccion = i;
//                return;
//            }
//        }
//    }
//    ///7- Si el jugador tiene pocos puntos (2 o menos) y solo tiene cartas de -2 o -1, trata de tira el -1 primero, y si no el -2
//    for(i = 0; i < 3; i++)
//    {
//        if(maquina->mazo[i]  == RESTA1)
//        {
//            *seleccion = i;
//            return;
//        }
//    }
//    for(i = 0; i < 3; i++)
//    {
//        if(maquina->mazo[i]  == RESTA2)
//        {
//            *seleccion = i;
//            return;
//        }
//    }
//    *seleccion = 0;//creo que no deberia llegar nunca aca, pero por las dudas manda la primer carta del mazo
//}
