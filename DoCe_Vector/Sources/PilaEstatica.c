#include "../Headers/PilaEstatica.h"
#include <string.h>
#define min(a,b)((a)>(b)?b:a)
void crearPila(tPila* pPila)
{
    pPila->tope=CANTTAMMAX;
}
void vaciarPila(tPila*pPila)
{
    pPila->tope=CANTTAMMAX;
}
int vertopePila(const tPila*pPila,void* dato,size_t tamDato)
{
    if(pPila->tope>=CANTTAMMAX)
        return 0;
    size_t tamReg;
    memcpy(&tamReg,pPila->pila+pPila->tope,sizeof(size_t));
    memcpy(dato,pPila->pila+pPila->tope+sizeof(size_t),min(tamReg,tamDato));
    return 1;
}
int sacarDePila(tPila*pPila,void* dato,size_t tamDato)
{
    if(pPila->tope>=CANTTAMMAX)
        return 0;
    size_t tamReg;
    memcpy(&tamReg,pPila->pila+pPila->tope,sizeof(size_t));
    pPila->tope+=sizeof(size_t);
    memcpy(dato,pPila->pila+pPila->tope,min(tamReg,tamDato));
    pPila->tope+=tamReg;
    return 1;
}
int ponerEnPila(tPila*pPila,const void* dato,size_t tamDato)
{
    if(tamDato+sizeof(size_t)>pPila->tope)
        return 0;
    pPila->tope-=tamDato;
    memcpy(pPila->pila+pPila->tope,dato,tamDato);
    pPila->tope-=sizeof(size_t);
    memcpy(pPila->pila+pPila->tope,&tamDato,sizeof(size_t));
    return 1;
}

int pilaLlena(const tPila*pPila,size_t tamDato)
{
    return tamDato>pPila->tope;
}
int pilaVacia(const tPila*pPila)
{
    return pPila->tope>=CANTTAMMAX;
}
