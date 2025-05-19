#include "../Headers/Logica.h"
#include <time.h>
int partida()
{
    tPila mazo;
    int cantCartas=0;
    int puntajeJugador=0;
    crearPila(&mazo);
    system("cls");
    while(puntajeJugador<12)
    {
        cantCartas-=6;
        if(cantCartas<0)
        {
            vaciarPila(&mazo);
            cargaMazo(&mazo);
            cantCartas=40;
        }
        //Sacan Cartas
        //Hacen Cosas;
        puntajeJugador++;
    }
    ///Esto es para Mostrar Lo que tiene 
    //Se borrara Luego
    int i=0;
    char aux;
    while(sacarDePila(&mazo,&aux,sizeof(char)))
    {
        i++;
        printf("Carta %c,Numero Carta %d\n",aux,i);
    }
    return 1;
}
//a +2
//b +1
//c -1
//d -2
//e repite
//f espejo
int cargaMazo(tPila *mazo)
{
    char cartas[41]={"aaaaaabbbbbbbbbbccccccccddddddeeeeeeffff"};
    unsigned cantCartas=40;
    unsigned cartaElegida;
    srand(time(NULL));
    while(cantCartas>0)
    {
        cartaElegida=rand()%cantCartas;
        if(!ponerEnPila(mazo,cartas+cartaElegida,sizeof(char)))
            return 0;
        cantCartas--;
        cartas[cartaElegida]=cartas[cantCartas];
    }
    return 1;
}
