#include <iostream>
using namespace std;

const unsigned int MAX_NINIOS = 20; // maximo numero de ninos
// el numero de sitios siempre
// sera menor o igual que el
// numero de ninos

// Representacion de la matriz de satisfacciones
typedef struct {
	int n_ninios;	// numero de ninos.
	int n_sitios;	// numero de sitios
	int sat[MAX_NINIOS][MAX_NINIOS];  // la posicion sitio,j representa la satisfaccion
	// que siente el ninio sitio si se le asigna el sitio j
} tMatrizSatisfacciones;

typedef struct {
	int asignaciones[MAX_NINIOS];
	int sumaSatisfaccion;
} tDatos;

/*
(1) En caso de utilizar una generalizacion, indicar su parametros, y explicar para que
sirven cada uno de ellos
	int limiteMalAsignados (Entrada): Cantidad limite de ninos mal asignados para el problema
	tDatos datos (Entrada): Informacion sobre la solucion parcial
		asignaciones: Lista de asignaciones sitio - nino (asignaciones[X] = Y, en el asiento X esta el nino Y)
		sumaSatisfaccion: Suma de la satisfaccion de los ninos para esta solucion
	int maxSatisfaccion (Salida): Satisfaccion maxima encontrada hasta el momento
	int malAsignados (Entrada): Numero de ninos mal asignados
	bool estaHermano (Entrada): Indica si el hermano ha sido invitado para esta solucion
	int numNinio (Entrada): Numero de nino que estamos intentando sentar
	int puestosOcupados (Entrada): Numero de puestos que estan ocupados
(2) Como son las soluciones parciales de este problema?
	Una lista de asignaciones de ninos a unos asientos con una suma de satisfaccion
(3) Cuando una solucion parcial es viable?
	Cuando todos los ninos tienen una satisfaccion positiva por ese puesto y hay menos de m/3 ninos mal asignados (m siendo la cantidad de asientos disponibles)
(4) Cuando una solucion parcial es una solucion final al problema?
	Cuando hayamos asignado todos los asientos o intentado sentar a todos los ninos
(5) Dada una solucion parcial, como se generan las siguientes soluciones
parciales viables?
	Al nino X se le intentara sentar en cada uno de los asientos libres y con satisfaccion positiva disponibles
(6) Analisis de casos
	(6.1) Caso(s) base
		if(numNinio == sats.n_ninios || puestosOcupados == sats.n_sitios)
			if(estaHermano && datos.sumaSatisfaccion > maxSatisfaccion)
				maxSatisfaccion = datos.sumaSatisfaccion
	(6.2) Caso(s) recursivos
		for(int sitio = 0; sitio < sats.n_sitios; sitio++)
			if(datos.asignaciones[sitio] < 0 && sats.sat[numNinio][sitio] >= 0)
				if(numNinio % sats.n_sitios == sitio)
					malAsignados++
				if(malAsignados <= limiteMalAsignados)
					if(numNinio == posHermano)
						estaHermano = true
					datos.asignaciones[sitio] = numNinio
					datos.sumaSatisfaccion += sats.sat[numNinio][sitio]
					solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, numNinio + 1, puestosOcupados + 1)
					datos.asignaciones[sitio] = -1
					datos.sumaSatisfaccion -= sats.sat[numNinio][sitio]
					if(numNinio == posHermano)
						estaHermano = false
				if(numNinio % sats.n_sitios == sitio)
					malAsignados--
		solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, numNinio + 1, puestosOcupados)
(7) En caso de utilizar una generalizacion, explicar como se define el algoritmo final
a partir de la misma, por inmersion.
	tDatos datos
	int maxSatisfaccion = 0, malAsignados = 0, limiteMalAsignados = sats.n_sitios / 3
	bool estaHermano = false
	datos.sumaSatisfaccion = 0
	for (int i = 0; i < sats.n_sitios; i++)
		datos.asignaciones[i] = -1
	solve(sats, h, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, 0, 0)
	return maxSatisfaccion
*/
/*
	AVISO: Esta solucion da TIMELIMIT en el juez. Para solucionarlo, se tiene que implementar una poda donde, citando a Jose Luis Sierra,
	"Debes introducir una poda, manteniendo, para ello, la satisfacción restante que, como mucho, podrás conseguir"
*/
void solve(const tMatrizSatisfacciones& sats, int posHermano, const int limiteMalAsignados, tDatos datos, int& maxSatisfaccion, int& malAsignados, bool& estaHermano, int numNinio, int puestosOcupados) {
	if(numNinio == sats.n_ninios || puestosOcupados == sats.n_sitios){
		//Para validar la solucion final comprobamos que este presente el hermano, y que la satisfaccion total de esta combinacion supere la maxima hallada hasta ahora
		if (estaHermano && datos.sumaSatisfaccion > maxSatisfaccion) {
			maxSatisfaccion = datos.sumaSatisfaccion;
		}
	} else {
		//Para el caso recursivo ejecutamos el bucle for para recorrer la lista de sitios
		for (int sitio = 0; sitio < sats.n_sitios; sitio++) {
			//        Puesto libre                    Afinidad positiva
			if (datos.asignaciones[sitio] < 0 && sats.sat[numNinio][sitio] >= 0) {
				//Aplicamos marcaje:
				/*
					Si la asignacion del ninio es mala incrementamos el contador de malAsignados
					Si el ninio que estamos agregando es el hermano activamos el booleano de estaHermano
					Al array de asignaciones de puestos le asignaremos al puesto sitio el ninio numNinio
					A la suma de satisfaccion le agregaremos la satisfaccion del ninio por ese puesto
					Aumentamos el numero de ninio
					Aumentamos el numero de puestos ocupados
				*/
				if (numNinio % sats.n_sitios == sitio) {
					malAsignados++;
				}
				//Si no superamos el limite de mal asignados seguimos con el marcaje, en caso contrario ya no tendria sentido probar esta solucion
				if (malAsignados <= limiteMalAsignados) {
					if (numNinio == posHermano) {
						estaHermano = true;
					}
					datos.asignaciones[sitio] = numNinio;
					datos.sumaSatisfaccion += sats.sat[numNinio][sitio];
					solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, numNinio + 1, puestosOcupados + 1); //Se llama a la recursion
					//Deshacemos el marcaje
					datos.asignaciones[sitio] = -1;
					datos.sumaSatisfaccion -= sats.sat[numNinio][sitio];
					if (numNinio == posHermano) {
						estaHermano = false;
					}
				}

				if (numNinio % sats.n_sitios == sitio) {
					malAsignados--;
				}
			}
		}
		//Probamos a no invitar al ninio y pasamos al siguiente
		solve(sats, posHermano, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, numNinio + 1, puestosOcupados);
	}
}

int satisfaccion_maxima(const tMatrizSatisfacciones& sats, int h) {
	tDatos datos;
	int maxSatisfaccion = 0, malAsignados = 0, limiteMalAsignados = sats.n_sitios / 3;
	bool estaHermano = false;
	datos.sumaSatisfaccion = 0;
	for (int i = 0; i < sats.n_sitios; i++) {
		datos.asignaciones[i] = -1;
	}
	solve(sats, h, limiteMalAsignados, datos, maxSatisfaccion, malAsignados, estaHermano, 0, 0);
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