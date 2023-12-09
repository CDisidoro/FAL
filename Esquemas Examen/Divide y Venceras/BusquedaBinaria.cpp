/*
NOMBRE Y APELLIDOS: CAMILO ANDRES D'ISIDORO
IMPORTANTE: Si no se añade el nombre y apellidos,
el ejercicio no se corregira (puntuara como 0).
*/

#include <iostream>
using namespace std;


/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del diseño del algoritmo. No 
se tendra en cuenta la codificacion del algoritmo, a menos que
este acompañada del diseño sistematico del mismo.
*/
/*
(1) En caso de utilizar una generalizacion, 
determinacion de los parametros de la generalizacion.
Determina los parametros de la generalizacion. Para cada parametro
indica: (i) su tipo; (ii) su nombre; (iii) si es un parametro
de entrada, de salida, o de entrada / salida; (iv) su proposito,
descrito de manera clara y concisa.
	Entradas:	int a[] -> Vector de datos
				int b[] -> Vector de datos con intruso
				int ini -> Inicio de busqueda
				int fin -> Fin de busqueda
	Salidas:	int resul -> Numero intruso
(2) Analisis de casos:
(2.1) Casos base
	(fin - ini) = 0
		if(a[fin] != b[fin])
			return {true, b[fin]}
		else
			return {true, b[fin + 1]}
(2.2) Casos recursivos
	(fin - ini) != 0
		medio = (fin + ini) / 2
		if(a[medio] != b[medio])
			if(a[medio-1] == b[medio-1])
				return {true, b[medio]}
			else
				return intruso_aux(a, b, ini, medio)
		else
			return intruso_aux(a, b, medio, fin, n)
(3) En caso de utilizar una generalizacion, definicion por inmersion 
del algoritmo. Describe de manera clara y concisa como se lleva a 
cabo el algoritmo, en que punto o puntos se invoca a la generalizacion,
con que parametros reales, y como se genera el resultado
a partir de los devueltos por la generalizacion.
	intruso_aux(a, 0, n - 1)
	Empieza el algoritmo evaluando si el elemento del medio esta alineado.
	De estarlo, podemos intuir que el bloque izquierdo lo está tambien y hay que
	buscar en el bloque derecho y retornar el intruso.
	En caso contrario, revisamos si el elemento a su izquierda esta alineado.
	De estarlo, entonces el intruso esta en el centro
	Sino, el intruso esta en el bloque izquierdo y lo buscamos
(4)Determina justificadamente la complejidad del algoritmo
(4.1) Determinacion de las ecuaciones de recurrencia para la generalizacion
	T(n) = C0 (Caso Base)
	T(n) = C1 + T(n/2) (Pues en el peor caso seguimos buscando en una sola de las mitades)
(4.2) Resolucion utilizando los patrones vistos en clase
	Por division
	a = 1 (Dividimos en un subproblema)
	b = 2 (Dividimos el problema principal en 2)
	k = 0
	b ^ k = 1
(4.3) Determinacion justificada de la complejidad del algoritmo final.
	a = b^k => 1 = 1
	O(n^k log n) => O(n^0 log n) => o(log n)
*/

int intruso_aux(int a[], int b[], int ini, int fin){
	//Caso Base
	if((fin - ini) == 0){
		if(a[fin] != b[fin]){
			return b[fin];
		}else{
			return b[fin+1];
		}
	}else{ //Caso Recursivo
		int medio = (fin + ini) / 2;
		if(a[medio] != b[medio]){
			if(a[medio-1] == b[medio-1]){
				return b[medio];
			}else{
				return intruso_aux(a, b, ini, medio);
			}
		}else{
			return intruso_aux(a, b, medio + 1, fin);
		}
	}
}

// El vector 'a' tiene 'n' elmenentos. El vector 'b' n+1
int intruso(int a[], int n, int b[]) {
   return intruso_aux(a, b, 0, n - 1);
}

/*
En este tipo de ejercicios dividimos el problema en torno al array que se nos proporciona.
Por lo que, a diferencia de un problema de espacio de soluciones, pasamos directamente a la generalizacion.
En esta, debemos buscar primero el valor central y comprobar la condicion que se nos pide e irnos moviendo por la mitad izquierda o 
derecha según lo que proceda.

Para este ejercicio concreto se nos pasan dos arrays A y B, donde B es igual que A pero con un elemento extra llamado 'intruso', y la idea 
es buscar el intruso.
Para eso, buscamos el elemento central de A y lo comparamos con el central de B. Si son iguales, quiere decir
que el intruso está en la mitad derecha (Pues no hay desalineamiento hasta despues del elemento central).
En caso de ser distintos comprobara si los arrays estan alineados para el elemento inmediatamente anterior, y de estarlo, entonces 
el intruso está en el medio en B. En caso de ser distintos, entonces nuestro intruso está en la mitad inferior.

Dado que para este tipo de ejercicios no hay que acotar espacios de soluciones ni comprobar una solución recorriendo el array completo,
el cálculo de la complejidad sigue las pautas habituales de los problemas recursivos
*/

/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el codigo que sigue no se corregiran (puntuaran 0).

const int NMAX = 10000; // El vector 'a' no tendra mas de 10000 de elementos

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) {
		return false;
	}
	else {
		int a[NMAX];
		int b[NMAX + 1];
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for (int i = 0; i <= n; i++) {
			cin >> b[i];
		}
		cout << intruso(a, n, b) << endl;
        return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}