#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "..\Headers\juego.h"
#include "..\Headers\Menu.h"
#include "..\Headers\Grafica.h"
#include "..\Headers\ListaCircular.h"
#include "..\Headers\Sistema.h"
//Funciones Juego
int jugar(tLista360 *listaTurnos, tJugador *jugador, tJugador *maquina);
int VerGanador(const tJugador *jugador,const tJugador *maquina);
//Funciones Informe
int generarInforme(tLista360 *ListaTurnos,tJugador *jugador,tJugador *maquina);
int informarTurno(tLista360 *listaTurnos,tJugador* jugador);
//Funciones API
int cargarConfig(const char* nombreArchConfig,tConfig* config);
void configDarUrlCC(const tConfig *config,char* destino);
int abrirArchivoTextoConNombreAppend(FILE **archivo,const char* nombreInicial,ACT append,const char* modoApertura);
int appendFecha(void* Cadena,void* NULO);
int informeEstadoAPI(const tJugador*jugador,int estado);
int postearEstado(const tConfig *config,const char *json);
//Funciones Mostrar
void mostrarUltimaCartaJugadaJugador(const tJugador* jugador);
void mostrarGanador(const tJugador *jugador,const tJugador *maquina);
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
//
char* _strcpyWhile(char* dest,char* source,char end);

int iniciarJuego()
{
    int resultado;
    tJugador jugador;
    tJugador maquina={"Maquina",0};
    tLista360 listaTurnos;
    int a;
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
    a=informeEstadoAPI(&jugador,VerGanador(&jugador,&maquina));
    printf("Codigo http:%d\n",a);
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

    jugador->puntos=12;    //Opcional solo para testeo
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
    //hacer un un texto cjson que cumpla con codigogrupo y codigo
    //jugador nombre: jugador->nombre, vencedor: estado
    //Enviarlo por API
    return postearEstado(&config,textoJSON);
}
int cargarConfig(const char* nombreArchConfig,tConfig* config)
{
    FILE* archivoConfig=fopen(nombreArchConfig,"rt");
    char buffer[256],*cursor;
    if(!archivoConfig)
        return 0;
    fgets(buffer,256,archivoConfig);
    fclose(archivoConfig);
    cursor=_strcpyWhile(config->url,buffer,'|');
    cursor++;
    _strcpyWhile(config->codigo,cursor,'\n');
    return 1;
}
//Funcion solo para el caso especifico
//NO USAR FUERA DE OTRO LADO
//MUY ROMPIBLE
char* _strcpyWhile(char* dest,char* source,char end)
{
    while (*source!=end)
    {
        *dest=*source;
        dest++;
        source++;
    }
    *dest='\0';
    return source;
}
int postearEstado(const tConfig *config,const char *json)
{
    CURL *urlDoce=curl_easy_init();
    struct curl_slist *tipoDato=NULL;
    CURLcode resultado;
    char urlCC[288];
    long codigoHTTP;
    if(!urlDoce)
        return 0;
    //Inicializar La Url
    configDarUrlCC(config,urlCC);
    curl_easy_setopt(urlDoce,CURLOPT_URL,urlCC);
    //curl_easy_setopt(urlDoce, CURLOPT_VERBOSE, 1L); MUY UTIL
    curl_easy_setopt(urlDoce,CURLOPT_POST,1L);
    //Poner el Header adecuado y el contenido a postear
    tipoDato = curl_slist_append(tipoDato, "Content-Type: application/json");
    curl_easy_setopt(urlDoce, CURLOPT_HTTPHEADER, tipoDato);
    curl_easy_setopt(urlDoce, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(urlDoce, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(urlDoce, CURLOPT_SSL_VERIFYHOST, 0L);
    resultado = curl_easy_perform(urlDoce);
    //Ver Respuesta HTTP
    curl_easy_getinfo(urlDoce, CURLINFO_RESPONSE_CODE, &codigoHTTP);
    //LiberarMemoria
    curl_slist_free_all(tipoDato);
    curl_easy_cleanup(urlDoce);
    if(resultado!=CURLE_OK)
    {
        return 0;
    }
    return codigoHTTP;
}
void configDarUrlCC(const tConfig *config,char* destino)
{
    strcpy(destino,config->url);
    //strcat(destino,"/");
    //strcat(destino,config->codigo);
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
    //ACT decisionSegundo=elegirCarta;
    ACT decisionSegundo=rand3;
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
    tLista360* listaInfo=ListaINFO;
    int cartaElegida;
    do
    {
        cartaElegida=ronda->decision(ronda->jugador,ronda->oponente);
        rondaAplicarEfecto(ronda);
        rondaDarCarta(ronda);
        if(!informarTurno(listaInfo,ronda->jugador))//SI FALLA CANCELAR PARTIDA DAR MEJOR GANADOR
            return 0;//PODRIA HABER EMPATE
    } while (cartaElegida=='e');
    if(rondaFinalizoJuego(ronda))
        return 0;
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
