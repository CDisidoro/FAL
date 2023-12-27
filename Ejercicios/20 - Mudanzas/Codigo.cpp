#include <iostream>
using namespace std;
const int MAX_OBJS = 20;
// Lista con los objetos a portar 
typedef struct {
	int tamanios[MAX_OBJS];  // Array en cuyas primeras posiciones se guardan los tamaños de los objetos
	int n_objetos;           // Numero de objetos
} tObjetos;

typedef struct {
	int asignaciones[MAX_OBJS];
	int capacidadRestante;
	int numCaja;
} tDatos;
/*
(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos
	tDatos (Entrada):
		asignaciones (Entrada): Guarda una lista en la que indica a que caja va a ir el objeto i
		capacidadRestante (Entrada): Capacidad restante de la caja actual
		numCaja (Entrada): Numero de caja que estamos utilizando ahora
	objetoActual (Entrada): Indica que objeto estamos inspeccionando ahora, para saber si hemos llegado al final
	minCajas (Entrada/Salida): Guarda la cantidad minima de cajas a utilizar
(2) ¿Cómo son las soluciones parciales de este problema?
	Una lista de asignaciones de cajas a los objetos pendiente de completar, junto un numero de cajas en uso y la capacidad restante de esta
(3) ¿Cuándo una solución parcial es viable?
	De hecho cualquier solución parcial resultaría viable, porque si el objeto i cabe en la caja j, se introducirá en esta, y si no cabe, se agregará a una caja i+1
(4) ¿Cuándo una solución parcial es una solución final al problema?
	En cuanto se hayan asignado todos los objetos a una caja
(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?
	Se recorre la lista de objetos buscando los que están pendientes de asignar y se le asigna dicho objeto a una caja
(6) Análisis de casos
	(6.1) Caso(s) base
		if (objetoActual == objetos.n_objetos) {
			if (datos.numCaja < minCajas) {
				minCajas = datos.numCaja;
			}
		}
	(6.2) Caso(s) recursivos
		else if(minCajas > datos.numCaja){
		for (int objeto = 0; objeto < datos.numCaja; objeto++) {
			int capacidadNueva = datos.asignaciones[objeto] + objetos.tamanios[objetoActual];
			if (capacidadNueva <= capacidad_caja) {
				datos.asignaciones[objeto] += objetos.tamanios[objetoActual];
				solve(objetos, capacidad_caja, objetoActual + 1, datos, minCajas);
				datos.asignaciones[objeto] -= objetos.tamanios[objetoActual];
			}
		}
		datos.numCaja++;
		datos.asignaciones[datos.numCaja - 1] += objetos.tamanios[objetoActual];
		solve(objetos, capacidad_caja, objetoActual + 1, datos, minCajas);
		datos.asignaciones[datos.numCaja - 1] -= objetos.tamanios[objetoActual];
		datos.numCaja--;
	}
(7) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.
	int minCajas = objetos.n_objetos;
	tDatos datos;
	datos.capacidadRestante = capacidad_caja;
	datos.numCaja = 1;
	datos.objetoActual = 0;
	solve(objetos, capacidad_caja, datos, minCajas);
*/

void solve(const tObjetos& objetos, int capacidad_caja, int objetoActual, tDatos datos, int& minCajas) {
	if (objetoActual == objetos.n_objetos) {
		if (datos.numCaja < minCajas) {
			minCajas = datos.numCaja;
		}
	}else if(minCajas > datos.numCaja){
		for (int objeto = 0; objeto < datos.numCaja; objeto++) {
			int capacidadNueva = datos.asignaciones[objeto] + objetos.tamanios[objetoActual];
			if (capacidadNueva <= capacidad_caja) {
				datos.asignaciones[objeto] += objetos.tamanios[objetoActual];
				solve(objetos, capacidad_caja, objetoActual + 1, datos, minCajas);
				datos.asignaciones[objeto] -= objetos.tamanios[objetoActual];
			}
		}
		datos.numCaja++;
		datos.asignaciones[datos.numCaja - 1] += objetos.tamanios[objetoActual];
		solve(objetos, capacidad_caja, objetoActual + 1, datos, minCajas);
		datos.asignaciones[datos.numCaja - 1] -= objetos.tamanios[objetoActual];
		datos.numCaja--;
	}
}

int min_numero_de_cajas(const tObjetos& objetos, int capacidad_caja) {
	tDatos datos;
	int minCajas = objetos.n_objetos;
	datos.capacidadRestante = capacidad_caja;
	datos.numCaja = 0;
	for (int i = 0; i < objetos.n_objetos; i++) {
		datos.asignaciones[i] = 0;
	}
	solve(objetos, capacidad_caja, 0, datos, minCajas);
	return minCajas;
}

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

bool ejecuta_caso() {
	int capacidad;
	cin >> capacidad;
	if (capacidad != -1) {
		tObjetos objetos;
		cin >> objetos.n_objetos;
		for (int i = 0; i < objetos.n_objetos; i++) {
			cin >> objetos.tamanios[i];
		}
		cout << min_numero_de_cajas(objetos, capacidad) << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {
	while (ejecuta_caso());
}
