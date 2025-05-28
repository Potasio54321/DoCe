#include "..\Headers\juego.h"
#include "..\Headers\PilaEstatica.h"
#include "..\Headers\Menu.h"
#include "..\Headers\Grafica.h"
#include <time.h>
void dar3CartasJugador(tJugador* jugador,tPila* mazo);
void darCartaJugador(tJugador* jugador,tPila* mazo);
int elegirCarta(void* Jugador,void* Maquina);
int jugarTurno2(tLista *list_turnos,tJugador *juega, tJugador *oponente,ACT decision);
int strAInt(int *numero,const char* str);
void aplicarEfecto(tJugador *aplica, tJugador *aplicado);
int finalizaJuego(tJugador *jugador, tJugador *maquina, int resultado);
void mostrarJugadorCartas(tJugador *jugador);
int ingresoJugador(tJugador *jugador);
void selectdificultad(int *d);
int cargarMazo(tPila *mazo);
int rand3(void* Maquina,void* Jugador);

int iniciarJuego()
{
    int resultado;
    tJugador jugador;
    tJugador maquina={"Maquina",0};
    tLista list_turnos;
    //tConfig config;
    //cargarConfig(NOMBRE_ARCH_CONFIG, &config);

    if(!ingresoJugador(&jugador)) //si no se ingreso jugador vuelve al menu
        return 0;

    // Inicializa la semilla para los numeros aleatorios
    srand(time(NULL));
    //Partida
    crearLista(&list_turnos);
    resultado = jugar(&list_turnos, &jugador, &maquina);
    if(resultado == GANAR)
        grafica(1);
    else
        grafica(2);
    //generarInforme(&list_turnos, jugador, ganador, puntosIA);
    //generarInforme(&list_turnos,jugador,maquina);
    vaciarLista(&list_turnos);
    return 1;
}
int jugar(tLista *list_turnos, tJugador *jugador, tJugador *maquina)
{
    int resultado;
    int juega = rand() % 2,//se sortea quien empieza, si sale 0 empieza la maquina, si sale 1 empieza el humano.
        dificultad;
    tPila mazo;

    selectdificultad(&dificultad);
    puts("Presione Cualquier tecla para continuar");

    ///inicializa el mezclado de cartas
    if (juega == 1)
    {
        printf("\nEmpezas vos\n");
    }
    else
    {
        printf("\nEmpieza la IA.\n");
    }
    printf("-------------------------\n");
    printf("=====================================================\n");
    pausarPantalla();
    limpiarPantalla();

    ///MEZCLAR MAZO
    ///REPARTIR 3 CARTAS

    ///REPARTIR CARTAS A LA MAQUINA
    crearPila(&mazo);
    cargarMazo(&mazo);
    dar3CartasJugador(jugador,&mazo);
    dar3CartasJugador(maquina,&mazo);
    jugador->puntos=10;
    do
    {
        if(pilaVacia(&mazo))
        {
            cargarMazo(&mazo);
        }
        //Cambiar

        //Funcion Jugador Mostrar Cartas
        mostrarJugadorCartas(jugador);
        //Funcion Jugador Mostrar Puntaje
        printf("\n TU PUNTAJE: %d",jugador->puntos);
        printf("\n PUNTAJE DE LA MAQUINA: %d",maquina->puntos);
        if(juega==1)//se juega el turno enviando con Juega qui�n juega.
        {
            puts("\nJuegas vos");
            resultado=jugarTurno2(list_turnos,jugador, maquina,elegirCarta);//Juega el que toca
            darCartaJugador(jugador,&mazo);//Saca una Carta
        }
        else
        {
            puts("\nJuega La Maquina");
            resultado=jugarTurno2(list_turnos,maquina, jugador,rand3);
            darCartaJugador(maquina,&mazo);
            printf("Carta jugada Por la maquina %c\n",maquina->mazo[3]);
        }
        system("pause");
        //resultado = jugarTurno(list_turnos,jugador, maquina, &mazo,opc, dificultad);
        if((resultado=finalizaJuego(jugador, maquina, resultado)) == -1) ///Debe intercambiar quien juega la proxima vez
        {
            juega++;
            juega%=2;///si resultado==2 entonces NO CAMBIA quien juega pq eligio una carta de repetir turno
        }
        limpiarPantalla();
    }while (resultado != 0 && resultado != 1);

    return resultado;
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
    return 1;
}
int jugarTurno2(tLista *list_turnos,tJugador *juega, tJugador *oponente,ACT decision)
{
    int cartaJugada=decision(juega,oponente);
    aplicarEfecto(juega,oponente);
    //informarLista(list_turnos,juega);
    if(cartaJugada == 'e'){
        return 2;
    }
    return -1;
}
void dar3CartasJugador(tJugador* jugador,tPila* mazo)
{
    char* cartaJugada=jugador->mazo;
    char* ultimaCarta=jugador->mazo+3;
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
    while (cartaJugada<ultimaCarta&&*cartaJugada!='\0')
    {
        cartaJugada++;
    }
    if(cartaJugada!=ultimaCarta&&!*cartaJugada)
    {
        sacarDePila(mazo,cartaJugada,sizeof(char));
    }
}
int elegirCarta(void* Jugador,void* Maquina)
{
    tJugador* jugador=Jugador;
    tJugador* maquina=Maquina;
    int selecion;
    int entradaValida;
    char input[3];
    do
    {
        limpiarPantalla();
        mostrarJugadorCartas(jugador);
        printf("\n TU PUNTAJE: %d",jugador->puntos);
        printf("\n PUNTAJE DE LA MAQUINA: %d",maquina->puntos);
        printf("\n%s Ingrese su carta a Jugar: ", jugador->nombre);
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
    int selecion=rand()%3;
    maquina->mazo[3]=maquina->mazo[selecion];
    maquina->mazo[selecion]='\0';
    return maquina->mazo[3];
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
int finalizaJuego(tJugador *jugador, tJugador *maquina, int resultado)
{
    //luego del turno se verifica si hay un ganador
    if (jugador->puntos >=12) //Si se gano en este turno, verifica quien gano
    {

        printf("%s ha ganado\n", jugador->nombre );
        system("pause");

        return 1;
    }
    else if (maquina->puntos >= 12)
    {
        printf("Maquina ha ganado\n");
        system("pause");
        return 0;
    }
    //si hubo un ganador, esta funcion devolvera los puntos que le corresponden al usuario.
    //si no hubo ganador y se lanzo un repetir, devuelve 2 para que no cambie de jugador el proximo turno.
    //si no hubo ganador, devuelve juegoTerminado = -1 para que se juegue el siguiente turno.
    return resultado;
}
void mostrarJugadorCartas(tJugador *jugador)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    int i;
    printf("\n TUS CARTAS SON:\n");
    for(i=0;i<3;i++)
    {
        printf("%d) %s ",i+1,Cartas[jugador->mazo[i]-'a']);
    }
}
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
void selectdificultad(int *d)
{
    limpiarPantalla();
    char input[3];
    int entradaValida;
    do
    {
        limpiarPantalla();
        grafica(7);
        registrarInput(input,sizeof(input),condIgual3);
        if((entradaValida=strAInt(d,input))!=1&&!(entradaValida=rango(*d,1,3)))
        {
            puts("Ingreso Invalido");
            pausarPantalla();
        }
    }
    while(!entradaValida);
}
//int jugarTurno(tLista *list_turnos, tJugador *jugador, tJugador *maquina,int opc, int dificultad)
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
