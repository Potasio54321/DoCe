#include "..\Headers\funcioneslista.h"
#include "../Headers/API.h"
#define SINMEMORIA 0
#define LISTAVACIA 0
#define POSINVALIDA 0
#define DUPLICADO 0
#define NOENCONTRADO 0
#define OK 1
#define MIN(X,Y) (X)<(Y)?X:Y



void crearLista(tLista *pl){///PONER EL PUNTERO A LISTA EN NULO
    *pl=NULL;
}

int ponerPrimeroLista (tLista *pl, const void *dt, unsigned tam){
    tNodo *nue=(tNodo*)malloc(sizeof(tNodo));///reserva espacio para el nuevo nodo
    if(!nue){
        return SINMEMORIA;
    }
    ///nue es un nodo con: *info, tam y sig
    nue->info = malloc(tam);///reservo espacio para la info
    if(!nue->info){
        free(nue);
        return SINMEMORIA;
    }

    memcpy(nue->info,dt,tam); ///copio la info
    nue->taminfo = tam; ///copio el tam
    ///PARA PONER -> DESENGANCHO Y ENGANCHO DONDE CONVIENE

    nue->sig = *pl;
    *pl = nue;

    return OK;
}

int sacarPrimeroLista (tLista *pl, void *dt, unsigned tam){
    tNodo * aux; ///SACAR NECESITA UN AUXILIAR PARA PODER HACER EL FREE Y QUE SE PUEDA DESENGANCHAR

    aux = *pl; ///CHEQUEO Q HAYA ALGO EN LISTA ANTES DE SACAR!!!!!!
    if(!aux){ ///si aux apunta a NULL -> LISTA VACIA
        return LISTAVACIA;
    }

    ///hay que devolver el dato -> SIEMPRE AL MENOR TAM
    memcpy(dt,aux->info,MIN(tam,aux->taminfo));

    ///desengancho
    *pl = (*pl)->sig;
    free(aux->info);
    free(aux);

    return OK;
}

int ponerPosLista (tLista *pl, const void *dt, unsigned tam, unsigned pos){
        tNodo *nue; ///poner requiere generar el nodo

        while (*pl && pos) ///voy restando hasta llegar a la posicion
        {
            pl = &(*pl)->sig;
            pos--;
        }

        if(pos){///VERIFICAR QUE SE HAYA ENCONTRADO LA POSICI�N
            return POSINVALIDA;
        }

        nue = (tNodo*) malloc(sizeof(tNodo));
        if(!nue){
            return SINMEMORIA;
        }

        nue->info = malloc(tam);
        if(!nue->info){
            free(nue);
            return SINMEMORIA;
        }

        memcpy(nue->info,dt,tam);
        nue->taminfo=tam;
        nue->sig = *pl;
        *pl = nue;

        return OK;
}

int ponerUltLista (tLista *pl, const void *dt, unsigned tam){
    while(*pl){
        pl = &(*pl)->sig;
    }
    tNodo *nue;
      nue = (tNodo*) malloc(sizeof(tNodo));
        if(!nue){
            return SINMEMORIA;
        }

        nue->info = malloc(tam);
        if(!nue->info){
            free(nue);
            return SINMEMORIA;
        }

        memcpy(nue->info,dt,tam);
        nue->taminfo=tam;
        nue->sig = *pl;
        *pl = nue;
    return OK;
}

int ponerOrdenLista(tLista *pl, const void *dt, unsigned tam, int (*cmp)(const void*, const void*)){
    tNodo *nue;
    int rc;

    while(*pl && (rc=cmp(dt,(*pl)->info))>0){
        pl=&(*pl)->sig;
    }
    ///Si rc = 0 es pq compar� con un NULL (es el 1ero) o pq es igual
    ///si es el primero -> la lista no existe y el resultado es 0
    ///para que sea dupli: la lista existe (no es el primero) y rc es 0
    if(*pl && !rc){ ///SI ESTA DUPLICADO (RC=0) SIEMPRE EXISTE LA LISTA: SINO LA COMPARACION ES CONTRA NULL
        return DUPLICADO;
    }

    nue =(tNodo*) malloc (sizeof (tNodo));

    if(!nue){
        return SINMEMORIA;
    }

    nue->info = malloc (tam);

    if(!nue->info){
        free(nue);
        return SINMEMORIA;
    }

    memcpy(nue->info,dt,tam);
    nue->taminfo = tam;

    nue->sig = *pl;
    *pl = nue;
    return OK;

}

