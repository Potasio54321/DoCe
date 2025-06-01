#ifndef GRAFICA_H_INCLUDED
#define GRAFICA_H_INCLUDED
//Menu
#define CONDJUGAR 'A'
#define CONDVERRANKING 'B'
#define CONDSALIR 'C'
//grafica
#define INTRODUCCION 0
#define VICTORIA 1
#define DERROTA 2
#define MAZOMEZCLADO 3
#define RANKING 4
#define MENU 5
#define INGRESOJUGADOR 6
#define INGRESODIFICULTAD 7
#define JUEGAJUGADOR 8
#define JUEGAMAQUINA 9

void grafica(int opc);
int menu(char opcion);
void print_carta_mas1();
void print_carta_mas2();
void print_carta_menos1();
void print_carta_menos2();
void print_carta_espejo();
void print_carta_repetir();

#endif // GRAFICA_H_INCLUDED
