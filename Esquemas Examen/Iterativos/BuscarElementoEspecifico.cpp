#include <iostream>

using namespace std;

const int TMAX = 1000000;  // No habra vectores de mas de un millon de elementos

/*
PRECONDICION DE LA FUNCION: 
  P = { 0 < n <= tam(a) ^ ParaTodo i: 0 <= i < n - 1: a[i] <= a[i+1] }
*/
int menor_moda(const int a[], int n); 
/*
POSTCONDICION DE LA FUNCION: 
  Q = { resul = min x: 0 <= x < n ^ max i: 0 <= i < n: (#j: 0 <= j < i: a[i] = a[j]) : a[x] }
  
*/

/*
DISEÑO DEL ALGORITMO:
-- Especifica cada paso del diseño en cada apartado indicado
Paso 1. Variables
    i, resul, resulReps, num, reps
Paso 2. Invariante
    resul = min x: 0 <= x <= i < n ^ max x: 0 <= x <= i < n: reps : num ^
    resulReps = max x: 0 <= x <= i < n: reps ^ 
    num = a[x]: 0 <= x <= i < n ^
    reps = #x: 0 <= x <= i < n: num = a[x]
Paso 3. Inicializacion
    i = 1, resul = a[0], resulReps = 1, num = a[0], reps = 1
Paso 4. Condicion del bucle, y codigo tras el bucle
    while(i < n){...}
    return resul
Paso 5. Cuerpo del bucle
    if(a[i] == num){
        reps++;
        if(reps == resulReps && num < resul){
            resul = num;
        }
        if(reps > resulReps){
            resulReps = reps
            resul = num
        }
    }else{
        num = a[i]
        reps = 1
    }
    i++
Paso 6. Justificacion de que el algoritmo siempre termina
    COTA: n - i porque i siempre aumenta por cada iteración, al punto que n-i=0
Paso 7. Complejidad
    O(n) porque el bucle se ejecuta 1 vez por cada elemento en el vector
*/
int menor_moda(const int a[], int n) {
    int i = 1, resul = a[0], resulReps = 1, num = a[0], reps = 1;
    /*
    Para este ejercicio se busca el valor mas pequeño que mas se repite en un vector ordenado, en el cual para cada elemento
    sumamos las veces que se repite y compara con la mejor solucion hallada hasta ahora, y si es mejor actualiza la mejor solucion
    */
    while(i < n){
        if(a[i] == num){
            reps++;
            if(reps == resulReps && num < resul){
                resul = num;
            }
            if(reps > resulReps){
                resulReps = reps;
                resul = num;
            }
        }else{
            num = a[i];
            reps = 1;
        }
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
		   cout << menor_moda(a, n) << endl;
	   }
   }
   while (n != -1);
}