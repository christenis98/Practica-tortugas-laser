#ifndef CARTAS_H
#define CARTAS_H
#include <string>
using namespace std;
#include "Tablero.h"


typedef tCarta tMazo[TAM_MAZO];

void crearVacia(tMazo & mazo);
bool sacar(tMazo & mazo, tCarta & carta);
void insertar(tMazo & mazo, tCarta carta);
void crearMazoAleatorio(tMazo & mazo);

#endif