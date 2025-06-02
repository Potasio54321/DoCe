#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "../Headers/juego.h"
#include "..\Headers\Grafica.h"
#include "..\Headers\ListaCircular.h"
#include "..\Headers\Sistema.h"
#include "../Headers/API.h"
//Funciones Juego
int jugar(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina);
int VerGanador(const tJugador *jugador,const tJugador *maquina);
//Funciones Informe
int informeEstadoAPI(const tJugador*jugador,int estado);
int generarInforme(tLista360 *ListaTurnos,tJugador *jugador,tJugador *maquina);
int informarTurno(tLista360 *listaTurnos,tJugador* jugador);
int abrirArchivoTextoConNombreAppend(FILE **archivo,const char* nombreInicial,ACT append ,const char* modoApertura);
int appendFecha(void* Cadena,void* NULO);
//Funciones Mostrar
void mostrarUltimaCartaJugadaJugador(const tJugador* jugador);
void mostrarGanador(const tJugador *jugador,const tJugador *maquina);
void mostrarPuntajeJugador(const tJugador* jugador);
void mostrarJugadorCartas(const tJugador *jugador);
//Funciones Mazo
void dar3CartasJugador(tJugador* jugador,tPila* mazo);
void darCartaJugador(tJugador* jugador,tPila* mazo);
int cargarMazo(tPila *mazo);
int cargarMazoDescartes(tPila* mazo,tPila* descartes);
//Funciones Decision
int elegirCarta(void* Jugador,void* Maquina);
int decisionFacil(void* Maquina,void* Jugador);
int decisionNormal(void* Maquina,void* Jugador);
int decisionDificil(void* Maquina,void* Jugador);
//Funciones jugarTurnoIA
int jugarTurnoFacilIA(tJugador *maquina);
int jugarTurnoMedioIA(tJugador *maquina, const tJugador*jugador);
int jugarTurnoDificilIA(tJugador *maquina,const tJugador* jugador);
//Funciones InteractuanConElMazo
void cargarValoracion(int valoracion[],int valorSuma2,int valorSuma1,int valorResta1,int valorResta2,int valorRepite,int valorEspejo);
int buscarCartas(const char *mazo,char tam,Cond cumple);
int BuscarCartaConValoracion(const char mazo[],char tam,const int valoracion[]);
//FuncionesCondicion
int condEspejo(const void*Carta);
int condNoResta2(const void*Carta);
int condNoResta(const void*Carta);
int condSoloRestaORepite(const void*Carta);
int condSoloResta(const void*Carta);
int condSoloSuma(const void*Carta);
//Funciones tRonda
void crearRondas(tLista360* rondas,tJugador* jugador,tJugador* maquina,tPila* mazo, tPila* descartadas);
void crearRonda(tRonda* ronda,tJugador* jugador,tJugador* oponente,tPila* mazo, tPila* descartadas,ACT decision);
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

    if(!ingresoJugador(&jugador)) //si no se ingreso jugador vuelve al menu
        return 0;

    //Partida
    crearLista360(&listaTurnos);
    if((resultado= jugar(&listaTurnos, &jugador, &maquina)) == GANAR)
        grafica(1);
    else
        grafica(2);
    generarInforme(&listaTurnos,&jugador, &maquina);
    vaciarLista360(&listaTurnos);

    if(informeEstadoAPI(&jugador,VerGanador(&jugador,&maquina))!=204)
        puts("No se pudo enviar el resultado de la partida");
    else
        puts("Se pudo enviar el resultado de la partida");
    return 1;
}
int jugar(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina)
{
    int resultado=-1;
    tPila mazo;
    tPila descartadas;
    tLista360 rondas;
    srand(time(NULL));
    crearPila(&mazo);
    crearPila(&descartadas);
    crearLista360(&rondas);
    crearRondas(&rondas,jugador,maquina,&mazo,&descartadas);

    do
    {
        if(!recorrerLista360(&rondas,jugarRondaConLista,listaTurnos))
            resultado=VerGanador(jugador, maquina);
    }while (resultado != 0 && resultado != 1);
    mostrarGanador(jugador,maquina);
    vaciarLista360(&rondas);
    return resultado;
}
void mostrarGanador(const tJugador *jugador,const tJugador *maquina)
{
    if(VerGanador(jugador,maquina))
    {
        printf("%s HA PERDIDO\n%s HA GANADO\n",maquina->nombre,jugador->nombre);
        system("pause");
    }
    else
    {
        printf("%s HA PERDIDO\n%s HA GANADO\n",jugador->nombre,maquina->nombre);
        system("pause");
    }
}
int VerGanador(const tJugador *jugador,const tJugador *maquina)
{
    return jugador->puntos>maquina->puntos; //Ve quien tiene mas puntos
}
//Funciones Informe
int informeEstadoAPI(const tJugador*jugador,int estado)
{
    tConfig config;
    char textoJSON[256];
    if(!cargarConfig(NOMBRE_ARCH_CONFIG, &config))
        return 0;
    sprintf(textoJSON,"{\"CodigoGrupo\":\"%s\",\"jugador\":{\"nombre\":\"%s\",\"vencedor\":\"%d\"}}"
            ,config.codigo,jugador->nombre,estado);
    return postearEstado(&config,textoJSON);
}
int generarInforme(tLista360 *ListaTurnos,tJugador *jugador,tJugador *maquina)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    FILE *archivoInforme;
    tTurno turnoActual;
    tJugador* ganador=VerGanador(jugador,maquina)?jugador:maquina;
    if(!abrirArchivoTextoConNombreAppend(&archivoInforme,"informe-juego_",appendFecha,"wt"))
        return 0;
    fprintf(archivoInforme,"JUGADOR: %-19s\nGanador: %-10s\nPuntaje de %s: %d\nPuntaje de %s: %d\nListado de turnos:\n",
            jugador->nombre,ganador->nombre,jugador->nombre,jugador->puntos,maquina->nombre,maquina->puntos);
    while (sacarEnLista360Ini(ListaTurnos,&turnoActual,sizeof(turnoActual)))
    {
        fprintf(archivoInforme,"Turno: %03d\tCarta Jugada: %-7s\tJugador: %-19s\n",
                turnoActual.turno,Cartas[turnoActual.cartaJugada-'a'],turnoActual.nombre);
    }
    fclose(archivoInforme);
    return 1;
}
int abrirArchivoTextoConNombreAppend(FILE **archivo,const char* nombreInicial,ACT append,const char* modoApertura)
{
    char nombrearch[256];
    strcpy(nombrearch,nombreInicial);
    append(nombrearch,NULL);
    strcat(nombrearch,".txt");
    *archivo = fopen(nombrearch,modoApertura);
    return *archivo!=NULL;
}
int appendFecha(void* Cadena,void* NULO)
{
    char append[128];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(append,"%04d-%02d-%02d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
    strcat(Cadena,append);
    return 1;
}
//Funciones Mostrar
void mostrarUltimaCartaJugadaJugador(const tJugador* jugador)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    Print printCartas[6]={print_carta_mas2,print_carta_mas1,print_carta_menos1,print_carta_menos2,print_carta_repetir,print_carta_espejo};
    printf("\nUltima carta jugada por %s es %s\n",jugador->nombre,Cartas[jugador->mazo[3]-'a']);
    printCartas[jugador->mazo[3]-'a']();
}
void mostrarPuntajeJugador(const tJugador* jugador)
{
    printf("%s Tiene %d Puntos\n",jugador->nombre,jugador->puntos);
}
void mostrarJugadorCartas(const tJugador *jugador)
{
    char Cartas[6][7]={"+2","+1","-1","-2","Repite","Espejo"};
    Print printCartas[6]={print_carta_mas2,print_carta_mas1,print_carta_menos1,print_carta_menos2,print_carta_repetir,print_carta_espejo};
    int i;
    printf("\n TUS CARTAS SON:\n");
    for(i=0;i<3;i++)
    {
        printf("\n\tCarta %d): %s\n", i + 1,Cartas[jugador->mazo[i]-'a']);
        printCartas[jugador->mazo[i]-'a']();
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
int cargarMazoDescartes(tPila* mazo,tPila* descartes)
{
    char cartasDescartadas[41-5];
    char* cartaDescartadaAct=cartasDescartadas;
    unsigned cantCartas=41-6;
    unsigned cartaElegida;
    while (sacarDePila(descartes,cartaDescartadaAct,sizeof(char)))
        cartaDescartadaAct++;
    while (cantCartas>0)
    {
        cartaElegida=rand()%cantCartas;
        if(!ponerEnPila(mazo,cartasDescartadas+cartaElegida,sizeof(char)))
            return 0;
        cantCartas--;
        cartasDescartadas[cartaElegida]=cartasDescartadas[cantCartas];
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
int decisionFacil(void* Maquina,void* Jugador)
{
    tJugador* maquina=Maquina;
    const tJugador* jugador=Jugador;
    int selecion;
    grafica(JUEGAMAQUINA);
    pausarPantalla();
    limpiarPantalla();
    mostrarJugadorCartas(jugador);
    mostrarPuntajeJugador(jugador);
    mostrarPuntajeJugador(maquina);
    selecion=jugarTurnoFacilIA(maquina);
    maquina->mazo[3]=maquina->mazo[selecion];
    maquina->mazo[selecion]='\0';
    mostrarUltimaCartaJugadaJugador(maquina);
    pausarPantalla();
    return maquina->mazo[3];
}
int decisionNormal(void* Maquina,void* Jugador)
{
    tJugador* maquina=Maquina;
    const tJugador* jugador=Jugador;
    int selecion;
    grafica(JUEGAMAQUINA);
    pausarPantalla();
    limpiarPantalla();
    mostrarJugadorCartas(jugador);
    mostrarPuntajeJugador(jugador);
    mostrarPuntajeJugador(maquina);
    selecion=jugarTurnoMedioIA(maquina,jugador);
    maquina->mazo[3]=maquina->mazo[selecion];
    maquina->mazo[selecion]='\0';
    mostrarUltimaCartaJugadaJugador(maquina);
    pausarPantalla();
    return maquina->mazo[3];
}
int decisionDificil(void* Maquina,void* Jugador)
{
    tJugador* maquina=Maquina;
    const tJugador* jugador=Jugador;
    int selecion;
    grafica(JUEGAMAQUINA);
    pausarPantalla();
    limpiarPantalla();
    mostrarJugadorCartas(jugador);
    mostrarPuntajeJugador(jugador);
    mostrarPuntajeJugador(maquina);
    selecion=jugarTurnoDificilIA(maquina,jugador);
    maquina->mazo[3]=maquina->mazo[selecion];
    maquina->mazo[selecion]='\0';
    mostrarUltimaCartaJugadaJugador(maquina);
    pausarPantalla();
    return maquina->mazo[3];
}
//Funciones Ronda
void crearRondas(tLista360* rondas,tJugador* jugador,tJugador* maquina,tPila* mazo,tPila* descartadas)
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
    crearRonda(&rondaAct,primero,segundo,mazo,descartadas,decisionPrimero);
    ponerEnLista360Fin(rondas,&rondaAct,sizeof(rondaAct));
    crearRonda(&rondaAct,segundo,primero,mazo,descartadas,decisionSegundo);
    ponerEnLista360Fin(rondas,&rondaAct,sizeof(rondaAct));
    dar3CartasJugador(primero,mazo);
    dar3CartasJugador(segundo,mazo);
}
void crearRonda(tRonda* ronda,tJugador* jugador,tJugador* oponente,tPila* mazo,tPila*descartadas,ACT decision)
{
    ronda->jugador=jugador;
    ronda->oponente=oponente;
    ronda->mazo=mazo;
    ronda->descartes=descartadas;
    ronda->decision=decision;
}
int jugarRondaConLista(void* Ronda,void* ListaINFO)
{
    tRonda* ronda=Ronda;
    tLista360* listaInfo=ListaINFO;
    int cartaElegida;
    do
    {
        cartaElegida=ronda->decision(ronda->jugador,ronda->oponente);
        rondaAplicarEfecto(ronda);
        if(!informarTurno(listaInfo,ronda->jugador))
            return 0;
        if(rondaFinalizoJuego(ronda))
            return 0;
        rondaDarCarta(ronda);
    } while (cartaElegida=='e');

    return cartaElegida;
}
int informarTurno(tLista360 *listaTurnos,tJugador* jugador)
{
    tTurno turnoActual;//Este Escribe
    tTurno turnoPasado;//Este lee
    if(!verFinLista360(listaTurnos,&turnoPasado,sizeof(tTurno)))
        turnoActual.turno=1;
    else
        turnoActual.turno=turnoPasado.turno+1;
    turnoActual.cartaJugada=jugador->mazo[3];
    strcpy(turnoActual.nombre,jugador->nombre);
    return ponerEnLista360Fin(listaTurnos,&turnoActual,sizeof(tTurno));
}
void rondaDarCarta(const tRonda* ronda)
{
    ponerEnPila(ronda->descartes,ronda->jugador->mazo+3,sizeof(char));
    if(pilaVacia(ronda->mazo))
        cargarMazoDescartes(ronda->mazo,ronda->descartes);
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
        if (strcmp(jugador->nombre, "0") == 0)
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
        return decisionFacil;
    case NORMAL:
        return decisionNormal;
    case DIFICIL:
        return decisionDificil;
    default:
        break;
    }
    return decisionFacil;
}
//Funciones JugarIA
int jugarTurnoFacilIA(tJugador *maquina)
{
    return rand() % 3;
}
int jugarTurnoMedioIA(tJugador *maquina,const tJugador*jugador)
{
    int cartaSelecionada;
    ///1- Si una carta de suma le da la victoria a maquina (llega a 12 puntos o m�s), jugarla.
    if(maquina->puntos >= CERCAGANAR)
    {
        if((cartaSelecionada=buscarCartas(maquina->mazo,3,condSoloSuma))!=404)
            return cartaSelecionada;
    }
    if(jugador->puntos==1)///2- Si puntos del jugador < 2, tira la primera carta que no sea -2
    {
        if((cartaSelecionada=buscarCartas(maquina->mazo,3,condNoResta2))!=404)
            return cartaSelecionada;
    }
    if(jugador->puntos==0)///3- Si puntos del jugador < 1, tira la primera carta que no sea -2 y -1
    {
        if((cartaSelecionada=buscarCartas(maquina->mazo,3,condNoResta))!=404)
            return cartaSelecionada;
    }
    ///4- Pasa si no se cumplio nada
    return rand() % 3;
}
int jugarTurnoDificilIA(tJugador *maquina,const tJugador* jugador)
{
    int cartasBuenas = 0, cartaBuenaActual;
    int cartaSelecionada;
    int valoracion[6];
    ///1- Si el jugador jugo carta negativa(-1, -2), usar espejo
    if(rango(jugador->mazo[3],RESTA1,RESTA2))
    {
        if((cartaSelecionada=buscarCartas(maquina->mazo,3,condEspejo))!=404)
            return cartaSelecionada;
    }
    ///2- Si esta cerca de la victoria y el jugador no que se centre en ganar.
    if(maquina->puntos >= CERCAGANAR&&maquina->puntos>jugador->puntos)
    {
        if((cartaSelecionada=buscarCartas(maquina->mazo,3,condSoloSuma))!=404)
            return cartaSelecionada;
    }
    //cuento las cartas buneas (+2,+1,-2,-1)
    for(cartaBuenaActual = 0; cartaBuenaActual < 3; cartaBuenaActual++)
        if(rango(maquina->mazo[cartaBuenaActual],SUMA2,RESTA2))
            cartasBuenas++;
    ///3- si puntos del jugador >=8: usar -2, si no -1, si no REPITE(si es que tengo mas de 1 carta buena)
    if(jugador->puntos >= CERCAGANAR)
    {
        //aca me parecio que con 1 carta buena ya era suficiente para jugar un REPITE
        if(cartasBuenas>1)
            cartaSelecionada=buscarCartas(maquina->mazo,3,condSoloRestaORepite);
        else
            cartaSelecionada=buscarCartas(maquina->mazo,3,condSoloResta);
        if(cartaSelecionada!=404)
            return cartaSelecionada;
    }
    ///4- si puntos del jugador >= 2, maquina usa la mejor carta posible: +2 -> -2 -> REPITE(con 1 buena) -> +1 -> -1 -> Repite -> Espejo
    if(jugador->puntos >= 2)
    {
        //BuscarConValoracion ya hecha
        cargarValoracion(valoracion,6,3,2,5,1+cartasBuenas>1?3:0,0);
        //suma2 6//suma1 3//resta2 5//resta1 2//repiteConBuenas 4//repite 1//Espejo 0
        if((cartaSelecionada=BuscarCartaConValoracion(maquina->mazo,3,valoracion))!=-1)
            return cartaSelecionada;
    }
    ///5- si puntos del jugador == 1, maquina usa la mejor carta posible sin el -2: +2 -> +1 -> -1 -> Repite -> Espejo
    if(jugador->puntos == 1)
    {
        cargarValoracion(valoracion,4,3,-1,2,1,0);
        //suma2 4//suma1 3//resta2 -1//resta1 2//repite 1//Espejo 0
        if((cartaSelecionada=BuscarCartaConValoracion(maquina->mazo,3,valoracion))!=-1)
            return cartaSelecionada;
    }
    ///6- si puntos del jugador == 0, maquina usa la mejor carta posible sin el -2 y -1: +2 -> +1 -> -1 -> Repite -> Espejo
    if(jugador->puntos == 0)
    {
        cargarValoracion(valoracion,3,2,-1,-4,1,0);
        //suma2 3//suma1 2//resta2 -1//resta1 -1//repite 1//Espejo 0
        if((cartaSelecionada=BuscarCartaConValoracion(maquina->mazo,3,valoracion))!=-1)
            return cartaSelecionada;
    }
    return rand() % 3;//En caso de que tenga solo menos con pocos puntos elige su cualquier carta
}
//Funciones que Interactuan con el Mazo
void cargarValoracion(int valoracion[],int valorSuma2,int valorSuma1,int valorResta1
                    ,int valorResta2,int valorRepite,int valorEspejo)
{
    valoracion[0]=valorSuma2;
    valoracion[1]=valorSuma2;
    valoracion[2]=valorResta1;
    valoracion[3]=valorResta2;
    valoracion[4]=valorRepite;
    valoracion[5]=valorEspejo;
}
int BuscarCartaConValoracion(const char mazo[],char tam,const int valoracion[])
{
    int cartaActual,max=-1,cartaSelecionada=-1;
    for(cartaActual=0;cartaActual<tam;cartaActual++)
    {
        if(max<valoracion[mazo[cartaActual]-SUMA2])
        {
            max=valoracion[mazo[cartaActual]-SUMA2];
            cartaSelecionada=cartaActual;
        }
    }
    return cartaSelecionada;
}
int buscarCartas(const char *mazo,char tam,Cond cumple)
{
    const char *cartaActual;
    const char *fin=mazo+tam;
    for(cartaActual = mazo; cartaActual < fin; cartaActual++)
    {
        if(cumple(cartaActual))
            return cartaActual-mazo;
    }
    return 404;
}
//FuncionesCondicion
int condSoloSuma(const void*Carta)
{
    const char* carta=Carta;
    return rango(*carta,SUMA2,SUMA1);
}
int condSoloResta(const void*Carta)
{
    const char* carta=Carta;
    return rango(*carta,RESTA1,RESTA2);
}
int condSoloRestaORepite(const void*Carta)
{
    const char* carta=Carta;
    return rango(*carta,RESTA1,RESTA2)||*carta==REPITE;
}
int condNoResta(const void*Carta)
{
    const char* carta=Carta;
    return !rango(*carta,RESTA1,RESTA2);
}
int condNoResta2(const void*Carta)
{
    const char* carta=Carta;
    return *carta!=RESTA2;
}
int condEspejo(const void*Carta)
{
    const char* carta=Carta;
    return *carta==ESPEJO;
}