int sacarElemLista (tLista *pl, void *dt, unsigned tam, int (*cmp)(const void*, const void*)){
    tNodo *aux;


    while(*pl && cmp(dt,(*pl)->info)!=0){
        pl = &(*pl)->sig;
    }

    if(!*pl){///SI LA LISTA NO EXISTE ENTONCES ES QUE NO LO ENCONTR� NO NECESITA EL RC.
        return NOENCONTRADO;
    }

    aux = *pl;

    memcpy(dt,aux->info,MIN(tam,aux->taminfo));

    ///debo desenganchar el nodo antes de eliminarlo
    *pl = aux->sig;

    free(aux->info);
    free(aux);
    return OK;
}
///Cuando la lista esta ordenada si voy pasando y llego al 3 (buscaba 2) ya asumo que el elemento no esta
///EN LUGAR DE RECORRER TOOODA LA LISTA COMO SACAR ELEMENTO LISTA
int sacarElemOrdenadoLista (tLista *pl, void *dt, unsigned tam, int (*cmp)(const void*, const void*)){
        tNodo *elim;
        int rc; ///si necesita el rc pq va comparando cuando se pasa
        while(*pl && (rc=cmp(dt,(*pl)->info))>0){
            pl = &(*pl)->sig;
        }

        if(!*pl || rc<0){
            return NOENCONTRADO;
        }

        ///si existe la lista -> rc debe ser == 0 -> encontrado

        elim = *pl;

        memcpy(dt,elim->info,MIN(elim->taminfo,tam));

        ///primero reconecta con el sig y luego free

        *pl = elim->sig;
        free(elim->info);
        free(elim);
        return OK;
}


int recorrerLista(tLista *pl, int (*accion)(void*,void*), void*param){
    if(!*pl){
        return -1;
    }

    while(*pl){
        if (accion((*pl)->info,param))
            return 0;
        pl = &(*pl)->sig;
    }
    return 1;
}

void mostrarENTEROLista(void *pl,void*param){
    int *aux;

        aux = (int*)pl;
        printf("%d - ",*aux);

}


void eliminarDuplicados(tLista *pl, int (*cmp)(const void*, const void*),
                                     void (*accion)(void*,void*)){
}


int comparaEntero(const void *a, const void *b){
    const int *aux = (const int*)a;
    const int *auxb= (const int*)b;

    return (*aux-*auxb);
}

void vaciarLista(tLista *pl){
    tNodo *elim;

    while(*pl){
        elim=*pl;
        *pl=elim->sig;

        free(elim->info);
        free(elim);
    }

}


void intercambiar(tLista *a, tLista *b){
    void *auxinfo = (*a)->info;
    size_t auxtam = (*a)->taminfo;


    (*a)->taminfo = (*b)->taminfo;
    (*b)->taminfo = auxtam;


    (*a)->info = (*b)->info;
    (*b)->info = auxinfo;

}

void ordenarLista(tLista *pl, int (*cmp)(const void *, const void*)){
    tLista *pri = pl;
    if(!(*pl))
        return;
    while((*pl)->sig)
    {
        if(cmp((*pl)->info, (*pl)->sig->info) < 0)
        {
            tLista *q = pri;
            tNodo *aux = (*pl)->sig;
            (*pl)->sig = aux->sig;
            while(cmp((*q)->info, aux->info) > 0)
                q = &(*q)->sig;
            aux->sig = *q;
            *q = aux;
        }
        else
            pl = &(*pl)->sig;
    }
}

int comparoPorPuntaje(const void *d1, const void *d2)
{
    tJugAPI *jug1 = (tJugAPI*)d1;
    tJugAPI *jug2 = (tJugAPI*)d2;
    return(jug1->puntos - jug2->puntos);
}
