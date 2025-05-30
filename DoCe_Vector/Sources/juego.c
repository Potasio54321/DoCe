#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "..\Headers\juego.h"
#include "..\Headers\Menu.h"
#include "..\Headers\Grafica.h"
#include "..\Headers\ListaCircular.h"
#include "..\Headers\Sistema.h"
int iniciarJuego();
int jugar(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina);
int VerGanador(const tJugador *jugador,const tJugador *maquina);
//Funciones Mostrar
void mostrarUltimaCartaJugadaJugador(const tJugador* jugador);
void mostrarPuntajeJugador(const tJugador* jugador);
void mostrarJugadorCartas(const tJugador *jugador);
//Funciones Mazo
void dar3CartasJugador(tJugador* jugador,tPila* mazo);
void darCartaJugador(tJugador* jugador,tPila* mazo);
int cargarMazo(tPila *mazo);
//Funciones Decision
int elegirCarta(void* Jugador,void* Maquina);
int rand3(void* Maquina,void* Jugador);
//Funciones tRonda
void crearRondas(tLista360* rondas,tJugador* jugador,tJugador* maquina,tPila* mazo);
void crearRonda(tRonda* ronda,tJugador* jugador,tJugador* oponente,tPila* mazo,ACT decision);
int jugarRondaConLista(void* Ronda,void* ListaINFO);
void rondaDarCarta(const tRonda* ronda);
int rondaFinalizoJuego(const tRonda* ronda);
void rondaAplicarEfecto(const tRonda* ronda);
void aplicarEfecto(tJugador *aplica, tJugador *aplicado);
//Funciones Ingreso
ACT selecionarDificultad();
int ingresoJugador(tJugador *jugador);

