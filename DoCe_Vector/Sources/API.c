#include "../Headers/API.h"
#include "../Headers/funcioneslista.h"
size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;
    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if (ptr == NULL) {
        return 0;
    }
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, total_size);
    mem->size += total_size;
    mem->response[mem->size] = '\0';
    return total_size;
}

void recuperar_de_api(void) {

    tLista listaJug;
    tJugAPI jug;
    crearLista(&listaJug);

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error al inicializar cURL\n");
        return;
    }
    struct Memory chunk = { .response = malloc(1), .size = 0 };
    if (chunk.response == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        curl_easy_cleanup(curl);
        return;
    }
    chunk.response[0] = '\0';
    curl_easy_setopt(curl, CURLOPT_URL, URL_API2);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error en la peticion GET: %s\n", curl_easy_strerror(res));
    } else {
        if (chunk.response == NULL || strlen(chunk.response) == 0 || strcmp(chunk.response, "[]") == 0) {
            printf("No hay datos disponibles en la API.\n");
        } else {
            cJSON *json_respuesta = cJSON_Parse(chunk.response);
            if (!json_respuesta) {
                printf("Error al parsear JSON: %s\n", cJSON_GetErrorPtr());
            } else {
                if (!cJSON_IsArray(json_respuesta)) {
                    printf("El JSON no es un array como se esperaba.\n");
                } else {
                    int num_jugadores = cJSON_GetArraySize(json_respuesta);

                    for (int i = 0; i < num_jugadores; i++) {
                        cJSON *jugador = cJSON_GetArrayItem(json_respuesta, i);
                        cJSON *nombre = cJSON_GetObjectItem(jugador, "nombreJugador");
                        cJSON *puntos = cJSON_GetObjectItem(jugador, "cantidadPartidasGanadas");
                        memcpy(jug.nombre, nombre->valuestring, sizeof(jug.nombre));
                        jug.puntos = puntos->valueint;
                        ponerPrimeroLista(&listaJug, &jug, sizeof(tJugAPI));
                    }
                }
                cJSON_Delete(json_respuesta);
            }
        }
    }
    ordenarLista(&listaJug, comparoPorPuntaje);
//    grafica(4);
    printf("\n\t\t\t\tNombre:\tPuntos:\n");
    recorrerLista(&listaJug, imprimoRanking, NULL);
    curl_easy_cleanup(curl);
    free(chunk.response);
}
void enviarResultadoJugadorAPI(char *nombreJugador, int vencedor, const char *codigoGrupo)
{
    if (!nombreJugador || !codigoGrupo) {
        fprintf(stderr, "Error: Datos de jugador o CodigoGrupo inválidos.\n");
        return;
    }


    cJSON *json_raiz = cJSON_CreateObject();
    if (!json_raiz) {
        fprintf(stderr, "Error al crear el objeto JSON raiz.\n");
        return;
    }

    cJSON_AddStringToObject(json_raiz, "CodigoGrupo", codigoGrupo);

    cJSON *json_jugador = cJSON_CreateObject();
    if (!json_jugador) {
        fprintf(stderr, "Error al crear el objeto JSON de jugador.\n");
        cJSON_Delete(json_raiz);
        return;
    }

    cJSON_AddStringToObject(json_jugador, "nombre", nombreJugador);
    cJSON_AddNumberToObject(json_jugador, "vencedor", vencedor);

    cJSON_AddItemToObject(json_raiz, "jugador", json_jugador);

    char *json_str = cJSON_PrintUnformatted(json_raiz);
    if (!json_str) {
        fprintf(stderr, "Error al generar JSON.\n");
        cJSON_Delete(json_raiz);
        return;
    }
    printf("JSON enviado:\n%s\n", json_str);

    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, URL_API);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        printf("Código de respuesta HTTP: %ld\n", response_code);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error en la petición: %s\n", curl_easy_strerror(res));
        } else {
            printf("Resultado del jugador enviado con éxito.\n");
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    cJSON_Delete(json_raiz);
    free(json_str);
}

