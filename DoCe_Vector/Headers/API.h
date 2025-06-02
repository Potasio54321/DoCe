#ifndef API_H_INCLUDED
#define API_H_INCLUDED
#include <stddef.h>
#define TAMNOMBRE 248
#define ERR_MEM 1
#define ERR_CURL 2
#define ERR_CJSON 3
//NombreArchivoConfig
#define NOMBRE_ARCH_CONFIG "Config.txt"
#define URL_API "https://algoritmos-api.azurewebsites.net/api/doce"
#define URL_API2 "https://algoritmos-api.azurewebsites.net/api/doce/arreglo"

typedef struct{
    char* respuesta;
    size_t tam;
}tMemoria;

typedef struct{
    char nombre[35];
    unsigned cantidadPartidasGanadas;
}tJugAPI;

typedef struct
{
    char url[256];
    char codigo[32];
}tConfig;

int verRanking();
int cargarConfig(const char* nombreArchConfig,tConfig* config);
int postearEstado(const tConfig *config,const char *json);

void recuperar_de_api(void);
void enviarResultadoJugadorAPI(char *nombreJugador, int vencedor, const char *codigoGrupo);


#endif // API_H_INCLUDED
