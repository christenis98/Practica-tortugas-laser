#ifndef JUEGO_H
#define JUEGO_H



#include <string>
using namespace std;
#include "Tablero.h"
#include "Cartas.h"
typedef tCarta tMano[TAM_MAZO];
typedef struct {
	string nombre;
	tMazo mazo;
	tMano mano;
	tCoordenada coor;
}tJugador;
typedef struct {
	int numInJug;
	int turno;
	tJugador jugadores[MAX_JUGADORES];
	tTablero tablero;
}tJuego;
bool cargarJuego(tJuego & juego);
void mostrarJuego(const tJuego & juego);
bool ejecutarTurno(tJuego &juego);
bool accionRobar(tJuego & juego);
bool accionSecuencia(tJuego & juego, tMazo & cartas);
void cambiarTurno(tJuego &juego);
bool esFinDePartida(tJuego &juego);
void incluirCarta(tMano &mano, tCarta carta);
#endif // !JUEGO_H