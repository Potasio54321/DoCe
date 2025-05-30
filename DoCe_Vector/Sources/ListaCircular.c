#include "../Headers/ListaCircular.h"
#include <stdlib.h>
#include <string.h>
#define min(a,b)((a)<(b)?(a):(b))

void crearLista360(tLista360 *pLista)
{
    *pLista=NULL;
}

void vaciarLista360(tLista360 *pLista)
{
    tNodo *elim=*pLista;
    tNodo *cursor=elim;
    //a b c d e -> a
    while(cursor!=*pLista)
    {
        cursor=elim->sig;
        free(elim->info);
        free(elim);
        elim=cursor;
    }
    free(cursor->info);
    free(cursor);
    *pLista=NULL;
}

int lista360Vacia(const tLista360* pLista)
{
    return *pLista==NULL;
}
int lista360Llena(const tLista360* pLista,size_t tamAgregar)
{
    return 0;
}
///Pone al segundo lugar
int ponerEnLista360Ini(tLista360 *pLista,const void* dato,size_t tamElem)
{
    tNodo *nuevo;
    nuevo=malloc(sizeof(tNodo*));
    if(!nuevo||!(nuevo->info=malloc(tamElem)))
    {
        free(nuevo);
        return 0;
    }
    memcpy(nuevo->info,dato,tamElem);
    nuevo->tamElem=tamElem;
    if(*pLista==NULL)
    {
        nuevo->sig=nuevo;
        *pLista=nuevo;
    }
    else
    {
        nuevo->sig=(*pLista)->sig;
        (*pLista)->sig=nuevo;
    }
    return 1;
}

int ponerEnLista360Fin(tLista360 *pLista,const void* dato,size_t tamElem)
{
    tNodo *nuevo;
    nuevo=malloc(sizeof(tNodo*));
    if(!nuevo||!(nuevo->info=malloc(tamElem)))
    {
        free(nuevo);
        return 0;
    }
    memcpy(nuevo->info,dato,tamElem);
    nuevo->tamElem=tamElem;
    if(*pLista==NULL)
        nuevo->sig=nuevo;
    else
    {
        nuevo->sig=(*pLista)->sig;
        (*pLista)->sig=nuevo;
    }
    *pLista=nuevo;
    return 1;
}
///Sacar desde el segundo lugar
int sacarEnLista360Ini(tLista360 *pLista,void* dato,size_t tamElem)
{
    tNodo *elim;
    if(*pLista==NULL)
        return 0;
    elim=(*pLista)->sig;
    if(*pLista==elim)
        *pLista=NULL;
    else
        (*pLista)->sig=elim->sig;
    memcpy(dato,elim->info,min(elim->tamElem,tamElem));
    free(elim->info);
    free(elim);
    return 1;
}

///Esta es una forma de sacar ineficiente porque debe recorrer toda la lista para sacar
int sacarEnLista360Fin(tLista360 *pLista,void* dato,size_t tamElem)
{
    tNodo *cursorelim=*pLista;
    if(*pLista==NULL)
        return 0;
    if((*pLista)->sig==*pLista)
        *pLista=NULL;
    else
    {
        while(cursorelim->sig!=*pLista)
        {
            cursorelim=cursorelim->sig;
        }
        *pLista=cursorelim;
        cursorelim=cursorelim->sig;
        (*pLista)->sig=cursorelim->sig;

    }
    memcpy(dato,cursorelim->info,min(cursorelim->tamElem,tamElem));
    free(cursorelim->info);
    free(cursorelim);
    return 1;
}

int recorrerLista360(const tLista360* pLista360, int (*accion)(void *a, void *b), void *param)
{
    tNodo *cursor;

    if(!*pLista360)
    {
        return -1;
    }
    //Correr Desde el Inicio
    cursor=(*pLista360)->sig;

    do
    {
        if(!accion(cursor->info,param))
            return 0;
        cursor=cursor->sig;
    }
    while(cursor != (*pLista360)->sig);
    return 1;
}
