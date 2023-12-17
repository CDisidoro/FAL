/*
NOMBRE Y APELLIDOS: Camilo Andres D'isidoro
*/
#include <iostream>
using namespace std;
/*
PRECONDICION DE LA FUNCION:
	P = { 0 <= n <= tam(a) ^ c > 0 ^ ParaTodo i: 0 <= i < n: v[i] > 0 }
*/
bool /* resul */ hay_c_tramo(int a[], int n, int c);
/*
POSTCONDICION DE LA FUNCION:
---Escribe aquí la poscondición de la función. Para refirte
---al valor devuelto por la función, utiliza la pseudo-variable
---'resul'
(1) Definiciones auxiliares (si procede):
(2) Postcondición
	Q = { resul = Existe ini, fin: 0 <= ini <= fin < n: (Sum x: ini <= x <= fin: v[x]) = c }
*/
/* DISEÑO DEL ALGORITMO:
	PASO 1. Variables adicionales (aparte de los parámetros y el resultado)
		int suma, ini, fin;
		bool sumaMayor;
	PASO 2. Invariante
	   (2.1) Definiciones auxiliares (si procede)
	   (2.2) Invariante
			resul = Existe ini, fin: 0 <= ini <= fin <= n: (Sum x: ini <= x <= fin : v[x]) = c
	PASO 3. Código de inicialización, justificando que, tras
	        dicho código, se cumple el invariante
		int suma = 0, ini = 0, fin = 0;
		bool resul = false, sumaMayor = false;
	PASO 4. Condición del bucle, código tras el bucle (si procede),
	        y justificación de que, una vez finalizado el algoritmo,
			se cumple la postcondición
		while(!resul && fin < n){
			...
		}
		return resul;
    PASO 5. Diseño del cuerpo del bucle, justificando que dicho código
	        preserva el invariante
		if(a[fin] > c){
			suma = 0;
			ini = fin + 1;
		}else if(a[fin] == c){
			resul = true;
		}else{
			suma += a[fin];
			if(suma > c){
				sumaMayor = true;
				while(ini < fin && sumaMayor){
					if(suma - a[ini] > c){
						suma -= a[ini];
					}else if(suma - a[ini] == c){
						resul = true;
						sumaMayor = false;
					}else{
						suma -= a[ini];
						sumaMayor = false;
					}
					ini++;
				}
			}
			if(suma == c){
				resul = true;
			}
		}
		fin++;
	PASO 6: Expresión de cota y justificación de que el algoritmo siempre 
	        termina
		2n - (fin + ini): Porque fin + ini siempre va a incrementar hasta llegar a un suelo
	PASO 7: Determinación justificada de la complejidad del algoritmo
		O(n) porque hacemos tantas iteraciones del bucle como elementos del array
*/
bool /* resul */ hay_c_tramo(int a[], int n, int c){
	bool resul = false, sumaMayor = false;
	int suma = 0, ini = 0, fin = 0;
	while(!resul && fin < n){
		if(a[fin] > c){
			suma = 0;
			ini = fin + 1;
		}else if(a[fin] == c){
			resul = true;
		}else{
			suma += a[fin];
			if(suma > c){
				sumaMayor = true;
				while(ini < fin && sumaMayor){
					if(suma - a[ini] > c){
						suma -= a[ini];
					}else if(suma - a[ini] == c){
						resul = true;
						sumaMayor = false;
					}else{
						suma -= a[ini];
						sumaMayor = false;
					}
					ini++;
				}
			}
			if(suma == c){
				resul = true;
			}
		}
		fin++;
	}
	return resul;
}	

/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/


const static int MAX_ELEMS=1000000;
bool ejecuta_caso() {
  	static int a[MAX_ELEMS];
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
      for (int i=0; i < n; i++) {
		  cin >> a[i];
	  }
	  int c;
	  cin >> c;
	  if (hay_c_tramo(a,n,c)) {
		  cout << "SI" << endl;
	  }
	  else {
	      cout << "NO" << endl;
	  }	  
      return true;	  
	}
}

int main() {
	while(ejecuta_caso());
}
