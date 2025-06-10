#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stddef.h>
#define ACCIONOK 1
typedef struct sNodo
{
    void* info;
    size_t tamElem;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista360;

void crearLista360(tLista360 *pLista360);
void vaciarLista360(tLista360 *pLista360);

int lista360Vacia(const tLista360* pLista360);
int lista360Llena(const tLista360* pLista360,size_t tamAgregar);

int ponerEnLista360Ini(tLista360 *pLista360,const void* dato,size_t tamElem);
int ponerEnLista360Fin(tLista360 *pLista360,const void* dato,size_t tamElem);

int sacarEnLista360Ini(tLista360 *pLista360,void* dato,size_t tamElem);
int sacarEnLista360Fin(tLista360 *pLista360,void* dato,size_t tamElem);
int verFinLista360(tLista360 *pLista,void* dato,size_t tamElem);

void recorrerLista360(const tLista360* pLista360, int (*ACT)(void *a, void *b), void *param);
int recorrerLista360ConCond(const tLista360* pLista360, int (*accion)(void *a, void *b), void *param);


#endif // LISTA_H_INCLUDED
