#include <iostream>
using namespace std;
const int TMAX = 1000000;  // No habra vectores de mas de un millon de elementos
/*
PRECONDICION DE LA FUNCION: 
  ---Escribe aqui la precondicion de la funcion.
  P: {0 < n <= tam(a) ^ PARATODO i: 0 <= i < n-1: a[i] <= a[i+1]}
*/
int misterio(const int a[], int n) {
    int i = 1, contador = 1, max = 1, num = a[0], resul = a[0];
    while(i < n){
        if(a[i] == num){
            contador++;
        }else{
            num = a[i];
            contador = 1;
        }
        if(contador > max){
            max = contador;
            resul = num;
        }
        i++;
    }
    return resul;
} 
/*
POSTCONDICION DE LA FUNCION: 
  Q: {resul = min i: 0 <= i < n ^ ( (#j: 0 <= j < n: a[i] = a[j]) = (max j: 0 <= j < n: (#k: 0 <= k < n: a[j] = a[k]) ) ): a[i] }
  Resul sera el valor minimo del vector que cumpla que:
  -- La cantidad de veces que ese elemento se repite en el vector sea igual a:
  -- El elemento que se repite mas veces en el vector
  Es decir, que este algoritmo busca el numero que mas veces se repite en el vector, y en caso de haber
  dos elementos que tengan la misma cantidad de repeticiones, escogera el mas pequeño
*/

/* COMPLEJIDAD:
   Tiene complejidad O(n), porque el bucle se ejecuta tantas veces como el tamaño del segmento del array a de tamaño n
*/

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA. NO MODIFICAR */

void lee_vector(int a[], int & n) {
	cin >> n; 
   for (int i=0; i < n; i++) {
	   cin >> a[i]; 
   }   
}

int main() {
	static int a[TMAX];
	int n;
   do {
	   lee_vector(a,n); 
	   if (n>=0) {
		   cout << misterio(a, n) << endl;
	   }
   }
   while (n != -1);
}