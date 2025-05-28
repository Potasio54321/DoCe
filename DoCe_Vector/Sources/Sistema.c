#include "..\Headers\Sistema.h"
#include <string.h>
#include <ctype.h>
#define TAMBUFFER 256
int limpiarBuffer(char *bufferOriginal);

void limpiarPantalla(void)
{
    system("cls");
}
void pausarPantalla(void)
{
    system("pause");
}
void registrarInput(char *buffer, size_t tamBuffer, Cond cond)
{
    fgets(buffer, tamBuffer, stdin);
    while(!cond(buffer) || limpiarBuffer(buffer))
    {
        fgets(buffer, tamBuffer, stdin);
    }
    *(strchr(buffer,'\n'))='\0';
}
int limpiarBuffer(char *bufferOriginal)
{
    char bufferLimpieza[TAMBUFFER];
    if(strchr(bufferOriginal,'\n')!=NULL)
        return 0;
    while (strchr(bufferLimpieza,'\n')==NULL)
    {
        fgets(bufferLimpieza, TAMBUFFER, stdin);
    }
    return 1;
}
int condIgual3(const void *Buffer)
{
    const char *buffer = Buffer;
    return buffer[2] == '\0';
}
int condInsercionAceptable(const void *Buffer)
{
    const char *buffer = Buffer;
    return strlen(buffer)>1;
}
int strAInt(int *numero,const char* str)
{
    return sscanf(str,"%d",numero);
}
int esNombreValido(const char *nombre)
{
    while(*nombre&&*nombre!='\n')
    {
        if (!isalpha(*nombre))
            return 0;
        nombre++;
    }
    return 1;
}
