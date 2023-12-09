#include <iostream>
using namespace std;
const int TMAX = 1000000;  // No habra vectores de mas de un millon de elementos
/*
PRECONDICION DE LA FUNCION:
  P: {0 <= n <= tam(a)}
*/
bool divertida(const int a[], int n);
/*
POSTCONDICION DE LA FUNCION: 
  Q: { resul = (  (PARATODO i:0<=i<n:(SUMA j:0<=j<=i:a[j])>=0) && ( (SUMA i:0<=i<n:a[i])=0 ) ) }
  Para que resul sea true se debe cumplir que:
  -- La suma de los elementos anteriores mas el mismo debe ser mayor o igual a cero
  -- La suma de todos los elementos del vector debe ser cero
*/
bool divertida(const int a[], int n) {
    bool resul = true;
    int suma = 0, i = 0;
    /* 
    Debemos recorrer el array mientras no lleguemos al final y el condicional no se haya roto
    No tendria sentido seguir comprobando el vector si uno de sus valores hace que la condicion no se cumpla
    */
    while(i < n && resul){ 
        suma += a[i];
        if(suma < 0){
            resul = false;
        }
        i++;
    }
    if(suma != 0){
        resul = false;
    }
    return resul;
} 
/* COMPLEJIDAD:
   Tiene complejidad O(n), puesto que hacemos iteraciones del bucle while tantas veces como elementos haya en el segmento del array a de tamano n
*/

/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA. NO MODIFICAR! */

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
		 if (divertida(a,n)) 
           cout << "SI" << endl;
         else  
           cout << "NO" << endl;			 
	   }
   }
   while (n != -1);
}