#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
using namespace std;
#include "Tablero.h"




bool resuelveCaso() {
	bool encontradosDatos = false;
	string linea, baSURa;
	// leer los datos de la entrada
	// numJugadores == 0 es false
	int numJugadores = 0, tortugaConLaser = 0, num = 0;
	cin >> numJugadores;
	cin >> tortugaConLaser;
	cin >> num;
	if (numJugadores > 0) {
		encontradosDatos = true;
		tTablero tablero;
		tVCartas cartas;
		char2carta(cartas, num);
		
		tCoordenada coor;
		// Busca la tortuga a la que le toca jugar
		bool enc = false;
		int k = 0;
		for (int i = 0; i < FIL && !enc; ++i) {
			for (int j = 0; j < COL && !enc; ++j) {
				if (tablero[i][j].estado == TORTUGA) {
					k++;
					if (k == tortugaConLaser) {
						enc = true;
						coor.x = i;
						coor.y = j;
					}
				}
			}
		}
		// LLamada a la función laser
		realizarMovimiento(tablero, coor, cartas);
		// Mostrar tablero de salida
		dibujarTablero(tablero);
		// Para leer los tableros que no se han usado.
		// Son tableros del caso que se encuentran despues del tablero que se carga
		getline(cin, linea);
		while (cin && linea != "---") {
			getline(cin, linea);
		}
	}
	return encontradosDatos;
}

bool compCoord(tCoordenada & coor) {
	bool ok;
	if ((coor.x < FIL) && (coor.x >= 0) && (coor.y < COL) && (coor.y >= 0)) {
		ok = true;
	}
	else {
		ok = false;
	}
	return ok;
}

bool compMov(tTablero tablero, tCoordenada coor, tDir dir) {
	bool ok = false;
	tCoordenada coordenada1, coordenada2;
	coordenada1.x = coor.x + incF[dir];
	coordenada1.y = coor.y + incC[dir];
	coordenada2.x = coor.x + incF[dir] + incF[dir];
	coordenada2.y = coor.y + incC[dir] + incC[dir];
	if ((tablero[coordenada1.x][coordenada1.y].estado != HIELO) &&
		(tablero[coordenada1.x][coordenada1.y].estado != MURO) &&
		(tablero[coordenada1.x][coordenada1.y].estado != TORTUGA) &&
		compCoord(coordenada1)) {
		if (tablero[coordenada1.x][coordenada1.y].estado == CAJA) {
			if ((tablero[coordenada2.x][coordenada2.y].estado != HIELO) &&
				(tablero[coordenada2.x][coordenada2.y].estado != MURO) &&
				(tablero[coordenada2.x][coordenada2.y].estado != TORTUGA) &&
				(tablero[coordenada2.x][coordenada2.y].estado != CAJA) &&
				(tablero[coordenada2.x][coordenada2.y].estado != JOYA) &&
				compCoord(coordenada2)) {
				ok = true;
			}
		}
		else {
			ok = true;
		}
	}

	return ok;
}

void dibujarTablero(const tTablero tablero)
{
	for (int fil = 0; fil < FIL; fil++) {
		for (int col = 0; col < COL; col++) {
			cout << casilla2char(tablero[fil][col]);
			colorFondo(0);
		}
		cout << endl;
	}
	cout << endl;
}

bool cargarTablero(tTablero tablero, int num_jugadores, string archivo)
{
	int num;
	bool ok = false;
	string basura, linea;
	ifstream fichero;
	fichero.open(archivo);
	if (fichero.is_open()) {
		fichero >> num;
		getline(fichero, basura);
		while (num != num_jugadores) {
			for (int i = 0; i < FIL; i++) {
				getline(fichero, basura);
			}
			fichero >> num;
			getline(fichero, basura);
		}
		if (num == num_jugadores) {
			ok = true;
			int i = 1;
			for (int fil = 0; fil < FIL; fil++) {
				getline(fichero, linea);
				for (int col = 0; col < COL; col++) {
					tablero[fil][col] = char2Casilla(linea[col]);
					if (tablero[fil][col].estado == TORTUGA) {
						tablero[fil][col].tortuga.num = i;
						i++;
					}
				}
			}
		}
	}
	return ok;
}

