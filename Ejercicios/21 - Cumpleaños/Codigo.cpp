#include <iostream>
using namespace std;

const unsigned int MAX_NINIOS = 20; // maximo numero de ninos
// el numero de sitios siempre
// sera menor o igual que el
// n�mero de ninos

// Representacion de la matriz de satisfacciones
typedef struct {
	int n_ninios;	// numero de ninos.
	int n_sitios;	// numero de sitios
	int sat[MAX_NINIOS][MAX_NINIOS];  // la posicion i,j representa la satisfaccion
	// que siente el ninio i si se le asigna el sitio j
} tMatrizSatisfacciones;

typedef struct {
	int puestosOcupados;
	int asignaciones[MAX_NINIOS];
	int sumaSatisfaccion;
	int numNinio;
} tDatos;

/*
(1) En caso de utilizar una generalizacion, indicar su parametros, y explicar para que
sirven cada uno de ellos

(2) Como son las soluciones parciales de este problema?

(3) Cuando una solucion parcial es viable?

(4) Cuando una solucion parcial es una solucion final al problema?

(5) Dada una solucion parcial, como se generan las siguientes soluciones
parciales viables?

(6) Analisis de casos
	(6.1) Caso(s) base

	(6.2) Caso(s) recursivos

(7) En caso de utilizar una generalizacion, explicar c�mo se define el algoritmo final
a partir de la misma, por inmersion.

*/
void solve(const tMatrizSatisfacciones& sats, int posHermano, const int limiteMalAsignados, tDatos datos, int& maxSatisfaccion, int malAsignados, bool estaHermano) {
	//Si hemos llegado al final de la lista de ninios o ya hemos ocupado todos los asientos llegamos al caso base
	if (datos.numNinio == sats.n_ninios || datos.puestosOcupados == sats.n_sitios) {
		//Para validar la solucion final comprobamos que este presente el hermano, y que la satisfaccion total de esta combinacion supere la maxima hallada hasta ahora
		if (estaHermano && datos.sumaSatisfaccion > maxSatisfaccion) {
			maxSatisfaccion = datos.sumaSatisfaccion;
		}
	} else {
		//Para el caso recursivo ejecutamos el bucle for mientras no lleguemos al final de la lista de ninios y que hayan puestos libres
		//No se pone que parta desde datos.numNinio porque limitaria demasiado la busqueda (Sentar al ninio X en el asiento Y haria que ignorasemos la afinidad de los ninios [0...X-1] para el asiento Y+1)
		for (int i = 0; i < sats.n_ninios; i++) {
			//Si la afinidad del ninio por ese puesto es positiva lo agrega a la solucion parcial
			if (datos.asignaciones[datos.puestosOcupados] < 0 && sats.sat[i][datos.puestosOcupados] > -1) {
				//Aplicamos marcaje:
				/*
					Si el ninio que estamos agregando es el hermano activamos el booleano de estaHermano
					Si la asignacion del ninio es mala incrementamos el contador de malAsignados
					Al array de asignaciones de puestos le asignaremos el ninio i
					A la suma de satisfaccion le agregaremos la satisfaccion del ninio por ese puesto
					Aumentamos el numero de ninio
					Aumentamos el numero de puestos ocupados
				*/
				if (i % sats.n_sitios == datos.puestosOcupados) {
					malAsignados++;
				}
				//Si no superamos el limite de mal asignados seguimos con el marcaje, en caso contrario ya no tendria sentido probar esta solucion
				if (malAsignados <= limiteMalAsignados) {
					if (i == posHermano) {
						estaHermano = true;
					}
					datos.asignaciones[datos.puestosOcupados] = i;
					datos.sumaSatisfaccion += sats.sat[i][datos.puestosOcupados];
					datos.numNinio++;
					datos.puestosOcupados++;
					solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano); //Se llama a la recursion
					//Deshacemos el marcaje (Probar a no invitar al ninio X sino al X+1)
					datos.puestosOcupados--;
					datos.numNinio--;
					datos.sumaSatisfaccion -= sats.sat[i][datos.puestosOcupados];
					datos.asignaciones[datos.puestosOcupados] = -1;
					if (i == posHermano) {
						estaHermano = false;
					}
				}
				if (i % sats.n_sitios == datos.puestosOcupados) {
					malAsignados--;
				}
			}
		}
		if (datos.puestosOcupados < sats.n_sitios) {
			datos.numNinio = sats.n_ninios;
			solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano);
		}
	}
}

int satisfaccion_maxima(const tMatrizSatisfacciones& sats, int h) {
	int maxSatisfaccion = 0;
	int malAsignados = 0;
	int limiteMalAsignados = sats.n_sitios / 3;
	bool estaHermano = false;
	tDatos datos;
	datos.puestosOcupados = 0;
	datos.sumaSatisfaccion = 0;
	datos.numNinio = 0;
	solve(sats, h, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano);
	return maxSatisfaccion;
}

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

bool ejecuta_caso() {
	tMatrizSatisfacciones sats;
	cin >> sats.n_ninios;
	if (sats.n_ninios != -1) {
		cin >> sats.n_sitios;
		int h;
		cin >> h;
		for (int sitio = 0; sitio < sats.n_sitios; sitio++) {
			for (int ninio = 0; ninio < sats.n_ninios; ninio++) {
				cin >> sats.sat[ninio][sitio];
			}
		}
		cout << satisfaccion_maxima(sats, h) << endl;
		return true;
	}
	else {
		return false;
	}
}


int main() {
	while (ejecuta_caso());
}