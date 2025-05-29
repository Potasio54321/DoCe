#include "juego.h"
#include <time.h>


int iniciarJuego()
{
    int resultado,
        puntosIA;
    char ganador[10];
    tJugador jugador;

    //tConfig config;
    tLista list_turnos;

    //cargarConfig(NOMBRE_ARCH_CONFIG, &config);

    resultado = ingresoJugador(&jugador);

    if(!resultado) //si no se ingreso jugador vuelve al menu
        return 0;

    // Inicializa la semilla para los numeros aleatorios
    srand(time(NULL));


    limpiarPantalla();

    //Partida
            crearLista(&list_turnos);

            resultado = jugar(&list_turnos, &jugador, &puntosIA);

            if(resultado == GANAR)
            {
                strcpy(ganador,jugador.nombre);
                grafica(1);
            }
            else
            {
                strcpy(ganador,"MAQUINA");
                grafica(2);
            }

//    generarInforme(&list_turnos, jugador, ganador, puntosIA);

    vaciarLista(&list_turnos);
    return 1;
}

int ingresoJugador(tJugador *jugador)
{
    limpiarPantalla();
    printf("\n\t\t ========================================================");
    printf("\n\t\t|\t\t   INGRESO DE JUGADOR                    |");
    printf("\n\t\t|\t\t   --------------------                  |");
    printf("\n\t\t|\t Ingrese su nombre o 0 para volver al menu.      |");
    printf("\n\t\t ========================================================\n\n");

    while(1)
    {
        printf("Jugador: ");
        scanf("%19s", jugador->nombre);

        if (strcmp(jugador->nombre, "0") == 0)
            return 0;

        if (esNombreValido(jugador->nombre)) {
            jugador->puntos = 0; // Inicializar
            return 1; // OK
        }
        printf("Ingreso inválido. Use solo letras. Intente de nuevo o ingrese 0 para salir.\n");
        pausarPantalla();
    }


    return 0;
}

void selectdificultad(int *d){

    limpiarPantalla();
    printf("\n\t\t ========================================================");
    printf("\n\t\t|\t\t   DIFICULTAD                   |");
    printf("\n\t\t|\t\t   --------------------                  |");
    printf("\n\t\t|\t [1] FACIL     |");
    printf("\n\t\t|\t [2] MEDIO     |");
    printf("\n\t\t|\t [3] DIFICIL    |");
    printf("\n\t\t ========================================================\n\n");

    do{
    printf("Seleccione nivel de dificultad: ");
    scanf("%d", d);
    if(*d != 1 && *d != 2 && *d != 3){
    printf("Ingrese un numero de nivel valido [1]facil, [2]medio o [3]dificil ");
    }
    }while(*d != 1 && *d != 2 && *d != 3);

}


int esNombreValido(const char *nombre) {
   int i;
    for (i = 0; nombre[i] != '\0'; i++) {
        if (!isalpha(nombre[i]))
            return 0;
    }
    return 1;
}


