/*
Nº GRUPO: B
NOMBRES Y APELLIDOS: Camilo Andres D'isidoro
*/
#include <iostream>

using namespace std;


//n siempre sera positivo (es decir, podeis asumir n >= 1)
int diametro(int a[], int n) {
    int min = a[0], max = a[0];
    for(int i = 1; i < n; i++){
        if(a[i] < min){
            min = a[i];
        }
        if(a[i] > max){
            max = a[i];
        }
    }
    return abs(max - min);
}


/* CODIGO PARA LEER Y EJECUTAR LOS CASOS DE PRUEBA */

const int TMAX = 1000000;  // No se podran leer vectores de mas de un millon de elementos

bool ejecuta_caso() {
	static int a[TMAX];
	int n;
	cin >> n;
	if (n == -1 || n > TMAX) {
		return false;
	}
	else {
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		cout << diametro(a, n) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
}