#include <iostream>
using namespace std;

const unsigned int MAX_NINIOS = 20; // maximo numero de niños
                                    // el numero de sitios siempre
									// sera menor o igual que el
									// numero de niños

  // Representacion de la matriz de satisfacciones
typedef struct {
	int n_ninios;	// numero de niños.
    int n_sitios;	// numero de sitios
	int sat[MAX_NINIOS][MAX_NINIOS];  // la posicion i,j representa la satisfaccion
                                      // que siente el ninio i si se le asigna el sitio j											   
} tMatrizSatisfacciones;


/*
(1) En caso de utilizar una generalizacion, indicar sus parametros, y explicar para que
sirven cada uno de ellos

(2) Como son las soluciones parciales de este problema?

(3) Cuando una solucion parcial es viable?

(4) Cuando una solucion parcial es una solucion final al problema?

(5) Dada una solucion parcial, como se generan las siguientes soluciones
parciales viables?

(6) Analisis de casos
	(6.1) Caso(s) base

	(6.2) Caso(s) recursivos

(7) En caso de utilizar una generalizacion, explicar como se define el algoritmo final
a partir de la misma, por inmersion.

*/

int satisfaccion_maxima(const tMatrizSatisfacciones& sats, int h) {
	// A IMPLEMENTAR
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */
					
bool ejecuta_caso() {
	tMatrizSatisfacciones sats;
	cin >> sats.n_ninios;
	if (sats.n_ninios != -1) {
	   cin >> sats.n_sitios;
	   int h;
	   cin >> h;
	   for (int sitio=0; sitio < sats.n_sitios; sitio++) {
		   for (int ninio=0; ninio < sats.n_ninios; ninio++) {
			   cin >> sats.sat[ninio][sitio];
		   }
	   }
	   cout << satisfaccion_maxima(sats,h) << endl; 
	   return true;
	}
	else {
		return false; 
	}
}	


int main() {
	while(ejecuta_caso());
}