#include <iostream>
#include <fstream>>
#include <istream>
#include <string>
#include "Puntuaciones.h"
using namespace std;

bool cargarPuntuaciones(tPuntuaciones &puntos) {
	bool cargado = false;
	char basura;
	string basurilla;
	ifstream archivo;
	archivo.open("Puntuaciones.txt");
	if (archivo.is_open()) {
		for (int i = 0; i < puntos.iterador; i++) {
			getline(archivo, basurilla);
		}
		archivo >> puntos.nombre;
		archivo.get(basura);		
		archivo >> puntos.puntuacion;
		archivo.get(basura);
		cargado = true;
	}
	
	archivo.close();
	return cargado;
}

void guardarPuntuaciones(const tPuntuaciones & puntos) {
	string basurilla;
	fstream archivo("Puntuaciones.txt");
	for (int i = 0; i < puntos.iterador; i++) {
		getline(archivo, basurilla);
	}
	archivo << puntos.nombre << " " << puntos.puntuacion << "\n";
	archivo.close();
}

void mostrarPuntuaciones(const tPuntuaciones & puntos) {
	
	cout << puntos.nombre << " " << puntos.puntuacion << "\n";
}
bool actualizarPuntuacion(tPuntuaciones & puntos, const string &nombre, int nuevos) {
	bool verdad = false;
	for (int i = 0; i < MAXIMO; i++) {
		cargarPuntuaciones(puntos);
		if (puntos.nombre == nombre) {
			guardarPuntuaciones(puntos);
		}
	}
	return verdad;
}