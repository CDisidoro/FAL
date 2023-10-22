/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:
    CAMILO ANDRES D'ISIDORO
Si alguno de los miembros del grupo no ha realizado
la practica, indicarlo aqui, junto con el motivo:
*/
#include <iostream>
using namespace std;


/*
PRECONDICION DE LA FUNCION:
    P = { 0 <= n <= tam(a) }
*/
int long_tramo_par_mas_largo(int v[], unsigned int n);
/*
POSTCONDICION DE LA FUNCION:
(1) Definiciones auxiliares (si procede):
(2) Postcondicion
    Q = { resul = max ini, fin: 0 <= ini <= fin < n ^ (ParaTodo i: ini <= i <= fin: a[i] % 2 = 0): (fin - ini) + 1 v
          resul = 0: ParaTodo i: 0 <= i < n: a[i] % 2 != 0 }
*/

/* DISEÑO DEL ALGORITMO:
--- Detalla aqui el proceso seguido para diseñar el algoritmo
PASO 1. Variables adicionales (aparte de los parametros y el resultado)
    ini, fin
PASO 2. Invariante
    (2.1) Definiciones auxiliares (si procede)
    (2.2) Invariante
        resul = max ini, fin: 0 <= ini <= fin <= n ^ (ParaTodo i: ini <= i <= fin: a[i] % 2 = 0): (fin - ini) + 1 v
        resul = 0: ParaTodo i: 0 <= i <= fin <= n: a[i] % 2 != 0
PASO 3. Codigo de inicializacion, justificando que, tras
        dicho codigo, se cumple el invariante
        ini = 0, fin = 0, resul = 0
        Ini y fin son cero, por lo que cumple 0 <= ini <= fin <= n
        resul es cero, por lo que cumple que no hay tramo de pares
PASO 4. Condicion del bucle, codigo tras el bucle (si procede),
        y justificacion de que, una vez finalizado el algoritmo,
        se cumple la postcondicion
        while(fin < n){...}
        return resul
PASO 5. Diseño del cuerpo del bucle, justificando que dicho codigo
        preserva el invariante
        if(ini == fin && a[fin] % 2 != 0){
            ini++;
            fin++;
        }else{
            if(a[fin] % 2 == 0){
                if(fin - ini + 1 > resul){
                    resul = fin - ini + 1;
                }
                fin++;
            }else{
                ini = fin;
            }
        }
PASO 6: Expresion de cota y justificacion de que el algoritmo siempre 
        termina
        Cota: n - fin, pues fin siempre avanza en cada iteracion hasta que cota=0
PASO 7: Determinacion justificada de la complejidad del algoritmo
        O(n)
*/
int long_tramo_par_mas_largo(int v[], int n) {
	int ini = 0, fin = 0, resul = 0;
    while(fin < n){
        if(ini == fin && v[fin] % 2 != 0){
            ini++;
            fin++;
        }else{
            if(v[fin] % 2 == 0){
                if(fin - ini + 1 > resul){
                    resul = fin - ini + 1;
                }
                fin++;
            }else{
                ini = fin;
            }
        }
    }
    return resul;
}	

/* PROGRAMA DE PRUEBA: No modificar */
const int MAX_ELEMS = 1000000;
 
bool ejecuta_caso() {
	int n;
	cin >> n;
	static int v[MAX_ELEMS];
	if (n == -1) return false;
	else {
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		cout << long_tramo_par_mas_largo(v, n) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
}