/*
Nº GRUPO: B02
NOMBRE Y APELLIDOS DE LOS MIEMBROS DEL GRUPO:
    CAMILO ANDRES D'ISIDORO
    JUAN ISRAEL BAROFFI GONZALEZ
SI ALGUNO DE LOS MIEMBROS NO HA PARTICIPADO, 
INDICAR AQUI EL MOTIVO:
    TODOS HEMOS PARTICIPADO
IMPORTANTE: Si no se añaden estos datos, el ejercicio no
se corregira (puntuara 0)

*/

#include <iostream>

using namespace std;

/*
IMPORTANTE: Para superar este ejercicio es necesario desarrollar
correctamente los distintos pasos del diseño del algoritmo. No 
se tendra en cuenta la codificacion del algoritmo, a menos que
este acompañada de la especificacion y el diseño sistematico
del mismo.
*/


/*
   vcs: vector de valores caloricos.
   vns: vector de valores nutricionales.
   n: Numero de chuches.
   u: Umbral calorico
*/
/*
PRECONDICION DE LA FUNCION:
    P = { 0 < n <= tam(vcs) ^ 0 < n <= tam(vns) ^ tam(vcs) = tam(vns) ^ 0 < u ^ 
        ParaTodo i: 0 <= i < n: 0 <= vcs[i] <= u ^
        ParaTodo i: 0 <= i < n: vns[i] >= 0 }
*/
int mejor_cajita(int vcs[], int vns[], int n, int u);
/*
POSTCONDICION DE LA FUNCION: 
    Q = { sumatorio(a,i,j) = SUMA x: i <= x <= j: a[x] ^
          resul = max i,j: 0 <= i <= j < n ^ sumatorio(vcs,i,j) <= u: sumatorio(vns,i,j) }
*/

/*
DISEÑO DEL ALGORITMO:
Paso 1. Variables
    sumCalorica -> Suma de valores caloricos actual
    sumNutri -> Suma de valores nutricionales actual
    ini, fin -> Inicio y fin de ventana
    resul -> Mejor suma nutricional (Resultado final)
Paso 2. Invariante
    sumatorio(a,i,j) = SUMA x: i <= x <= j: a[x] ^
    resul = max ini, fin: 0 <= ini <= fin <= n ^ sumCalorica <= u: sumNutri ^
    sumCalorica = sumatorio(vcs, ini, fin-1) ^
    sumNutri = sumatorio(vns, ini, fin-1)
Paso 3. Inicializacion
    int sumCalorica = vcs[0];
    int sumNutri = vns[0];
    int ini = 0;
    int fin = 1;
    int resul = vns[0];
Paso 4. Condicion del bucle, y codigo tras el bucle.
    while(fin < n){...}
    return resul;
Paso 5. Cuerpo del bucle
    if(sumCalorica+vcs[fin] <= u){
        sumCalorica += vcs[fin];
        sumNutri += vns[fin];
        fin++;
        if(sumNutri > resul){
            resul = sumNutri;
        }
    }else{
        sumCalorica -= vcs[ini];
        sumNutri -= vns[ini];
        ini++;
    }
Paso 6. Justificacion de que el algoritmo siempre termina.
    Cota: 2n - (ini + fin), pues o bien ini o fin siempre aumentaran hasta llegar al suelo de la cota
Paso 7. Complejidad:
    El algoritmo puede dar como maximo 2n iteraciones, con cada iteracion de complejidad Theta(1)
    Por ende, el coste del algoritmo es Theta(n)
*/
int mejor_cajita(int vcs[], int vns[], int n, int u) {
    int sumCalorica = vcs[0], sumNutri = vns[0], ini = 0, fin = 1, resul = vns[0];
    while(fin < n){
        if(sumCalorica + vcs[fin] <= u){
            sumCalorica += vcs[fin];
            sumNutri += vns[fin];
            fin++;
            if(sumNutri > resul){
                resul = sumNutri;
            }
        }else{
            sumCalorica -= vcs[ini];
            sumNutri -= vns[ini];
            ini++;
        }
    }
    return resul;
}

/************************************************************/
// Programa de prueba: NO MODIFICAR. Aquellas soluciones que
// modifiquen el codigo que sigue no se corregiran (puntuaran 0).

const static int MAX_CHUCHES = 1000000;

bool ejecuta_caso() {
	int n;
	cin >> n;
	if (n == -1) return false; 
	else {
		static int calorias[MAX_CHUCHES];
		static int nutricionales[MAX_CHUCHES];
		for (int i = 0; i < n; i++) {
			cin >> calorias[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> nutricionales[i];
		}
		int umbral;
		cin >> umbral;
		cout << mejor_cajita(calorias, nutricionales, n, umbral) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
	return 0;
}