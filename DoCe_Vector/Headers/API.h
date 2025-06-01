#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "Juego.h"


#define URL_API "https://algoritmos-api.azurewebsites.net/api/doce"
#define URL_API2 "https://algoritmos-api.azurewebsites.net/api/doce/arreglo"

struct Memory {
    char *response;
    size_t size;
};

typedef struct{
    char nombre[35];
    int puntos;
}tJugAPI;


size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
void recuperar_de_api(void);
void enviarResultadoJugadorAPI(char *nombreJugador, int vencedor, const char *codigoGrupo);


#endif // API_H_INCLUDED