void laser(tTablero & tablero, tCoordenada coor, tDir dir) {
	bool enc = false;
	while (!enc && ((coor.x + incF[dir] >= 0 && coor.x + incF[dir] < FIL) && (coor.y + incC[dir] >= 0 && coor.y + incC[dir] < COL))) {
		if (tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado == HIELO) {
			enc = true;
			tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado = VACIA;
		}
		else if (tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado == VACIA) {
			coor.x += incF[dir];
			coor.y += incC[dir];
		}
		else {
			enc = true;
		}
	}
}

void avanza(tTablero & tablero, tCoordenada & coor, tDir & dir) {
	if (compMov(tablero, coor, dir)) {
		if (tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado == CAJA) {
			tablero[coor.x + 2 * incF[dir]][coor.y + 2 * incC[dir]].estado = tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado;
			tablero[coor.x + incF[dir]][coor.y + incC[dir]].estado = VACIA;
			tablero[coor.x + incF[dir]][coor.y + incC[dir]] = tablero[coor.x][coor.y];
			tablero[coor.x + incF[dir]][coor.y + incC[dir]].tortuga = tablero[coor.x][coor.y].tortuga;
			tablero[coor.x][coor.y].estado = VACIA;
		}
		else {
			tablero[coor.x + incF[dir]][coor.y + incC[dir]] = tablero[coor.x][coor.y];
			tablero[coor.x + incF[dir]][coor.y + incC[dir]].tortuga = tablero[coor.x][coor.y].tortuga;
			tablero[coor.x][coor.y].estado = VACIA;
		}
		coor.x += incF[dir];
		coor.y += incC[dir];
	}
}

void char2carta(tVCartas & cartas, int num) {
	string linea;
	int j=0;
	cin >> linea;
		while (j < num) {
			if (linea == "AVANZAR") {
				cartas[j] = AVANZAR;
			}
			else if (linea == "GIROIZQUIERDA") {
				cartas[j] = GIROIZQUIERDA;
			}
			else if (linea == "GIRODERECHA") {
				cartas[j] = GIRODERECHA;
			}
			else {
				cartas[j] = LASER;
			}
			j++;
			if (j < num) {
				cin >> linea;
			}
		}
}

tCasilla char2Casilla(char a) {

	tCasilla casilla;
	switch (a) {
	case '#': casilla.estado = MURO;
		break;
	case '@': casilla.estado = HIELO;
		break;
	case ' ': casilla.estado = VACIA;
		break;
	case '$': casilla.estado = JOYA;
		break;
	case 'C': casilla.estado = CAJA;
		break;
	default: casilla.estado = TORTUGA;
		switch (a) {
		case 'U': casilla.tortuga.dir = UP;
			break;
		case 'D': casilla.tortuga.dir = DOWN;
			break;
		case 'R': casilla.tortuga.dir = RIGHT;
			break;
		case 'L': casilla.tortuga.dir = LEFT;
		}
		break;
	}
	return casilla;
}

string casilla2char(tCasilla casilla) {
	string a;
	switch (casilla.estado)
	{
	case MURO:
		colorFondo(8);
		a = "||";
		break;
	case HIELO:
		colorFondo(3);
		a = "**";
		break;
	case VACIA:
		colorFondo(1);
		a = "  ";
		break;
	case JOYA:
		colorFondo(5);
		a = "00";
		break;
	case CAJA:
		colorFondo(6);
		a = "[]";
		break;
	case TORTUGA:
		switch (casilla.tortuga.num) {
		case 1: colorFondo(6);
			break;
		case 2: colorFondo(2);
			break;
		case 3: colorFondo(13);
			break;
		case 4: colorFondo(5);
			break;
		}
		switch (casilla.tortuga.dir) {
		case UP:
			a = "^^";
			break;
		case DOWN:
			a = "vv";
			break;
		case RIGHT:
			a = ">>";
			break;
		case LEFT:
			a = "<<";
			break;
		}
		break;
	}
	return a;
}

