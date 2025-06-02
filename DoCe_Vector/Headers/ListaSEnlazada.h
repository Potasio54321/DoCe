#ifndef LISTASENLAZADA_H_INCLUDED
#define LISTASENLAZADA_H_INCLUDED
#include <stddef.h>
typedef struct sNodo
{
    void* info;
    size_t tamElem;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;
typedef int (*Cmp)(const void*a,const void* b);
typedef int (*ACT)(void*,void*);

void crearLista(tLista *pLista);
void vaciarLista(tLista *pLista);

int listaVacia(const tLista* pLista);
int listaLlena(const tLista* pLista,size_t tamAgregar);

int ponerPrincipioLista(tLista* pLista,const void* dDato,size_t tamDato);
int ponerUltLista(tLista* pLista,const void* dDato,size_t tamDato);

int sacarPrimeroLista(tLista* pLista,void* dDato,size_t tamDato);
int sacarUltLista(tLista* pLista,void* dDato,size_t tamDato);

int verPrimeroLista(const tLista* pLista,void* dDato,size_t tamDato);
int verUltimoLista(const tLista* pLista,void* dDato,size_t tamDato);
int insertarOrdenadoLista(tLista *pLista,const void* dDato,size_t tamDato,Cmp cmp,int dup);
int elimElemLista(tLista *plista,void* dDato,Cmp cmp);
int elimOrdLista(tLista *plista,void* dDato,Cmp cmp);

int recorrerLista(tLista* pLista,void* dDato,ACT accion);
int ordenadoSeleccionLista(tLista* pLista,Cmp cmp);

#endif // LISTASENLAZADA_H_INCLUDED
