#include "../Headers/lista.h"
#include <stdlib.h>
#include <string.h>
#define min(a,b)((a)<(b)?(a):(b))
void* buscarMin(tLista * cursor,Cmp cmp);
void crearLista(tLista *lista)
{
    *lista=NULL;
}
int listaVacia(const tLista* lista)
{
    return *lista==NULL;
}
int listaLlena(const tLista* lista,size_t TamAAgregar)
{
    tNodo *verificarMem=malloc(sizeof(tNodo));
    verificarMem->info=malloc(TamAAgregar);
    free(verificarMem->info);
    free(verificarMem);
    return !verificarMem->info||!verificarMem;
}
void vaciarLista(tLista* lista)
{
    while(*lista!=NULL)
    {
        free((*lista)->info);
        free(*lista);
        *lista=(*lista)->sig;
    }
}
int ponerUltLista(tLista* lista,const void* dato,size_t tamDato)
{
    tNodo*Nuevo=malloc(sizeof(tNodo));
    if(!Nuevo||!(Nuevo->info=malloc(tamDato)))
    {
        free(Nuevo);
        return 0;
    }
    while ((*lista))
    {
        lista=&(*lista)->sig;
    }
    memcpy(Nuevo->info,dato,tamDato);
    Nuevo->tamElem=tamDato;
    Nuevo->sig=NULL;
    *lista=Nuevo;
    return 1;
}
int sacarUltLista(tLista* lista,void* dato,size_t tamDato)
{
    if (!*lista)
    {
        return 0;
    }
    while ((*lista)->sig)
    {
        lista=&(*lista)->sig;
    }
    memcpy(dato,(*lista)->info,min(tamDato,(*lista)->tamElem));
    free((*lista)->info);
    free(*lista);
    *lista=NULL;
    return 1;
}
int verUltimoLista(const tLista* lista,void* dato,size_t tamDato)
{
    if (!*lista)
    {
        return 0;
    }
    while ((*lista)->sig)
    {
        lista=&(*lista)->sig;
    }
    memcpy(dato,(*lista)->info,min(tamDato,(*lista)->tamElem));
    return 1;
}
int ponerPrincipioLista(tLista* lista,const void* dato,size_t tamDato)
{
    tNodo*Nuevo=malloc(sizeof(tNodo));
    if(!Nuevo||!(Nuevo->info=malloc(tamDato)))
    {
        free(Nuevo);
        return 0;
    }
    memcpy(Nuevo->info,dato,tamDato);
    Nuevo->tamElem=tamDato;
    Nuevo->sig=*lista;
    *lista=Nuevo;
    return 1;
}
int sacarPrimeroLista(tLista* lista,void* dato,size_t tamDato)
{
    if(!*lista)
        return 0;
    tNodo *elim=*lista;
    memcpy(dato,elim->info,min(tamDato,elim->tamElem));
    *lista=elim->sig;
    free(elim->info);
    free(elim);
    return 1;
}
int verPrimeroLista(const tLista* lista,void* dato,size_t tamDato)
{
    if(!*lista)
        return 0;
    memcpy(dato,(*lista)->info,min(tamDato,(*lista)->tamElem));
    return 1;
}
int insertarOrdenadoLista(tLista *pLista,const void* dato,size_t tamDato,Cmp cmp,int dup)
{
    tNodo*Nuevo;
    int rComp=1;

    while(*pLista&&(rComp=cmp((*pLista)->info,dato)<0))
    {
        pLista=&(*pLista)->sig;
    }
    if(rComp==0&&!dup)
    {
        return 0;
    }
    if(!(Nuevo=malloc(sizeof(tNodo)))||!(Nuevo->info=malloc(tamDato)))
    {
        free(Nuevo);
        return 0;
    }
    memcpy(Nuevo->info,dato,tamDato);
    Nuevo->tamElem=tamDato;
    Nuevo->sig=*pLista;
    *pLista=Nuevo;
    return 1;
}
int elimOrdLista(tLista *plista,void* dato,Cmp cmp)
{
    tNodo *elim;
    int rComp;
    while(plista&&(rComp=cmp((*plista)->info,dato)>0))
    {
        plista=&(*plista)->sig;
    }
    if(!plista||rComp!=0)
        return 0;
    elim=*plista;
    free(elim->info);
    free(elim);
    *plista=elim->sig;
    return 1;
}
int elimElemLista(tLista *plista,void* dato,Cmp cmp)
{
    tNodo *elim;
    int rComp;
    while(plista&&(rComp=cmp((*plista)->info,dato)!=0))
    {
        plista=&(*plista)->sig;
    }
    if(!plista)
        return 0;
    elim=*plista;
    free(elim->info);
    free(elim);
    *plista=elim->sig;
    return 1;
}
int recorrerLista(tLista* pLista, void* Dato,ACT accion)
{
    if (!*pLista)
    {
        return 0;
    }
    while ((*pLista))
    {
        if(accion((*pLista)->info,Dato))
            return 0;
        pLista=&(*pLista)->sig;
    }
    return 1;
}
int ordenadoSeleccionLista(tLista* pLista,Cmp cmp)
{
    tLista *min;
    tNodo paraCopiar;
    while ((*pLista)->sig)
    {
        min=buscarMin(pLista,cmp);
        paraCopiar=*(*pLista);
        (*pLista)->info=(*min)->info;
        (*pLista)->tamElem=(*min)->tamElem;
        (*min)->info=paraCopiar.info;
        (*min)->tamElem=paraCopiar.tamElem;
        pLista=&((*pLista)->sig);
    }
    return 1;
}
void* buscarMin(tLista * cursor,Cmp cmp)
{
    tLista *min=cursor;
    while (*cursor)
    {
        if(cmp((*cursor)->info,(*min)->info)<0)
            min=cursor;
        cursor=&((*cursor)->sig);
    }
    return min;
}
