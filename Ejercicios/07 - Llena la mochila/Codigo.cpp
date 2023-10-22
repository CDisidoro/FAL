#include <iostream>

using namespace std;

const int TMAX = 2000000;  // No habra vectores de mas de dos millones de elementos


/*
PRECONDICION DE LA FUNCION: 
  P = { 0 < n <= tam(a) ^ ParaTodo i: 0 <= i < n : 0 < a[i] <= k ^ k > 0 }
*/
int llena_mochila(const int a[], int n, int k); 
/*
POSTCONDICION DE LA FUNCION: 
  Q = { resul = max ini, fin: 0 <= ini <= fin < n ^
    (SUM i: ini <= i <= fin: a[i] <= k): (fin - ini) + 1 }
*/
 

/*
DISEÑO DEL ALGORITMO:
Paso 1. Variables
    ini, fin, resul, suma, conteo
Paso 2. Invariante
    resul = max ini, fin: 0 <= ini <= fin <= n ^ suma <= k: (fin - ini) + 1 ^
    suma = SUM i: ini <= i <= fin: a[i] ^
    conteo = (fin - ini) + 1
Paso 3. Inicializacion
    ini = 0, fin = 0, suma = 0, conteo = 0, resul = 0
Paso 4. Condicion del bucle, y codigo tras el bucle.
    while(fin < n){...}
    return resul;
Paso 5. Cuerpo del bucle
    suma += a[fin];
    while(suma > k || fin - inicio != 0){
        suma -= a[ini];
        ini++;
        conteo--;
    }
    if(suma <= k){
        conteo++;
        if(resul < conteo){
            resul = conteo;
        }
    }
    fin++;
Paso 6. Justificacion de que el algoritmo siempre termina.
    COTA: n - fin, porque fin siempre incrementa por cada iteracion del bucle externo
Paso 7. Complejidad:
    O(n)
*/
int llena_mochila(const int a[], int n, int k) {
    int ini = 0, fin = 0, suma = 0, resul = 0;
    while(fin < n){
        suma += a[fin];
        while(suma > k && (fin - ini != 0)){
            suma -= a[ini];
            ini++;
        }
        if(suma <= k){
            if(resul < (fin - ini) + 1){
                resul = fin - ini + 1;
            }
        }
        fin++;
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
		   int k;
		   cin >> k;
		   cout << llena_mochila(a, n, k) << endl;
	   }
   }
   while (n != -1);
}