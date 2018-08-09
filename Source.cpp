/*
Cristian Anei y Alvaro Corrochano F17
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Tablero.h"
#include "juego.h"
#include "Cartas.h"
#include "Puntuaciones.h"

int menu();
void caso1(tJuego & juego);
void juego();

int main() {
	juego();
	return 0;
}

void juego() {
	tJuego juego;
	tPuntuaciones puntos;
	string depurar;
	puntos.iterador = 0;
	int men = menu();
	while (men != 0) {
		switch (men)
		{
		case 1:
			if (cargarPuntuaciones(puntos)) {
				caso1(juego);
			}
			break;
		case 2:
			puntos.iterador = 0;
			depurar = "nada";
			system("cls");
			for (int i = 0; i < MAXIMO; i++) {
				bool ok;
				ok = cargarPuntuaciones(puntos);
				if (ok == false) {
					cout << "No se ha podido abrir el archivo Puntuaciones.txt o el archivo no existe.\n";
				}
				else {
					if (depurar != puntos.nombre) {
						mostrarPuntuaciones(puntos);
					}

				}
				depurar = puntos.nombre;
				puntos.iterador++;
			}
			system("pause");
			system("cls");
			break;
		default:
			break;
		}
		men = menu();
	}
}

int menu() {
	int num;
	bool ok = false;
	cout << "1. Jugar \n2. Mostrar puntuaciones \n0. Salir" << endl;
	while (!ok) {
		cin >> num;
		if (num < 3 && num >= 0) {
			ok = true;
		}
		else {
			cout << "Numero incorrecto \n";
		}
	}
	return num;
}

void caso1(tJuego & juego) {
	if (cargarJuego(juego)) {
		for (int i = 0; i < juego.numInJug; i++) {
			cout << "Introduzca nombre de un jugador ( " << i << "/" << juego.numInJug << " ) :" << endl;
			cin >> juego.jugadores[i].nombre;
		}	//pide nombres
		juego.turno = 0;
		mostrarJuego(juego);
		bool fin = false;
		while (!fin) {
			if (ejecutarTurno(juego)) {
				fin = true;
			}
			cambiarTurno(juego);
			mostrarJuego(juego);
		}
	}
	else {
		cout << "No se pudo cargar el tablero" << endl;
	}
}