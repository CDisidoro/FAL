/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:
	CAMILO ANDRES D'ISIDORO
	JUAN ISRAEL BAROFFI GONZALEZ
Si alguno de los miembros del grupo no ha realizado
la practica, indicarlo aqui, junto con el motivo:
*/
#include <iostream>
using namespace std;
/*
(1) GENERALIZACION (EN CASO DE QUE PROCEDA): Entradas y salidas
	Entradas:	cMin (Combustible minimo del espacio de soluciones)
				cMax (Combustible maximo del espacio de soluciones)
				rep  (Repostajes disponibles)
	Salidas:	min_combustible (Combustible minimo para el trayecto)
(2) DISEÑO:
	Primero acotamos el valor minimo y maximo para conseguir solucionar el problema.
	Con esos valores, comprobamos si el valor del medio del intervalo (cMin, cMax) puede completar el problema
	Si lo consigue, revisamos el problema para medio - 1, y si lo logra comprobaremos el intervalo (cMin, medio - 1) por
	la solucion. Si no lo consigue para medio - 1, la respuesta es medio.
	En caso de que no se pueda completar para medio, buscaremos la respuesta en el intervalo (medio + 1, cMax)
	Para comprobar si un valor de combustible soluciona el problema, recorremos el problema linealmente restando el combustible
	por cada elemento, y si se puede repostar, reiniciara el combustibleRestante al valor inicial y restara el elemento donde se 
	haya quedado sin combustible suficiente, y continuara hasta llegar al final, o quedarse sin combustible y repostajes
(3) TERMINACION:
	cMax - cMin, porque llegara un punto en la recursion que cMax = cMin, lo que haria que la cota sea cero
(4) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE:
	acotar(etapas, n, min, max, repostajes_permitidos)
	min_capacidad_aux(etapas, n, min, max, repostajes_permitidos)
(5) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO:
	T(1, u) = C0 (Base)
	T(n, u) = w(u) + T(n/2) (Caso Recursivo)
		w(n) = O(n) => w(n) comprueba si la cantidad de combustible es factible para solucionar el problema
	La complejidad, por lo tanto es O(u log n)
*/

bool comprueba_combustible(int etapas[], int n, int combustible, int rep) {
	int i = 0, combustibleRestante = combustible;
	while (i < n && combustibleRestante >= 0 && rep >= 0) {
		combustibleRestante -= etapas[i];
		if (combustibleRestante < 0 && rep > 0) {
			rep--;
			combustibleRestante = combustible - etapas[i];
		}
		i++;
	}
	return i == n && combustibleRestante >= 0;
}

void acotar(int etapas[], int n, int& min, int& max, int rep) {
	min = 0;
	max = 2;
	while (!comprueba_combustible(etapas, n, max, rep)) {
		min = max;
		max *= 2;
	}
}

int min_capacidad_aux(int etapas[], int n, int cMin, int cMax, int rep) {
	int medio = (cMin + cMax) / 2;
	if (comprueba_combustible(etapas, n, medio, rep)) { //Lo logra con el valor medio, probamos para la mitad inferior
		if (!comprueba_combustible(etapas, n, medio - 1, rep)) { //Si no lo logra con el medio - 1, el medio es el minimo
			return medio;
		}
		else { //Si lo logra con medio - 1, revisa el extremo inferior (combustibleMinimo, medio - 1)
			return min_capacidad_aux(etapas, n, cMin, medio - 1, rep);
		}
	}
	else { //Si no lo consigue con el medio buscamos en el extremo superior (medio + 1, combustibleMaximo)
		return min_capacidad_aux(etapas, n, medio + 1, cMax, rep);
	}
}


int min_capacidad(int etapas[], int n, int repostajes_permitidos) {
	int min, max;
	acotar(etapas, n, min, max, repostajes_permitidos);
	return min_capacidad_aux(etapas, n, min, max, repostajes_permitidos);
}


const int MAX_ETAPAS = 100000;


bool ejecuta_caso() {
	static int v[MAX_ETAPAS];
	int n, c;
	cin >> n;
	if (n == -1) return false;
	else {
		cin >> c;
		for (int i = 0; i < n; ++i)
			cin >> v[i];
		cout << min_capacidad(v, n, c) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}
