/*
NOMBRE Y APELLIDOS: CAMILO ANDRES D'ISIDORO
IMPORTANTE: Si no se añade el nombre y apellidos,
el ejercicio no se corregira (puntuara como 0).
*/
#include <iostream>
using namespace std;

/*
(1) En caso de utilizar una generalizacion, 
determinacion de los parametros de la generalizacion.
Determina los parametros de la generalizacion. Para cada parametro
indica: (i) su tipo; (ii) su nombre; (iii) si es un parametro
de entrada, de salida, o de entrada / salida; (iv) su proposito,
descrito de manera clara y concisa.
es_superb_aux(int v[], int ini, int fin, int &min, int &max)
    int v[]: Vector de datos (Entrada)
    int ini: Posicion inicial de busqueda (Entrada)
    int fin: Posicion final de busqueda (Entrada)
    int &min: Valor minimo del segmento (Salida)
    int &max: Valor maximo del segmento (Salida)
(2) Analisis de casos:
(2.1) Casos base
    (fin - ini) + 1 < 3:
        min = min(v[ini], v[fin])
        max = max(v[ini], v[fin])
        return true
(2.2) Casos recursivos
    (fin - ini) + 1 >= 3:
        medio = (fin - ini) / 2
        superb = es_superb_aux(v, ini, medio - 1, minIzq, maxIzq) ^ es_superb_aux(v, medio + 1, fin, minDer, maxDer) ^ v[medio] == abs(maxI - minD)
        min = min(minIzq, minDer, maxIzq, maxDer, v[medio])
        max = max(minIzq, minDer, maxIzq, maxDer, v[medio])
        return superb

(3) En caso de utilizar una generalizacion, definicion por inmersion 
del algoritmo. Describe de manera clara y concisa como se lleva a 
cabo el algoritmo, en que punto o puntos se invoca a la generalizacion,
con que parametros reales, y como se genera el resultado
a partir de los devueltos por la generalizacion.
    Al ejecutar el algoritmo comprobamos si es superb para los segmentos de la mitad 
    izquierda y derecha con recursión hasta llegar al caso base (longitud < 3), donde 
    calculara el minimo y maximo del segmento y dara true. Y al ir volviendo de la recursion
    el resultado se calcula del valor absoluto de restar el maximo izquierdo con el minimo derecho.
    Una vez calculado superb, se obtiene el minimo y maximo del segmento comprobando los minimos y maximos 
    izquierdos y derechos para sacar el minimo y maximo general, que se usaran segun sea necesario en la siguiente 
    llamada

(4)Determina justificadamente la complejidad del algoritmo
(4.1) Determinacion de las ecuaciones de recurrencia para la generalizacion
    T(n) = C0 ((fin - ini) +  1) < 3 -> Caso Base
    T(n) = C1 + 2T(n/2)
(4.2) Resolucion utilizando los patrones vistos en clase
    a = 2
    b = 2
    k = 0
    b^k = 2^0 = 1
(4.3) Determinacion justificada de la complejidad del algoritmo final.
    2 > 1
    O(n^log_2 2) = O(n)
*/
bool es_superb_aux(int v[], int ini, int fin, int &min, int &max){
    //Caso Base
    if((fin - ini) + 1 < 3){
        if(v[ini] < v[fin]){
            min = v[ini];
            max = v[fin];
        }else{
            min = v[fin];
            max = v[ini];
        }
        return true;
    }else{ //Caso Recursivo
        int minI, minD, maxI, maxD, mid = v[(fin + ini) / 2];
        bool superb;
        if(es_superb_aux(v, ini, ((ini + fin) / 2) - 1, minI, maxI) && es_superb_aux(v, ((ini + fin) / 2) + 1, fin, minD, maxD) ){
            superb = mid == abs(maxI - minD);
            if(minI <= minD && minI <= maxI && minI <= maxD && minI <= mid){
                min = minI;
            }else if(minD <= minI && minD <= maxI && minD <= maxD && minD <= mid){
                min = minD;
            }else if(maxI <= minI && maxI <= minD && maxI <= maxD && maxI <= mid){
                min = maxI;
            }else if(maxD <= minI && maxD <= minD && maxD <= maxI && maxD <= mid){
                min = maxD;
            }else if(mid <= minI && mid <= minD && mid <= maxI && mid <= maxD){
                min = mid;
            }
            if(minI >= minD && minI >= maxI && minI >= maxD && minI >= mid){
                max = minI;
            }else if(minD >= minI && minD >= maxI && minD >= maxD && minD >= mid){
                max = minD;
            }else if(maxI >= minI && maxI >= minD && maxI >= maxD && maxI >= mid){
                max = maxI;
            }else if(maxD >= minI && maxD >= minD && maxD >= maxI && maxD >= mid){
                max = maxD;
            }else if(mid >= minI && mid >= minD && mid >= maxI && mid >= maxD){
                max = mid;
            }
            return superb;
        }
        return false;
    }
}

bool es_superb(int v[], int n) {
	// A IMPLEMENTAR: Devolver true si el vector v[n] es superb,
	// y false si no lo es.
    int min, max;
    return es_superb_aux(v, 0, n - 1, min, max);
}


/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el codigo que sigue no se corregiran (puntuaran 0).


const static int MAX_ELEMENTS = 10000;

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		int v[MAX_ELEMENTS];
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		if (es_superb(v, n)) {
			cout << "SUPERB" << endl;;
		}
		else {
			cout << "NO SUPERB" << endl;
		}
		return true;
	}
}


int main() {
	while (ejecuta_caso());
	return 0;
}