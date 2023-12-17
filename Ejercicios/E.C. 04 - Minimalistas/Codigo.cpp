/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:
Camilo Andres D'isidoro
Juan Israel Baroffi Gonzalez
Si alguno de los miembros del grupo no ha realizado
la practica, indicarlo aqui, junto con el motivo:
*/

#include <iostream>

using namespace std;

/*
(1) Como son las soluciones parciales viables de este problema?
	Un array de numeros para los que el minimo no se repite y la suma de los numeros es menor o igual que el umbral
(2) Cuando una solucion es final?
	Con que no supere el umbral y el minimo no se repita, ya cuenta como una solucion final, que luego puede extenderse hasta superar el umbral o repetir el minimo
(3) Dada una solucion viable, como se generan nuevas soluciones viables a partir de ella?
	Recorriendo la lista de numeros y añadir a la secuencia los numeros distintos del minimo
(4) Como se representaran las soluciones en este problema? Describe los distintos elementos
	de informacion que las componen, indicando si se representan como parametros de entrada,
	de entrada/salida (estado global), si se representan implicitamente...
	sumaNumeros (Entrada) = Suma de los numeros que componen la secuencia
	minimo (Entrada) = Numero minimo de la secuencia de numeros
	C (Entrada) = Lista de numeros a comprobar
	U (Entrada) = Umbral de la suma de numeros
	soluciones (Salida) = Cantidad de soluciones posibles
(5) Que marcadores utiliza el algoritmo? Describe claramente su proposito, los elementos
	de informacion que los componen, asi como si dichos elementos se representan como parametros
	de entrada, de entrada/salida (estado global)...
	sumaNumeros (Entrada) = Suma de los numeros que componen la secuencia. Al terminar de comprobar una secuencia se decrementa el valor de la suma para ver otras posibles soluciones
	minimo (Entrada) = Numero minimo de la secuencia. Si se encuentra un nuevo minimo se envia a las recursiones y al volver se retorna al valor minimo original
(6) Si el algoritmo utiliza generalizacion, indica como es la misma, describiendo claramente
	el proposito de cada parametro.
	sumaNumeros (Entrada) = Suma de los numeros que componen la secuencia
	minimo (Entrada) = Numero minimo de la secuencia de numeros
	soluciones (Salida) = Cantidad de soluciones posibles
(7) Analisis de casos: casos base, casos recursivos
	Caso Base:
		if(suma <= u)
			soluciones++
	Caso Recursivo:
		for(int i = 0; i < n; i++)
			if(c[i] < minimo)
				solve(c, n, u, sumaNumeros + c[i], c[i], soluciones)
			else
				if(minimo != c[i])
					solve(c, n, u, sumaNumeros + c[i], minimo, soluciones)
(8) Si el algoritmo utiliza una generalizacion, describe como se implementa el algoritmo
	en terminos de la misma (inmersion)
		soluciones = 0
		for(int i = 0; i < n; i++)
			solve(c, n, u, c[i], c[i], soluciones)
*/

void solve(int c[], int n, int u, int sumaNumeros, int minimo, int& soluciones) {
	if (sumaNumeros <= u) {
		soluciones++;
		for (int i = 0; i < n; i++) {
			if (c[i] < minimo) {
				solve(c, n, u, sumaNumeros + c[i], c[i], soluciones);
			}
			else {
				if (minimo != c[i]) {
					solve(c, n, u, sumaNumeros + c[i], minimo, soluciones);
				}
			}
		}
	}
}

// En los 'n' (n>0) primeros elementos de 'c' se encuentran almacenados
// los elementos del conjunto 'C'.
// En 'u' esta el umbral 'U' (U >= 0). 
int num_minimalistas(int c[], int n, int u) {
	int soluciones = 0;
	for (int i = 0; i < n; i++) {
		solve(c, n, u, c[i], c[i], soluciones);
	}
	return soluciones;
}

/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/

const int MAX_VALS = 100;

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		int v[MAX_VALS];
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		int u;
		cin >> u;
		cout << num_minimalistas(v, n, u) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}