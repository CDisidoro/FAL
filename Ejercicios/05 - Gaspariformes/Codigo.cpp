#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habra vectores de mas de dos millones de elementos


/*
PRECONDICION DE LA FUNCION: 
  P = { 0 < n <= tam(a) }
*/
bool es_gaspariforme(const int a[], int n); 
/*
POSTCONDICION DE LA FUNCION: 
  Q = { resul = (ParaTodo i: 0 <= i < n - 1: sumaParcialPos(a,i,resul)) ^ (SUM i: 0 <= i < n: a[i]) = 0 }
  sumaParcialPos(a,i,resul): resul = (SUM x: 0 <= x < i: a[x]) > 0
*/

/*
    DISEÑO DEL ALGORITMO:
    -- Especifica cada paso del diseño en cada apartado indicado
    Paso 1. Variables:
        i, sum, resul
    Paso 2. Invariante:
        resul = (ParaTodo x: 0 <= x <= i <= n - 1: sumaParcialPos(a,x,resul))
    Paso 3. Inicializacion:
        i = 0, sum = 0, resul = true
    Paso 4. Condicion del bucle, y codigo tras el bucle
        while(i < n - 1 && resul){...}
        if(sum + a[i] != 0){ resul = false }
        return resul
    Paso 5. Cuerpo del bucle
        suma += a[i]
        if(suma < 0){ resul = false }
        i++
    Paso 6. Justificacion de que el algoritmo siempre termina
        COTA = n - i
        Porque i se incrementa siempre tras cada iteracion, haciendo que la cota
        baje hasta cero. O en su defecto, si se deja de cumplir sumParcialPos para
        todas las sumas parciales
    Paso 7. Complejidad
        O(n), porque iteramos tantas veces como elementos haya en el vector
*/
bool es_gaspariforme(const int a[], int n) {
    int i = 0, suma = 0;
    bool resul = true;
    while(i < n - 1 && resul){
        suma += a[i];
        if (suma <= 0){
            resul = false;
        }
        i++;
    }
    if(suma + a[i] != 0){
        resul = false;
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
		 if (es_gaspariforme(a,n)) 
           cout << "SI" << endl;
         else  
           cout << "NO" << endl;			 
	   }
   }
   while (n >= 0);	
}