int iniciarJuego()
{
    int resultado;
    tJugador jugador;
    tJugador maquina={"Maquina",0};
    tLista360 listaTurnos;
    //tConfig config;
    //cargarConfig(NOMBRE_ARCH_CONFIG, &config);

    if(!ingresoJugador(&jugador)) //si no se ingreso jugador vuelve al menu
        return 0;

    //Partida
    crearLista360(&listaTurnos);
    if((resultado= jugar(&listaTurnos, &jugador, &maquina)) == GANAR)
    {
        grafica(1);
        //generarInforme(&listaTurnos,jugador,maquina);// generarInforme
                                                       //Arg 1 lista, arg2 ganador, arg3 perdedor
    }
    else
    {
        grafica(2);
        //generarInforme(&listaTurnos,maquina,jugador);// generarInforme
                                                       //Arg 1 lista, arg2 ganador, arg3 perdedor
    }
    //generarInforme(&listaTurnos, jugador, ganador, puntosIA);

    //vaciarLista360(&listaTurnos);
    return 1;
}
int jugar(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina)
{
    int resultado=-1;
    tPila mazo;
    tLista360 rondas;
    srand(time(NULL));
    crearPila(&mazo);
    crearLista360(&rondas);
    crearRondas(&rondas,jugador,maquina,&mazo);

    jugador->puntos=10;    //Opcional solo para testeo
    do
    {
        if(!recorrerLista360(&rondas,jugarRondaConLista,listaTurnos))
            resultado=VerGanador(jugador, maquina);
    }while (resultado != 0 && resultado != 1);

    return resultado;
}
int VerGanador(const tJugador *jugador,const tJugador *maquina)
{
    //luego del turno se verifica si hay un ganador
    if (jugador->puntos >=12) //Si se gano en este turno, verifica quien gano
    {
        printf("%s HA PERDIDO\n%s HA GANADO\n",maquina->nombre,jugador->nombre);
        system("pause");
        return 1;
    }
    printf("%s HA PERDIDO\n%s HA GANADO\n",jugador->nombre,maquina->nombre);
    system("pause");
    return 0;
}
//Funciones Mostrar
void mostrarUltimaCartaJugadaJugador(const tJugador* jugador)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    printf("Carta jugada Por %s es %s\n",jugador->nombre,Cartas[jugador->mazo[3]-'a']);
}
void mostrarPuntajeJugador(const tJugador* jugador)
{
    printf("%s Tiene %d Puntos\n",jugador->nombre,jugador->puntos);
}
void mostrarJugadorCartas(const tJugador *jugador)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    int i;
    printf("\n TUS CARTAS SON:\n");
    for(i=0;i<3;i++)
    {
        printf("%d) %s ",i+1,Cartas[jugador->mazo[i]-'a']);
    }
    puts("");
}
//Funciones Mazo
void dar3CartasJugador(tJugador* jugador,tPila* mazo)
{
    char* cartaJugada=jugador->mazo;
    char* ultimaCarta=jugador->mazo+3;
    if(pilaVacia(mazo))
        cargarMazo(mazo);
    while (cartaJugada<ultimaCarta)
    {
        sacarDePila(mazo,cartaJugada,sizeof(char));
        cartaJugada++;
    }
}
void darCartaJugador(tJugador* jugador,tPila* mazo)
{
    char* cartaJugada=jugador->mazo;
    char* ultimaCarta=jugador->mazo+3;
    if(pilaVacia(mazo))
        cargarMazo(mazo);
    while (cartaJugada<ultimaCarta&&*cartaJugada!='\0')
        cartaJugada++;
    if(cartaJugada!=ultimaCarta&&!*cartaJugada)
        sacarDePila(mazo,cartaJugada,sizeof(char));
}
int cargarMazo(tPila *mazo)
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
    grafica(MAZOMEZCLADO);
    pausarPantalla();
    return 1;
}
//Funciones Decision
int elegirCarta(void* Jugador,void* Maquina)
{
    tJugador* jugador=Jugador;
    const tJugador* maquina=Maquina;
    int selecion;
    int entradaValida;
    char input[3];
    grafica(JUEGAJUGADOR);
    pausarPantalla();
    do
    {
        limpiarPantalla();
        mostrarJugadorCartas(jugador);
        mostrarPuntajeJugador(jugador);
        mostrarPuntajeJugador(maquina);
        printf("%s Ingrese su carta a Jugar: ", jugador->nombre);
        registrarInput(input,sizeof(input),condIgual3);
        if((entradaValida=strAInt(&selecion,input))!=1&&!(entradaValida=rango(selecion,1,3)))
        {
            puts("Ingreso Invalido");
            pausarPantalla();
        }
    }while(!entradaValida);
    jugador->mazo[3]=jugador->mazo[selecion-1];
    jugador->mazo[selecion-1]='\0';
    return jugador->mazo[3];
}
int rand3(void* Maquina,void* Jugador)
{
    tJugador* maquina=Maquina;
    const tJugador* jugador=Jugador;
    int selecion=rand()%3;
    grafica(JUEGAMAQUINA);
    pausarPantalla();
    limpiarPantalla();
    mostrarJugadorCartas(jugador);
    mostrarPuntajeJugador(jugador);
    mostrarPuntajeJugador(maquina);
    maquina->mazo[3]=maquina->mazo[selecion];
    maquina->mazo[selecion]='\0';
    mostrarUltimaCartaJugadaJugador(maquina);
    pausarPantalla();
    return maquina->mazo[3];
}
//Funciones Ronda
void crearRondas(tLista360* rondas,tJugador* jugador,tJugador* maquina,tPila* mazo)
{
    tJugador*primero=maquina;
    ACT decisionPrimero=selecionarDificultad();
    tJugador*segundo=jugador;
    ACT decisionSegundo=elegirCarta;
    ACT CAMBIO;
    tRonda rondaAct;
    if(rand()%2)
    {
        CAMBIO=decisionPrimero;
        primero=jugador;
        decisionPrimero=decisionSegundo;
        segundo=maquina;
        decisionSegundo=CAMBIO;
    }
    crearRonda(&rondaAct,primero,segundo,mazo,decisionPrimero);
    ponerEnLista360Fin(rondas,&rondaAct,sizeof(rondaAct));
    crearRonda(&rondaAct,segundo,primero,mazo,decisionSegundo);
    ponerEnLista360Fin(rondas,&rondaAct,sizeof(rondaAct));
    dar3CartasJugador(primero,mazo);
    dar3CartasJugador(segundo,mazo);
}
void crearRonda(tRonda* ronda,tJugador* jugador,tJugador* oponente,tPila* mazo,ACT decision)
{
    ronda->jugador=jugador;
    ronda->oponente=oponente;
    ronda->mazo=mazo;
    ronda->decision=decision;
}
int jugarRondaConLista(void* Ronda,void* ListaINFO)
{
    tRonda* ronda=Ronda;
    //tLista360* listaInfo=ListaINFO;
    int cartaElegida;
    do
    {
        cartaElegida=ronda->decision(ronda->jugador,ronda->oponente);
        rondaAplicarEfecto(ronda);
        rondaDarCarta(ronda);
    } while (cartaElegida=='e');
    //informarTurno(listaInfo,ronda);//HACER
    if(rondaFinalizoJuego(ronda))
        return 0;
    return cartaElegida;
}
void rondaDarCarta(const tRonda* ronda)
{
    darCartaJugador(ronda->jugador,ronda->mazo);
}
int rondaFinalizoJuego(const tRonda* ronda)
{
    return ronda->jugador->puntos>=12;
}
void rondaAplicarEfecto(const tRonda* ronda)
{
    aplicarEfecto(ronda->jugador,ronda->oponente);
}
void aplicarEfecto(tJugador *aplica, tJugador *aplicado)
{
    switch (aplica->mazo[3])
    {
    //a +2
    case 'a':
        aplica->puntos+=2;
        break;
    //b +1
    case 'b':
        aplica->puntos+=1;
        break;
    //c -1
    case 'c':
        aplicado->puntos-=1;
        break;
    //d -2
    case 'd':
        aplicado->puntos-=2;
        break;
    //f espejo
    case 'f':
        if(aplicado->mazo[3]=='c')
        {
            aplica->puntos+=1;//Compensa los puntos perdidos
            aplicado->puntos-=1;//Quita puntos
        }
        if(aplicado->mazo[3]=='d')
        {
            aplica->puntos+=2;//Compensa los puntos perdidos
            aplicado->puntos-=2;//Quita puntos
        }
        break;
    //e repite
    default:
        break;
    }
    if(aplica->puntos>12)
        aplica->puntos=12;
    if(aplicado->puntos<0)
        aplicado->puntos=0;
}
//Funciones Ingreso
int ingresoJugador(tJugador *jugador)
{
    do
    {
        limpiarPantalla();
        grafica(6);
        registrarInput(jugador->nombre,sizeof(jugador->nombre),condInsercionAceptable);
        if (strcmp(jugador->nombre, "0\n") == 0)
            return 0;

        if (esNombreValido(jugador->nombre))
        {
            jugador->puntos = 0; // Inicializar
            return 1; // OK
        }
        puts("Ingreso invalido. Use solo letras. Intente de nuevo o ingrese 0 para salir.");
        pausarPantalla();
    }
    while(1);
    return 0;
}
ACT selecionarDificultad()
{
    limpiarPantalla();
    char input[3];
    int dificultad;
    int entradaValida;
    do
    {
        limpiarPantalla();
        grafica(7);
        registrarInput(input,sizeof(input),condIgual3);
        if((entradaValida=strAInt(&dificultad,input))!=1&&!(entradaValida=rango(dificultad,1,3)))
        {
            puts("Ingreso Invalido");
            pausarPantalla();
        }
    }
    while(!entradaValida);
    switch (dificultad)
    {
    case FACIL:
        return rand3;
    //case NORMAL:
    //    return FUNCIONDENORMAL;
    //case DIFICL:
    //    return FUNCIONDEDIFICIL;
    default:
        break;
    }
    return rand3;
}
//int jugarTurno(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina,int opc, int dificultad)
//{
//    int entradaValida=0;
//    int seleccion;
//    char carta;
//    if(opc == 0) //juega bot segun estrategias
//    {
//        ///SEGUIR ESTRATEGIA EN BASE A LA DIFICULTAD
//        //sacarDePila(mazo,&maquina->mazo[seleccion-1],sizeof(char));
//    }
//    else
//    {
//        // Jugador humano: ingresar carta
//      //por si ingresa un caracter o un simbolo por error
//
//            do
//            {   ///FUNCION QUE MUESTRE LAS CARTAS (QUE MUESTRE EL VALOR REAL)
//                mostrarJugadorCartas(jugador);
//                if((scanf("%d", &seleccion)) == 1)
//                {
//                    if(seleccion==1 || seleccion==2 || seleccion==3){
//                    entradaValida = 1;
//                    carta = jugador->mazo[seleccion-1];
//                    jugador->mazo[seleccion-1]='0';
//                    }
//                }
//                else
//                {
//                    limpiarBuffer();
//                }
//            }while(!entradaValida);
//
//        }
//
//    ///FUNCION QUE HAGA ALGO EN BASE A LA CARTA INGRESADA X HUMANO O X IA
//
//    ///FUNCION Q GUARDE EL TURNO EN LISTA de turnos
//
//    if(carta == 'e'){
//        return 2;
//    }
//    return -1;
//
//}
//
//void generarInforme(tLista360 *listaTurnos,tJugador jugador, char* ganador,int puntosIA){
// char nombrearch[40], codigoGrupo[] = "arreglo";
//    int i,
//        j,
//        result;
//    time_t t = time(NULL);
//    struct tm tm = *localtime(&t);
//    tPartida partida;
//
//    sprintf(nombrearch,"informe-juego_%04d-%02d-%02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
//
//    FILE *pl = fopen(nombrearch,"wt");
//
//    if(!pl)
//    {
//        printf("\nError al crear el informe");
//        return 0;
//    }
//
//    result=sacarDeLista(list_partidas,&partida,sizeof(partida));
//
//    while(result!=0)
//    {
//        fprintf(pl,"JUGADOR: %-19s\nPartida: %d\nGanador: %-10s\nPuntaje: %d\n",partida.jugador,partida.numPartida,partida.ganador,partida.puntaje);
//
//        // Escribir el tablero de la partida
//        fputs("TABLERO:\n", pl);
//        for (i = 0; i < TAM; i++)
//        {
//            for (j = 0; j < TAM; j++)
//            {
//                fprintf(pl, " %c ", partida.tablero[i][j]);
//                if (j < TAM - 1)
//                    fprintf(pl, "|"); // Separadores verticales
//            }
//            fputs("\n", pl);
//            if (i < TAM - 1)
//                fputs("---+---+---\n", pl); // Separadores horizontales
//        }
//        fputs("-----------------------------------\n", pl);
//
//        result=sacarDeLista(list_partidas,&partida,sizeof(partida));
//    }
//    generarRanking(list_jugadores, pl);
//    recorroListaYmandoDatosAPI(list_jugadores, codigoGrupo, 0, obtengoJugador);
//    fclose(pl);
//    return 0;
//return;
//}