int jugar(tLista *list_turnos, tJugador *jugador, int *puntosIA)
{
    int resultado = -1,
        opc = 0,
        entradaValida;
    int juega = rand() % 2,//se sortea quien empieza, si sale 0 empieza la maquina, si sale 1 empieza el humano.
        dificultad;
    tJugador maquina={"MAQUINA",0};

    selectdificultad(&dificultad);

    while(opc != 1) ///mientras el usuario no diga que esta listo para jugar
    {
        do
        {
            printf("\nListo para jugar? ([1] SI, [0] NO): ");
            entradaValida = scanf("%d", &opc);/// scanf me duelve 0 si se ingreso un caracter o un simbolo, en caso contrario me devuelve 1
            if (entradaValida != 1 || (opc != 0 && opc != 1))
            {
                printf("Entrada invalida. Ingrese 0 o 1.\n");
                limpiarBuffer();
            }
        }
        while (entradaValida != 1 || (opc != 0 && opc != 1));   /// Se repite hasta que ingrese 0 o 1
        if (opc == 0) ///si no esta listo
        {
            do
            {
                printf("\nVolver al menu? ([1] SI, [0] NO): "); ///pregunto si quiere volver al menu
                entradaValida = scanf("%d", &opc);
                if (entradaValida != 1)
                {
                    printf("Entrada invalida. Ingrese 0 o 1.\n");
                    limpiarBuffer();
                }
                else
                {
                    if(opc == 1)/// regreso al menu
                        return 0;
                }
            }
            while (entradaValida != 1 || (opc != 0 && opc != 1));   /// Se repite hasta que ingrese 0 o 1
            if (opc == 0)
            {
                opc = -1;  /// Para que vuelva a preguntar "Listo para jugar?"
            }
        }
    }

    ///inicializa el mezclado de cartas

    if (juega == 1)
    {
        printf("\n\tEmpezas vos\n");
    }
    else
    {
        printf("\n\tEmpieza la IA.\n");
    }
    printf("\t-------------------------\n");
    printf("\t=====================================================\n");
    pausarPantalla();
    limpiarPantalla();

    ///MEZCLAR MAZO
    ///REPARTIR 3 CARTAS

    ///REPARTIR CARTAS A LA MAQUINA


    while (resultado != 0 && resultado != 1)
    {
        printf("\n TUS CARTAS SON:\n");
        printf("1) %c ",jugador->mazo[0]);
        printf("2) %c ",jugador->mazo[1]);
        printf("3) %c ",jugador->mazo[2]);
        printf("\n TU PUNTAJE:\n");
        printf("%d",jugador->puntos);
        printf("\n PUNTAJE DE LA MAQUINA:\n");
        printf("%d",maquina.puntos);
        resultado = finalizaJuego(list_turnos, jugador, &maquina, juega, dificultad);

        if(resultado == -1) ///Debe intercambiar quien juega la proxima vez
                opc=opc==1?0:1; ///si resultado==2 entonces NO CAMBIA quien juega pq eligio una carta de repetir turno

        ///levantar una carta para el que acaba de jugar

    }

    return resultado;

}


int finalizaJuego(tLista *list_turnos, tJugador *jugador, tJugador *maquina, int opc, int dificultad)
{
    int juegoTerminado;
    int rTurno;
    rTurno = jugarTurno(list_turnos,jugador, maquina, opc, dificultad); //se juega el turno enviando con OPC quién juega.

    //luego del turno se verifica si hay un ganador

    if (opc==1  && jugador->puntos >=12) //Si se gano en este turno, verifica quien gano
    {

        printf("%s ha ganado\n", jugador->nombre );
        system("pause");

        juegoTerminado = 1;

    }
    else if (opc==0 && maquina->puntos >= 12)
        {
        printf("Maquina ha ganado\n");
        system("pause");
        juegoTerminado = 0;
        }
        else{
            juegoTerminado = rTurno;
        }



    return juegoTerminado; //si no hubo ganador, devuelve juegoTerminado = -1 para que se juegue el siguiente turno.
}                          //si hubo un ganador, esta funcion devolvera los puntos que le corresponden al usuario.
                        //si no hubo ganador y se lanzo un repetir, devuelve 2 para que no cambie de jugador el proximo turno.




int jugarTurno(tLista *list_turnos, tJugador *jugador, tJugador *maquina,int opc, int dificultad)
{
    int entradaValida=0;
    int seleccion;
    char carta;
    if(opc == 0) //juega bot segun estrategias
    {
        ///SEGUIR ESTRATEGIA EN BASE A LA DIFICULTAD
    }
    else
    {
        // Jugador humano: ingresar carta
      //por si ingresa un caracter o un simbolo por error

            do
            {   ///FUNCION QUE MUESTRE LAS CARTAS (QUE MUESTRE EL VALOR REAL)
                printf("\n TUS CARTAS SON:\n");
                printf("1) %c ",jugador->mazo[0]);
                printf("2) %c ",jugador->mazo[1]);
                printf("3) %c ",jugador->mazo[2]);
                printf("\n%s, ingresa carta: ", jugador->nombre);
                if((scanf("%d", &seleccion)) == 1)
                {
                    if(seleccion==1 || seleccion==2 || seleccion==3){
                    entradaValida = 1;
                    carta = jugador->mazo[seleccion-1];
                    jugador->mazo[seleccion-1]='0';
                    }
                }
                else
                {
                    limpiarBuffer();
                }
            }while(!entradaValida);

        }

    ///FUNCION QUE HAGA ALGO EN BASE A LA CARTA INGRESADA X HUMANO O X IA

    ///FUNCION Q GUARDE EL TURNO EN LISTA de turnos

    if(carta == 'e'){
        return 2;
    }
    return -1;

}
//
//void generarInforme(tLista *list_turnos,tJugador jugador, char* ganador,int puntosIA){
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
