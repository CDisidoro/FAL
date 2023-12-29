/*
NOMBRE Y APELLIDOS: Camilo Andres D'isidoro
IMPORTANTE: Si no se añade el nombre y apellidos,
el ejercicio no se corregirá (puntuará como 0).
*/
#include <iostream>

using namespace std;


const int MAX_PROCESOS = 100;

// Tipo para codificar los datos de entrada
// al problema
typedef struct {
	int t_procesamiento;  // Tiempo de procesamiento 'T' de los procesadores.
	// Cada procesador permite utizar, como máximo,
	// 'T' unidades de tiempo.
	int t_procesos[MAX_PROCESOS];  // Unidades de tiempo requeridas por cada proceso. 
	int b_procesos[MAX_PROCESOS];  // Beneficio reportado por cada proceso.
	int n;                         // Número de procesos 'N' (n <= MAX_PROCESOS).
} tEntrada;

/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del diseño del algoritmo. No
se tendrá en cuenta la codificación del algoritmo, a menos que
esté acompañada del diseño sistemático del mismo.
*/

/*
(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos
	tiempoDisponibleP1 (Entrada): Tiempo de ejecucion disponible para el procesador P1
	tiempoDisponibleP2 (Entrada): Tiempo de ejecucion disponible para el procesador P2
	sumBeneficios (Entrada): Suma de beneficio de ejecucion de la asignacion actual
	nProceso (Entrada): Numero de proceso que se va a comprobar
	mejorSuma (Entrada/Salida): Guarda la maxima suma de beneficio del problema
(2) ¿Cómo son las soluciones parciales de este problema?
	Una asignacion de tareas a procesadores con una suma de beneficios, sin haber llegado a recorrer la lista completa
(3) ¿Cuándo una solución parcial es viable?
	Siempre que uno de los procesadores tenga tiempo de ejecucion disponible para hacerse cargo de la tarea sera una solucion viable
(4) ¿Cuándo una solución parcial es una solución final al problema?
	Cuando se haya llegado al final de la lista
(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?
	Para los procesos restantes va probando si el proceso p[x] puede ser abordado por el procesador 1. Si puede abordarlo se recurre por esa rama y al terminar
	deshace el marcaje y repite el proceso para el procesador 2, siempre que pueda hacerse cargo de la tarea
(6) Si estás utilizando algún criterio de poda adicional, explica detalladamente
	el criterio utilizado
(7) Análisis de casos
	(7.1) Caso(s) base
		if (nProceso == entrada.n) {
			if (asigActual.sumBeneficios > mejorSuma) {
				mejorSuma = asigActual.sumBeneficios;
			}
		}
	(7.2) Caso(s) recursivos
		else {
		for (int i = nProceso; i < entrada.n; i++) {
			if (asigActual.tiempoDisponibleP1 - entrada.t_procesos[i] >= 0) {
				asigActual.tiempoDisponibleP1 -= entrada.t_procesos[i];
				asigActual.sumBeneficios += entrada.b_procesos[i];
				solve(entrada, asigActual, i + 1, mejorSuma);
				asigActual.sumBeneficios -= entrada.b_procesos[i];
				asigActual.tiempoDisponibleP1 += entrada.t_procesos[i];
			}
			if (asigActual.tiempoDisponibleP2 - entrada.t_procesos[i] >= 0) {
				asigActual.tiempoDisponibleP2 -= entrada.t_procesos[i];
				asigActual.sumBeneficios += entrada.b_procesos[i];
				solve(entrada, asigActual, i + 1, mejorSuma);
				asigActual.sumBeneficios -= entrada.b_procesos[i];
				asigActual.tiempoDisponibleP2 += entrada.t_procesos[i];
			}
		}
		solve(entrada, asigActual, entrada.n, mejorSuma);
(8) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.
	tAsignacion asigActual;
	montaAsignacion(entrada, asigActual);
	int mejorSuma = 0;
	solve(entrada, asigActual, 0, mejorSuma);
*/

typedef struct {
	int tiempoDisponibleP1;
	int tiempoDisponibleP2;
	int sumBeneficios;
} tAsignacion;

void montaAsignacion(const tEntrada& entrada, tAsignacion& asig) {
	asig.tiempoDisponibleP1 = entrada.t_procesamiento;
	asig.tiempoDisponibleP2 = entrada.t_procesamiento;
	asig.sumBeneficios = 0;
}

void solve(const tEntrada& entrada, tAsignacion& asigActual, int nProceso, int& mejorSuma) {
	if (nProceso == entrada.n) {
		if (asigActual.sumBeneficios > mejorSuma) {
			mejorSuma = asigActual.sumBeneficios;
		}
	} else {
		for (int i = nProceso; i < entrada.n; i++) {
			if (asigActual.tiempoDisponibleP1 - entrada.t_procesos[i] >= 0) {
				asigActual.tiempoDisponibleP1 -= entrada.t_procesos[i];
				asigActual.sumBeneficios += entrada.b_procesos[i];
				solve(entrada, asigActual, i + 1, mejorSuma);
				asigActual.sumBeneficios -= entrada.b_procesos[i];
				asigActual.tiempoDisponibleP1 += entrada.t_procesos[i];
			}
			if (asigActual.tiempoDisponibleP2 - entrada.t_procesos[i] >= 0) {
				asigActual.tiempoDisponibleP2 -= entrada.t_procesos[i];
				asigActual.sumBeneficios += entrada.b_procesos[i];
				solve(entrada, asigActual, i + 1, mejorSuma);
				asigActual.sumBeneficios -= entrada.b_procesos[i];
				asigActual.tiempoDisponibleP2 += entrada.t_procesos[i];
			}
		}
		solve(entrada, asigActual, entrada.n, mejorSuma);
	}
}

int max_beneficio(const tEntrada& entrada) {
	tAsignacion asigActual;
	montaAsignacion(entrada, asigActual);
	int mejorSuma = 0;
	solve(entrada, asigActual, 0, mejorSuma);
	return mejorSuma;
}

/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el código que sigue no se corregirán (puntuarán 0).
bool ejecuta_caso() {
	int t_procesamiento;
	int n_procesos;
	cin >> t_procesamiento >> n_procesos;
	if (t_procesamiento == 0 && n_procesos == 0) {
		return false;
	}
	else {
		tEntrada entrada;
		entrada.n = n_procesos;
		entrada.t_procesamiento = t_procesamiento;
		for (int p = 0; p < n_procesos; p++) {
			cin >> entrada.t_procesos[p];
		}
		for (int p = 0; p < n_procesos; p++) {
			cin >> entrada.b_procesos[p];
		}
		cout << max_beneficio(entrada) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}
