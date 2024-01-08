/*
NOMBRE Y APELLIDOS: Camilo Andres D'isidoro
Nº USUARIO DOMJUDGE: FAL034
*/
#include <iostream>
using namespace std;
const int MAX_PERSONAS = 20;
const int MAX_VEHICULOS = 10;
// Datos de entrada
typedef struct {
	bool ha_bebido[MAX_PERSONAS];   // ha_bebido[i]: La persona i ha bebido
	int capacidad[MAX_VEHICULOS];   // capacidad[v]: Nº de personas que caben en el vehículo v 
	int n_personas;                 // Nº total de personas en el clan
	int n_vehiculos;                // Nº total de vehículos
} tDatos;
/*
(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos
	posVehiculo (Entrada): Numero de vehiculo en el que estamos alojando personas
	posPersona (Entrada): Posicion de la siguiente persona a asignar y controlar que llegamos al final de la lista de personas
	sobrios[] (Entrada): Cantidad de sobrios en el vehiculo X
	ebrios[] (Entrada): Cantidad de ebrios en el vehiculo X
	soluciones (Salida): Cantidad de soluciones posibles
(2) ¿Cómo son las soluciones parciales de este problema?
	Una lista de asignaciones de personas a vehiculos donde no hemos terminado de asignar a todas las personas y vehiculos
(3) ¿Cuándo una solución parcial es viable?
	Cuando al asignar una persona nueva al vehiculo se cumple que:
		- La cantidad de ebrios no supera la mitad de capacidad del vehiculo
(4) ¿Cuándo una solución parcial es una solución final al problema?
	Cuando todos los vehiculos tienen pasajeros, entre ellos una persona sobria, y la cantidad de ebrios no supera la mitad de capacidad del vehiculo,
	asi como todas las personas van en vehiculos
(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?
	Si hay capacidad para alojar un pasajero mas en el vehiculo, recorrera la lista de personas en busca de una no asignada para añadirla al vehiculo (Validando el limite de ebrios si esta ebrio).
	Y también se plantea no alojar el pasajero en el vehiculo X sino que lo movemos al X+1, haya espacio o no en el vehiculo X
(6) Análisis de casos
	(6.1) Caso(s) base
		if (posPersona == datos.n_personas) {
			if (esViable(datos, solucion)) {
				soluciones++;
			}
		}
	(6.2) Caso(s) recursivos
		} else {
			for (int posVehiculo = 0; posVehiculo < datos.n_vehiculos; posVehiculo++) { //Recorremos entera la lista de vehiculos
				int puestosOcupados = solucion.sobrios[posVehiculo] + solucion.ebrios[posVehiculo];
				if (puestosOcupados < datos.capacidad[posVehiculo]) { //Si hay plazas suficientes en el vehiculo se prueba alojar gente en este vehiculo
					if (datos.ha_bebido[posPersona] && solucion.ebrios[posVehiculo] + 1 <= (datos.capacidad[posVehiculo] / 2)) { //Si ha bebido y al asignarlo no se supera el limite de ebrios
						solucion.ebrios[posVehiculo]++;
						posPersona++;
						solve(datos, solucion, posPersona, soluciones); //Recursion con la persona X+1
						posPersona--;
						solucion.ebrios[posVehiculo]--;
					}
					else if (!datos.ha_bebido[posPersona]) { //Si la persona no ha bebido
						solucion.sobrios[posVehiculo]++;
						posPersona++;
						solve(datos, solucion, posPersona, soluciones); //Recursion con la persona X+1
						posPersona--;
						solucion.sobrios[posVehiculo]--;
					}
				}
			}
		}
(7) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.
	int soluciones = 0;
	tSol solucion;
	for (int i = 0; i < datos.n_vehiculos; i++) {
		solucion.ebrios[i] = 0;
		solucion.sobrios[i] = 0;
	}
	solve(datos, solucion, 0, 0, soluciones);
*/
typedef struct {
	int sobrios[MAX_VEHICULOS];
	int ebrios[MAX_VEHICULOS];
} tSol;

bool esViable(const tDatos& datos, const tSol& solucion) {
	bool viable = true;
	for (int vehiculo = 0; vehiculo < datos.n_vehiculos && viable; vehiculo++) {
		//     No hay al menos un sobrio                           o el coche esta vacio
		if (solucion.sobrios[vehiculo] <= 0 || (solucion.ebrios[vehiculo] + solucion.sobrios[vehiculo]) <= 0) {
			viable = false;
		}
	}
	return viable;
}

void solve(const tDatos& datos, tSol solucion, int& posPersona, int& soluciones) {
	if (posPersona == datos.n_personas) { //Si llegamos al final de la lista de personas
		if (esViable(datos, solucion)) {
			soluciones++;
		}
	} else {
		for (int posVehiculo = 0; posVehiculo < datos.n_vehiculos; posVehiculo++) { //Recorremos entera la lista de vehiculos
			int puestosOcupados = solucion.sobrios[posVehiculo] + solucion.ebrios[posVehiculo];
			if (puestosOcupados < datos.capacidad[posVehiculo]) { //Si hay plazas suficientes en el vehiculo se prueba alojar gente en este vehiculo
				if (datos.ha_bebido[posPersona] && solucion.ebrios[posVehiculo] + 1 <= (datos.capacidad[posVehiculo] / 2)) { //Si ha bebido y al asignarlo no se supera el limite de ebrios
					solucion.ebrios[posVehiculo]++;
					posPersona++;
					solve(datos, solucion, posPersona, soluciones); //Recursion con la persona X+1
					posPersona--;
					solucion.ebrios[posVehiculo]--;
				}
				else if (!datos.ha_bebido[posPersona]) { //Si la persona no ha bebido
					solucion.sobrios[posVehiculo]++;
					posPersona++;
					solve(datos, solucion, posPersona, soluciones); //Recursion con la persona X+1
					posPersona--;
					solucion.sobrios[posVehiculo]--;
				}
			}
		}
	}
}

int num_asignaciones(const tDatos& datos) {
	int soluciones = 0;
	int posPersona = 0;
	tSol solucion;
	for (int i = 0; i < datos.n_vehiculos; i++) {
		solucion.ebrios[i] = 0;
		solucion.sobrios[i] = 0;
	}
	solve(datos, solucion, posPersona, soluciones);
	return soluciones;
}

bool ejecuta() {
	tDatos datos;
	cin >> datos.n_vehiculos;
	if (datos.n_vehiculos == -1) return false;
	cin >> datos.n_personas;
	for (int v = 0; v < datos.n_vehiculos; v++) {
		int bebe;
		cin >> datos.capacidad[v];
	}
	for (int p = 0; p < datos.n_personas; p++) {
		int bebe;
		cin >> bebe;
		if (bebe == 0) {
			datos.ha_bebido[p] = false;
		}
		else {
			datos.ha_bebido[p] = true;
		}
	}
	cout << num_asignaciones(datos) << endl;
	return true;

}

int main() {
	while (ejecuta());
}