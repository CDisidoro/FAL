/*
NOMBRE Y APELLIDOS: Camilo Andres D'isidoro
*/
#include <iostream>
using namespace std;
/*
Nota: NO es necesario que especifiques el algoritmo, ni las
funciones auxiliares utilizadas. Pero, en caso de utilizar
una generalizacion, si debes describir sus parametros, 
su resultado, y el proposito de los mismos 

(1) SI UTILIZAS UNA GENERALIZACION, DETALLA AQUI SUS PARAMETROS,
    SU RESULTADO, Y EL PROPOSITO DE LOS MISMOS 
	int ini (Entrada) = Punto de inicio de busqueda
	int fin (Entrada) = Punto de fin de busqueda
	bool found (Salida) = Se ha encontrado un elemento ni fu ni fa
(2) DISEÑO (CASOS)
	Caso Base: Hay solo un elemento en el array
		if(ini + 1 == fin)
			return false
	Caso Recursivo:
		int medio = (ini + fin) / 2;
		if(a[medio] > a[0] && a[medio] < a[n - 1]){
			return true;
		}else{
			if(a[medio] == a[0]){
				return hay_nifunifa_aux(a, n, medio, fin);
			}else{
				return hay_nifunifa_aux(a, n, ini, medio);
			}
		}
		return false;
(3) JUSTIFICACION DE LA TERMINACION DEL ALGORITMO
	fin - ini, porque filtramos casos reduciendo fin o aumentando ini hasta llegar al caso base
(4) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE
	hay_nifunifa_aux(a, n, 0, n)
(5) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO
	T(n) = C0 (Caso base)
	T(n) = C1 + T(n/2) (Caso recursivo)
	a = 1
	b = 2
	k = 0
	b ^ k = 1
	a = b ^ k
	O(n ^ k log n) => O(1 log n) => O(log n)
*/

bool hay_nifunifa_aux(int a[], int n, int ini, int fin){
	if(ini + 1 == fin){
		return false;
	}else{
		int medio = (ini + fin) / 2;
		if(a[medio] > a[0] && a[medio] < a[n - 1]){
			return true;
		}else{
			if(a[medio] <= a[0]){
				return hay_nifunifa_aux(a, n, medio, fin);
			}else{
				return hay_nifunifa_aux(a, n, ini, medio);
			}
		}
		return false;
	}
}

bool hay_nifunifa(int a[], int n) {
	if(n > 0){
		return hay_nifunifa_aux(a, n, 0, n);
	}
	return false;
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
	  if (hay_nifunifa(a,n)) {
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
