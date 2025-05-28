#include <curl/curl.h>
#include "../Headers/cJSON.h"
#include "../Headers/Ranking.h"
#include "../Headers/Lista.h"
#include <stdio.h>
int leerTextoJugador(char* registro,tJugador* jugador);
int tMemoriaCrear(tMemoria* memoria);
int cmp_tJugadorPG(const void* Jugador1,const void* Jugador2);
int mostrar_tJugador(void* Jugador,void*NULO);
void mostrarListaOrdenada(tLista* listaJugadores);
int cargarLista(tLista* listaJugadores,tMemoria *curlRegistro);
int cargaRegistro(CURL *curl,tMemoria *curlRegistro);
int leerTextoJugador(char* registro,tJugador* jugador);
int respuestaInvalida(tMemoria* curlRegistro);
int verRanking()
{
    tLista listaJugadores;
    tMemoria curlRegistro;
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "Error al inicializar cURL\n");
        return ERR_CURL;
    }
    if(!tMemoriaCrear(&curlRegistro))
    {
        curl_easy_cleanup(curl);
        return ERR_MEM;
    }
    if(!cargaRegistro(curl,&curlRegistro))
    {
        free(curlRegistro.respuesta);
        curl_easy_cleanup(curl);
        return ERR_CURL;
    }
    curl_easy_cleanup(curl);
    if(!cargarLista(&listaJugadores,&curlRegistro))
    {
        vaciarLista(&listaJugadores);
        free(curlRegistro.respuesta);
        return ERR_CJSON;
    }
    free(curlRegistro.respuesta);
    mostrarListaOrdenada(&listaJugadores);
    vaciarLista(&listaJugadores);
    return 1;
}
void mostrarListaOrdenada(tLista* listaJugadores)
{
    ordenadoSeleccionLista(listaJugadores,cmp_tJugadorPG);
    puts("Nombre\t\t\t\t Partidas Ganadas");
    recorrerLista(listaJugadores,NULL,mostrar_tJugador);
}
int mostrar_tJugador(void* Jugador,void*NULO)
{
    const tJugador *jugador=Jugador;
    printf("%s\t%I64d",jugador->nombre,jugador->partidasGanadas);
    return 0;
}
int cmp_tJugadorPG(const void* Jugador1,const void* Jugador2)
{
    const tJugador *jugador1=Jugador1;
    const tJugador *jugador2=Jugador2;
    return jugador1->partidasGanadas-jugador2->partidasGanadas;
}
int cargarLista(tLista* listaJugadores,tMemoria *curlRegistro)
{
    cJSON * respuesta;
    cJSON *jugador;
    cJSON *nombre,*puntos;
    tJugador jugadorAct;
    int cantElem,numJugadorActual;
    if(respuestaInvalida(curlRegistro))
        return 0;
    crearLista(listaJugadores);
    if(!(respuesta=cJSON_Parse(curlRegistro->respuesta))||!cJSON_IsArray(respuesta))
    {
        cJSON_Delete(respuesta);
        return 0;
    }
    cantElem=cJSON_GetArraySize(respuesta);
    for (numJugadorActual = 0; numJugadorActual < cantElem; numJugadorActual++)
    {
        jugador = cJSON_GetArrayItem(respuesta, numJugadorActual);
        nombre = cJSON_GetObjectItem(jugador, "nombreJugador");
        puntos = cJSON_GetObjectItem(jugador, "cantidadPartidasGanadas");

        memcpy(jugadorAct.nombre, nombre->valuestring, sizeof(jugadorAct.nombre));
        jugadorAct.partidasGanadas = puntos->valueint;
        if(!ponerPrincipioLista(listaJugadores, &jugadorAct, sizeof(tJugador)))
        {
            cJSON_Delete(respuesta);
            return 0;
        }
    }
    cJSON_Delete(respuesta);
    return 1;
}
int respuestaInvalida(tMemoria* curlRegistro)
{
    return !curlRegistro->respuesta||strlen(curlRegistro->respuesta)==0||strcmp(curlRegistro->respuesta,"[]")==0;
}
size_t escrituraCallBack(void *data, size_t tam, size_t ncant, void *userp)
{
    size_t ntam = tam * ncant;
    tMemoria *mem = userp;

    char *ptr = realloc(mem->respuesta, mem->tam + ntam + 1);
    if (ptr == NULL)
    {
        return 0;
    }

    mem->respuesta = ptr;
    memcpy(mem->respuesta+mem->tam, data, ntam);
    mem->tam += ntam;
    *(mem->respuesta+mem->tam) = '\0';

    return ntam;
}
int cargaRegistro(CURL *curl,tMemoria *curlRegistro)
{
    CURLcode codRes;
    curlRegistro->respuesta[0] = '\0';

    curl_easy_setopt(curl, CURLOPT_URL, URLAPI);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, escrituraCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlRegistro);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    codRes=curl_easy_perform(curl);
    return codRes!=CURLE_OK;
}
int leerTextoJugador(char* registro,tJugador* jugador)
{
    return sscanf(registro,"%[^|]|%I64u",jugador->nombre,&jugador->partidasGanadas)==2;
}
int tMemoriaCrear(tMemoria* memoria)
{
    memoria=malloc(1);
    if(!memoria)
        return 0;
    memoria->tam=0;
    return 1;
}


