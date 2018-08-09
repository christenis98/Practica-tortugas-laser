#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "juego.h"
bool cargarJuego(tJuego & juego) {
	string nombreFichero;
	bool ok = false;
	cout << "Introduzca nombre del fichero:   " << endl;
	cin >> nombreFichero;
	cout << "Introduzca el numero de jugadores:   " << endl;
	cin >> juego.numInJug;
	if (cargarTablero(juego.tablero, juego.numInJug, nombreFichero)) {
		ok = true;
		for (int i = 0; i < juego.numInJug; i++) {
			tMazo maso;
			crearVacia(maso);
			srand(time(NULL));
			int ran = rand();
			for (int i = 0; i < ran; i++) {
				crearMazoAleatorio(maso);
			}
			for (int j = 0; j < TAM_MAZO; j++) {
				juego.jugadores[i].mazo[j] = maso[j];
			}
			for (int k = 0; k < TAM_MAZO; k++) {
				juego.jugadores[i].mano[k] = VACIO;
			}
			for (int j = 0; j < 3; j++) {
				sacar(juego.jugadores[i].mazo, juego.jugadores[i].mano[j]);
			}
		}
	}
	else {
		cout << "error \n";
	}
	return ok;
}
void mostrarJuego(const tJuego & juego) {
	system("cls");
	dibujarTablero(juego.tablero);
	cout << endl;
	for (int i = 0; i < juego.numInJug; i++) {
		if ((juego.turno % juego.numInJug) == i) {
			cout << "> ";
		}
		else {
			cout << "  ";
		}
		cout << i << ". " << juego.jugadores[i].nombre;
		int j = 0, numAv = 0, numIz =0, numDch =0, numLas = 0;
		while (j < TAM_MAZO) {
			switch (juego.jugadores[i].mano[j])
			{
			case  AVANZAR: numAv++;
				break;
			case  GIROIZQUIERDA: numIz++;
				break;
			case  GIRODERECHA: numDch++;
				break;
			case  LASER: numLas++;
				break;
			default:
				break;
			}
			j++;
		}
		cout << " " << numAv << " ^ " << numDch << " > " << numIz << " < " << numLas << " ~ " << endl;
	}

}
bool ejecutarTurno(tJuego &juego) {
	char a;
	bool ok = false;
	cout << "Elija accion ( R para robar y E para crear y ejecutar una secuencia): " << endl;
	cin >> a;
	a = toupper(a);
	switch (a)
	{
	case 'R':  accionRobar(juego);
		break;
	case 'E': 
		tMazo mazo;
		tCarta carta;
		for (int i = 0; i < TAM_MAZO; i++) {
			mazo[i] = VACIO;
		}
		cout << "Presione una tecla\n Flecha arriba para avanzar \n Flecha derecha / izchierda para hacer un giro \n Espacio para laser \n Enter para salir )" << endl;
		tTecla tecla = leerTecla();
		int i = 0;
		bool todoCorrecto = true;
		do {
			todoCorrecto = true;
			while (tecla != SALIR && todoCorrecto) {
				bool esta[TAM_MAZO];
				for (int k = 0; k < TAM_MAZO; k++) {
					esta[k] = false;
				}
				int j = 0;
				do {
					if (juego.jugadores[juego.turno % juego.numInJug].mano[j] == tacla2Carta(tecla)) {
						esta[j] = true;
					}
					j++;
				} while (j < TAM_MAZO && !esta[j - 1]);
				if (esta[j - 1]) {
					carta = tacla2Carta(tecla);
					insertar(mazo, carta);
					cout << carta2char(mazo[i]);
					tecla = leerTecla();
					i++;
				}
				else {
					cout << carta2char(mazo[i]) << endl;
					cout << "No te quedan cartas de este tipo en la mano!!" << endl;
					todoCorrecto = false;
					cout << "Presione una tecla\n Flecha arriba para avanzar \n Flecha derecha / izchierda para hacer un giro \n Espacio para laser \n Enter para salir )" << endl;
					tecla = leerTecla();
				}
			}
			if (todoCorrecto) {
				sacar(juego.jugadores[juego.turno % juego.numInJug].mano, carta);
			}
		} while (!todoCorrecto);
		if (accionSecuencia(juego, mazo)) {
			ok = true;
		}//hay que revisar lo del turno
		break;
	}
	return ok;
}
bool accionRobar(tJuego & juego) {
	bool ok = false;
	int i = 0;
	while (juego.jugadores[juego.turno % juego.numInJug].mano[i] != VACIO) {
		i++;
	}
	i++;
	if (sacar(juego.jugadores[juego.turno % juego.numInJug].mazo, juego.jugadores[juego.turno % juego.numInJug].mano[i - 1])) {
		ok = true;
	}
	return ok;
}
bool accionSecuencia(tJuego & juego, tMazo & cartas){
	bool ok = false;
	int i = 0;
	int joyas1, joyas2;
	joyas1 = numeroJoyas(juego.tablero);
	realizarMovimiento(juego.tablero, coordenadaTortuga(juego.tablero, juego.turno % juego.numInJug), cartas);
	joyas2 = numeroJoyas(juego.tablero);
	if (joyas1 != joyas2) {
		ok = true;
	}
	return ok;
}
void cambiarTurno(tJuego &juego){
	juego.turno += 1;
} 
bool esFinDePartida(tJuego &juego){
	bool ok = false;
	if (accionSecuencia(juego, juego.jugadores[juego.turno % juego.numInJug].mazo)){
		ok = true;
	}
	return ok;
}
void incluirCarta(tMano &mano, tCarta carta){
	int i = 0;
	while (mano[i] != VACIO) {
		i++;
	}
	mano[i] = carta;
}