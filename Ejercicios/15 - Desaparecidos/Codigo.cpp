
#include <iostream>
using namespace std;


const int TMAX = 300000;  // No habrá vectores de más de 300000 elementos


/*
(1) En caso de utilizar una generalizacion, 
determinación de los parámetros de la generalización.
Determina los parámetros de la generalización. Para cada parámetro
indica: (i) su tipo; (ii) su nombre; (iii) si es un parámetro
de entrada, de salida, o de entrada / salida; (iv) su propósito,
descrito de manera clara y concisa.
	Entradas:	int a[] -> Vector de numeros
				int ini -> Punto de inicio de busqueda
				int fin -> Punto de finalizacion de busqueda
	Salidas:	bool encontrado -> Determina si hemos encontrado el maximo
				int max -> Valor maximo que falta en el vector
(2) Análisis de casos:
(2.1) Casos base
	(fin - ini) == 2
		if(v[fin] - v[ini] > 1)
			return {true, v[fin] - 1}
		else
			return {false, 0}
(2.2) Casos recursivos
	(fin - ini) > 3
		medio = (fin + ini) / 2
		tDer = num_perdido_aux(v, medio + 1, fin)
		if(tDer.encontrado)
			return tDer.max
		else
			return num_perdido_aux(v, ini, medio - 1).max
(3) En caso de utilizar una generalizacion, definición por inmersión 
del algoritmo. Describe de manera clara y concisa cómo se lleva a 
cabo el algoritmo, en qué punto o puntos se invoca a la generalización,
con qué parámetros reales, y cómo se genera el resultado
a partir de los devueltos por la generalización.
	num_perdido_aux(v, 0, n - 1)
	El algoritmo empieza obteniendo el valor central, y operando desde la derecha
	donde, al ser un array ordenado, hay más posibilidades de encontrar el perdido maximo
	y si encuentra el maximo en el segmento derecho lo retorna y termina el algoritmo
	Si no lo encuentra entonces debe estar el perdido en el segmento izquierdo, y lo busca ahi y lo retorna
(4)Determina justificadamente la complejidad del algoritmo
(4.1) Determinación de las ecuaciones de recurrencia para la generalización
	T(n) = C0 (Casos Base)
	T(n) = C1 + 2T(n/2) (Caso Recursivo en el peor caso, pues el peor es que el perdido maximo este en el inicio del array, por lo que revisa el array completo)
(4.2) Resolución utilizando los patrones vistos en clase
	Por division
		a = 2 (2 Subproblemas)
		b = 2 (Dividimos el tamaño del problema en 2)
		k = 0
		b ^ k = 1
(4.3) Determinación justificada de la complejidad del algoritmo final.
	a > b^k => 2 > 1
	O(n^log_b a) => O(n^log_2 2) => O(n)
*/

typedef struct{
	bool encontrado;
	int max;
}tSol;

tSol num_perdido_aux(int a[], int ini, int fin){
	int medio;
	//Casos Base
	if((fin - ini) == 1){
		if(a[fin] - a[ini] > 1){
			return {true, a[fin] - 1};
		}else{
			return {false, 0};
		}
	}else{//Caso Recursivo
		medio = (fin + ini) / 2;
		tSol tDer = num_perdido_aux(a, medio, fin);
		if(tDer.encontrado){
			return {true, tDer.max};
		}else{
			return num_perdido_aux(a, ini, medio);
		}
	}
}

int num_perdido(int a[], int n) {
	return num_perdido_aux(a, 0, n - 1).max;
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

bool procesa_caso() {
	static int a[TMAX];
	int n;
	cin >> n;
	if (n == -1) {
		return false;
	}
	else {
   	   for (int i=0; i < n; i++) {
         cin >> a[i];		
	   }
	   cout << num_perdido(a,n) << endl;
	   return true;
	}
}


int main() {
    while (procesa_caso());
}