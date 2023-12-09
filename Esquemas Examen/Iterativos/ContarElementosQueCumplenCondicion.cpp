#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habra vectores de mas de dos millones de elementos

/*
PRECONDICION DE LA FUNCION: 
  P = { 0 <= n <= tam(a) }
*/
int num_chupiguays(const int a[], int n); 
/*
POSTCONDICION DE LA FUNCION: 
  Q = { resul = #i: 0 <= i < n: a[i] % (SUM j: 0 <= j < i: a[j]) = 0 }
*/

/*
DISEÑO DEL ALGORITMO:
-- Especifica cada paso del diseño en cada apartado indicado
Paso 1. Variables:
    i, resul, sum
Paso 2. Invariante:
    resul = #x: 0 <= x <= i < n: a[x] % sum = 0 ^ 
    sum = SUM y: 0 <= y < x <= i < n: a[y]
Paso 3. Inicializacion:
    i = 0
    resul = 0
    sum = 0
Paso 4. Condicion del bucle, y codigo tras el bucle:
    while(i < n){...}
    return resul
Paso 5. Cuerpo del bucle
    if(a[i] == 0 || sum > 0 && a[i] % sum == 0){ resul++ }
    sum += a[i]
    i++
Paso 6. Justificacion de que el algoritmo siempre termina
    COTA = n - i
Paso 7. Complejidad
    O(n), pues iteramos tantas veces en el bucle como elementos haya en el vector
*/
int num_chupiguays(const int a[], int n) {
    int i = 0, resul = 0, sum = 0;
    /*
    Recorremos el array entero contando los elementos que cumplan una condición concreta, no tiene mucha ciencia
    */
    while(i < n){
        if(a[i] == 0 || (sum != 0 && a[i] % sum == 0)){
            resul++;
        }
        sum += a[i];
        i++;
    }
    return resul;
} 

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */
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
		   cout << num_chupiguays(a, n) << endl;
	   }
   }
   while (n != -1);
}