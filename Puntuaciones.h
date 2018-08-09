#ifndef PUNTUACIONES_H
#define PUNTUACIONES_H
#include <string>
using namespace std;


typedef struct {
	string nombre;
	int puntuacion;
	int iterador;
}tPuntuaciones;
const int MAXIMO = 5;

bool cargarPuntuaciones(tPuntuaciones &puntos);
void guardarPuntuaciones(const tPuntuaciones & puntos);
void mostrarPuntuaciones(const tPuntuaciones & puntos);
bool actualizarPuntuacion(tPuntuaciones & puntos, const string &nombre, int nuevos);

#endif