void realizarMovimiento(tTablero & tablero, tCoordenada coor, tVCartas cartas) {
	int i = 0, joyas1, joyas2;
	joyas1 = numeroJoyas(tablero);
	bool ok = true;
	while (ok) {
		switch (cartas[i])
		{
		case AVANZAR:
			avanza(tablero, coor, tablero[coor.x][coor.y].tortuga.dir);
			break;
		case GIRODERECHA:
			switch (tablero[coor.x][coor.y].tortuga.dir) {
			case UP: tablero[coor.x][coor.y].tortuga.dir = RIGHT;
				break;
			case RIGHT:tablero[coor.x][coor.y].tortuga.dir = DOWN;
				break;
			case DOWN:tablero[coor.x][coor.y].tortuga.dir = LEFT;
				break;
			case LEFT: tablero[coor.x][coor.y].tortuga.dir = UP;
				break;
			}
			break;
		case GIROIZQUIERDA:
			switch (tablero[coor.x][coor.y].tortuga.dir) {
			case UP: tablero[coor.x][coor.y].tortuga.dir = LEFT;
				break;
			case RIGHT:tablero[coor.x][coor.y].tortuga.dir = UP;
				break;
			case DOWN:tablero[coor.x][coor.y].tortuga.dir = RIGHT;
				break;
			case LEFT: tablero[coor.x][coor.y].tortuga.dir = DOWN;
				break;
			}
			break;
		case LASER:
			laser(tablero, coor, tablero[coor.x][coor.y].tortuga.dir);
			break;
		default:
			ok = false;
			break;
		}
		i++;
		joyas2 = numeroJoyas(tablero);
		if (joyas1 != joyas2) ok = false;
	}
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

tTecla leerTecla() {
	tTecla tecla;
	int dir;
	dir = _getch(); // dir: tipo int
	if (dir == 0xe0) {
		dir = _getch();
	}
	switch (dir) {
	case 13: tecla = SALIR;
		break;
	case 32: tecla = LASR;
		break;
	case 72: tecla = AVANZA;
		break;
	case 77: tecla = DERECHA;
		break;
	case 75: tecla = IZQUIERDA;
		break;
	default:
		tecla = NADA;
		break;

	}
	return tecla;
}

char carta2char(tCarta carta) {
	char a;
	switch (carta)
	{
	case AVANZAR: a = '^';
		break;
	case LASER: a = '~';
		break;
	case GIRODERECHA: a = '>';
		break;
	case GIROIZQUIERDA: a = '<';
		break;
	default:
		a = ' ';
		break;
	}
	return a;
}

tCarta tacla2Carta(tTecla tecla) {
	tCarta carta;
	switch (tecla)
	{
	case AVANZA: carta = AVANZAR ;
		break;
	case LASR: carta =  LASER;
		break;
	case DERECHA: carta = GIRODERECHA;
		break;
	case IZQUIERDA: carta =  GIROIZQUIERDA;
		break;
	default:
		carta = VACIO;
		break;
	}
	return carta;
}

int numeroJoyas(tTablero tablero) {
	int joyas = 0;
	for (int fil = 0; fil < FIL; fil++) {
		for (int col = 0; col < COL; col++) {
			if (tablero[fil][col].estado == JOYA) {
				joyas++;
			}
		}
	}
	return joyas;
}

tCoordenada coordenadaTortuga(tTablero tablero, int num) {
	tCoordenada coor;
	coor.x = 0;
	coor.y = 0;
	bool enc = false;
	int k = 0;
	for (int i = 0; i < FIL && !enc; ++i) {
		for (int j = 0; j < COL && !enc; ++j) {
			if (tablero[i][j].estado == TORTUGA) {
				k++;
				if (k == num) {
					enc = true;
					coor.x = i;
					coor.y = j;
				}
			}
		}
		return coor;
	}
}