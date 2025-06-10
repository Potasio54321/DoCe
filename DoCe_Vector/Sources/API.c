#include "../Headers/API.h"
#include "../Headers/ListaSEnlazada.h"
#include "../Headers/cJSON.h"
#include "../Headers/Grafica.h"
#include <curl/curl.h>
#include <stdio.h>
//Funciones tConfig
char* _strcpyWhile(char* dest,char* source,char end);
void configDarUrlCC(const tConfig *config,char* destino);
void configDarUrl(const tConfig *config,char* destino);
//Funciones de memoria
int tMemoriaCrear(tMemoria* memoria);
int respuestaInvalida(tMemoria* curlRegistro);
//Funciones para Leer
int cargarLista(tLista* listaJugadores,tMemoria *curlRegistro);
int cargaRegistro(CURL *curl,tMemoria *curlRegistro);
void mostrarListaOrdenada(tLista* listaJugadores);

int cmp_tJugAPIPorGanadas(const void* Jugador1,const void* Jugador2);
int imprimoRanking(void *d1, void *d2);

int verRanking()
{
    tLista listaJugadores;
    tMemoria curlRegistro;
    CURL *curl = curl_easy_init();
    grafica(RANKING);
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
int cargarLista(tLista* listaJugadores,tMemoria *curlRegistro)
{
    cJSON * respuesta;
    cJSON *jugador;
    cJSON *nombre,*cantidadPartidasGanadas;
    tJugAPI jugadorAct;
    int cantElem,numJugadorActual;
    if(respuestaInvalida(curlRegistro))
    {
        puts("No hay datos disponibles en la API.");
        return 0;
    }
    crearLista(listaJugadores);
    if(!(respuesta=cJSON_Parse(curlRegistro->respuesta))||!cJSON_IsArray(respuesta))
    {
        puts("La respuesta no esta formateada como lo esperado.");
        cJSON_Delete(respuesta);
        return 0;
    }
    cantElem=cJSON_GetArraySize(respuesta);
    for (numJugadorActual = 0; numJugadorActual < cantElem; numJugadorActual++)
    {
        jugador = cJSON_GetArrayItem(respuesta, numJugadorActual);
        nombre = cJSON_GetObjectItem(jugador, "nombreJugador");
        cantidadPartidasGanadas = cJSON_GetObjectItem(jugador, "cantidadPartidasGanadas");

        memcpy(jugadorAct.nombre, nombre->valuestring, sizeof(jugadorAct.nombre));
        jugadorAct.cantidadPartidasGanadas = cantidadPartidasGanadas->valueint;
        if(!ponerPrincipioLista(listaJugadores, &jugadorAct, sizeof(tJugAPI)))
        {
            puts("Falta de memoria");
            cJSON_Delete(respuesta);
            return 0;
        }
    }
    cJSON_Delete(respuesta);
    return 1;
}
void mostrarListaOrdenada(tLista* listaJugadores)
{
    ordenadoSeleccionLista(listaJugadores,cmp_tJugAPIPorGanadas);
    printf("\t\t\t |//////////////////////////////////////////////////|\n");
    printf("\t\t\t |Nombre%28sPartidas Ganadas|\n"," ");
    printf("\t\t\t |//////////////////////////////////////////////////|\n");
    recorrerLista(listaJugadores,NULL,imprimoRanking);
    printf("\t\t\t |//////////////////////////////////////////////////|\n");
}
int cmp_tJugAPIPorGanadas(const void* Jugador1,const void* Jugador2)
{
    const tJugAPI *jugador1=Jugador1;
    const tJugAPI *jugador2=Jugador2;
    return jugador2->cantidadPartidasGanadas-jugador1->cantidadPartidasGanadas;
}
int imprimoRanking(void *d1, void *d2)
{
    tJugAPI *jugador = (tJugAPI*)d1;
    printf("\t\t\t |%-34s|%15d|\n", jugador->nombre, jugador->cantidadPartidasGanadas);
    return 0;
}
int respuestaInvalida(tMemoria* curlRegistro)
{
    return !curlRegistro->respuesta||strlen(curlRegistro->respuesta)==0||strcmp(curlRegistro->respuesta,"[]")==0;
}
size_t escrituraCallBack(void *dato, size_t tam, size_t ncant, void *respuestaUsuario)
{
    size_t ntam = tam * ncant;
    tMemoria *mem = respuestaUsuario;

    char *ptr = realloc(mem->respuesta, mem->tam + ntam + 1);
    if (ptr == NULL)
    {
        return 0;
    }

    mem->respuesta = ptr;
    memcpy(mem->respuesta+mem->tam, dato, ntam);
    mem->tam += ntam;
    *(mem->respuesta+mem->tam) = '\0';

    return ntam;
}
int tMemoriaCrear(tMemoria* memoria)
{
    memoria->respuesta=malloc(1);
    if(!memoria)
        return 0;
    memoria->tam=0;
    return 1;
}
int cargaRegistro(CURL *curl,tMemoria *curlRegistro)
{
    CURLcode codRes;
    tConfig config;
    char urlCC[288];
    if(!cargarConfig(NOMBRE_ARCH_CONFIG,&config))
    {
        puts("Error al cargar las configuraciones");
        return 0;
    }
    configDarUrlCC(&config,urlCC);
    curlRegistro->respuesta[0] = '\0';
    curl_easy_setopt(curl, CURLOPT_URL, urlCC);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, escrituraCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlRegistro);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    codRes=curl_easy_perform(curl);
    return codRes==CURLE_OK;
}
//Funciones Para el Posteo
int postearEstado(const tConfig *config,const char *json)
{
    CURL *urlDoce=curl_easy_init();
    struct curl_slist *tipoDato=NULL;
    CURLcode resultado;
    char url[288];
    long codigoHTTP;
    if(!urlDoce)
        return 0;
    //Inicializar La Url
    configDarUrl(config,url);
    curl_easy_setopt(urlDoce,CURLOPT_URL,url);
    curl_easy_setopt(urlDoce,CURLOPT_POST,1L);
    //Poner el Header adecuado y el contenido a postear
    tipoDato = curl_slist_append(tipoDato, "Content-Type: application/json");
    curl_easy_setopt(urlDoce, CURLOPT_HTTPHEADER, tipoDato);
    curl_easy_setopt(urlDoce, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(urlDoce, CURLOPT_SSL_VERIFYPEER, 0L);
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
void configDarUrl(const tConfig *config,char* destino)
{
    strcpy(destino,config->url);
}
void configDarUrlCC(const tConfig *config,char* destino)
{
    strcpy(destino,config->url);
    strcat(destino,"/");
    strcat(destino,config->codigo);
}
