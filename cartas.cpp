#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include "Cartas.h"

void crearVacia(tMazo & mazo) {
	for (int i = 0; i < TAM_MAZO; i++) {
		if (i < 18) {
			mazo[i] = AVANZAR;
		}else if (i >= 18 && i < 26) {
			mazo[i] = GIRODERECHA;
		}
		else if (i >= 26 && i < 34) {
			mazo[i] = GIROIZQUIERDA;
		}
		else {
			mazo[i] = LASER;
		}
	}
	
}
bool sacar(tMazo & mazo, tCarta & carta) {
	bool ok = false;
	bool enc = false;
	carta = mazo[0];
	if (mazo[0] != VACIO) {
		ok = true;
		int acum = 0;
		for (int i = 0; i < TAM_MAZO && !enc; i++) {
			mazo[i] = mazo[i + 1];
		}
		int i = TAM_MAZO - 1;
		while (mazo[i] == VACIO) {
			i--;
		}
		mazo[i] = VACIO;
	}
	return ok;
}
void insertar(tMazo & mazo, tCarta carta) {
	int i = TAM_MAZO - 1;
	while (mazo[i] == VACIO) {
		i--;
	}
	mazo[i + 1] = carta;
}
void crearMazoAleatorio(tMazo & mazo) {
	random_shuffle(&mazo[0], &mazo[TAM_MAZO - 1]);
}
