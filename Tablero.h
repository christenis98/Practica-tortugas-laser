#ifndef TABLERO_H
#define TABLERO_H
#include <string> 
using namespace std;
const int FIL = 8;
const int COL = 8;
const int MAX_JUGADORES = 4;

const int incF[] = { -1, 0, 1, 0 };
const int incC[] = { 0, 1, 0, -1 };
const int TAM_MAZO = 38;


typedef enum { VACIO, AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER } tCarta;
typedef tCarta tVCartas[TAM_MAZO];
typedef enum { UP, RIGHT, DOWN, LEFT } tDir;
typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { AVANZA, DERECHA, IZQUIERDA, LASR , SALIR, NADA }tTecla;

typedef struct
{
	int num;               //0 SI NO ES TORTUGA, NÚMERO DE LA TORTUGA (DE 1 A 4, SEGÚN EL NÚMERO DE JUGADORES)
	tDir dir;             //... HACIA LA QUE MIRA
} tTortuga;

typedef struct
{
	tEstadoCasilla estado;
	tTortuga tortuga;
} tCasilla;

typedef tCasilla tTablero[FIL][COL];

typedef struct
{
	int x;
	int y;
} tCoordenada;
tCoordenada coordenadaTortuga(tTablero tablero, int num);
void colorFondo(int color);
int numeroJoyas(tTablero tablero);
tCasilla char2Casilla(char a);
tCarta tacla2Carta(tTecla tecla);
string casilla2char(tCasilla casilla);
void dibujarTablero(const tTablero tablero);
bool cargarTablero(tTablero tablero, int num_jugadores,string archivo);
void laser(tTablero & tablero, tCoordenada coor, tDir dir);
bool resuelveCaso();
bool compCoord(tCoordenada & coor);
bool compMov(tTablero tablero, tCoordenada  coor, tDir  dir);
void avanza(tTablero & tablero, tCoordenada & coor, tDir & dir);
void char2carta(tVCartas & cartas, int num);
void realizarMovimiento(tTablero & tablero, tCoordenada coordenada, tVCartas cartas);
tTecla leerTecla();
char carta2char(tCarta carta);

#endif // !TABLERO_H