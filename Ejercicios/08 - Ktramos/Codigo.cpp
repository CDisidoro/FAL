
#include <iostream>
using namespace std;
const int MAX_TAM = 100;


/*
PRECONDICION DE LA FUNCION: 
  P = { 0 <= n <= tam(a) }
*/
int tramo_mas_corto(bool a[], int n, int k); 
/*
POSTCONDICION DE LA FUNCION: 
    Q = { resul = min ini, fin: 0 <= ini <= fin < n ^ (#i: ini <= i <= fin : a[i] = true) = k : (fin - ini) + 1 v
          resul = n + 1: ¬Existe ini, fin: 0 <= ini <= fin < n: (#i: ini <= i <= fin : a[i] = true) = k }
*/


/*
DISEÑO DEL ALGORITMO:
Paso 1. Variables
    ini, fin, resul, conteo, found
Paso 2. Invariante
    resul = min ini, fin: 0 <= ini <= fin <= n ^ conteo = k: (fin - ini) + 1 ^
    conteo = #i: ini <= i <= fin : a[i] = true ^
    found = Existe ini, fin: 0 <= ini <= fin <= n: conteo = k
Paso 3. Inicializacion
    ini = 0, fin = 0, resul = 0, conteo = 0, found = false
Paso 4. Condicion del bucle, y codigo tras el bucle.
    while(fin < n){...}
    if(!found){
        resul = n + 1;
    }
    return resul
Paso 5. Cuerpo del bucle
    if(a[fin] == true){
        conteo++;
        if(conteo == k){
            while(a[ini] == false){
                ini++;
            }
            if(fin - ini + 1 < resul){
                resul = fin - ini + 1;
                found = true;
            }
        }else if(conteo > k){
            while(conteo > k){
                if(a[ini] == true){
                    conteo--;
                }
                ini++;
            }
        }
    }
    fin++;
Paso 6. Justificacion de que el algoritmo siempre termina.
    COTA: n - fin, pues fin siempre va a incrementarse
Paso 7. Complejidad
    O(n)
*/
int tramo_mas_corto(bool a[], int n, int k){
    int ini = 0, fin = 0, resul = MAX_TAM, conteo = 0;
    bool found = false;
    while (fin < n){
        if(a[fin]){
            conteo++;
            if(conteo == k){
                while(!a[ini]){
                    ini++;
                }
                if(fin - ini + 1 < resul){
                    resul = fin - ini + 1;
                    found = true;
                }
                ini++;
                conteo--;
            }
        }
        fin++;
    }
    if (!found){
        resul = n + 1;
    }
    return resul;
}

/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA: 
   NO MODIFICAR */
void lee_caso(int& n, bool a[], int& k) {
	cin >> n;
	if (n != -1) {
		for (int i = 0; i < n; i++) {
			int elem;
			cin >> elem;
			a[i] = bool(elem);
		}
		cin >> k;
	}
}

int main() {
	int n;
	bool a[MAX_TAM];
	int k;
	do {
		lee_caso(n, a, k);
		if (n != -1) {
			cout << tramo_mas_corto(a, n, k) << endl;
		}
	} while (n != -1);
}
	
	