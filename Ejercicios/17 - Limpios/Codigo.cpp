#include <iostream>

using namespace std;

typedef unsigned long long t_num;

/*
(1) En caso de utilizar una generalización, indicar su parámetros, y explicar para que
sirven cada uno de ellos
	Entradas
		t_num nextNum  => Contiene el numero que comprobamos ahora
		int sumaActual => Suma de digitos
		int cantidad   => Cantidad de digitos parte de la secuencia (Limita el tamaño de la secuencia a alpha)
	Salidas
		int soluciones => Cuenta las soluciones finales
(2) ¿Cómo son las soluciones parciales de este problema?
	Numeros entre 1 y n
(3) ¿Cuándo una solución parcial es viable?
	Cuando no tiene ceros y la suma de sus digitos es menor a s
(4) ¿Cuándo una solución parcial es una solución final al problema?
	Cuando la suma de sus digitos es 12 y las ocurrencias consecutivas de d tienen
	longitud menor que alpha
(5) Dada una solución parcial, ¿cómo se generan las siguientes soluciones
parciales viables?
	(nextNum * 10) + nextDigit
	Donde nextDigit va de 1 a 9 generando numeros
(6) Análisis de casos
	(6.1) Caso(s) base
		if(sumaActual == s && nextNum != 0)
			soluciones++
	(6.2) Caso(s) recursivos
		if(nextDigit != d)
			solve(d, alpha, n, s, (nextNumber * 10) + nextDigit, sumaActual + nextDigit, 0, soluciones)
		else if (cantidad + 1 < alpha)
			solve(d, alpha, n, s, (nextNumber * 10) + nextDigit, sumaActual + nextDigit, cantidad + 1, soluciones)
		nextDigit++
(7) En caso de utilizar una generalización, explicar cómo se define el algoritmo final
a partir de la misma, por inmersión.
	solve(d, alpha, n, s, 0, 0, 0, 0)
*/
void solve(unsigned short d, unsigned short alpha, t_num n, unsigned int s, t_num nextNum, unsigned int sumaActual, unsigned int cantidad, int &soluciones){
	if(sumaActual == s && nextNum != 0){
		soluciones++;
	}else{
		unsigned int nextDigit = 1;
		bool continuar = true;
		while(continuar){
			if(nextDigit > 9 || (sumaActual + nextDigit) > s || ((nextNum * 10) + nextDigit) >= n){
				continuar = false;
			}else{
				if(nextDigit != d){
					solve(d, alpha, n, s, (nextNum * 10) + nextDigit, sumaActual + nextDigit, 0, soluciones);
				}else if(cantidad + 1 < alpha){
					solve(d, alpha, n, s, (nextNum * 10) + nextDigit, sumaActual + nextDigit, cantidad + 1, soluciones);
				}
				nextDigit++;
			}
		}
	}
}


int num_limpios(unsigned short d, unsigned short alpha, t_num n, unsigned int s) {
	int soluciones = 0;
	solve(d, alpha, n, s, 0, 0, 0, soluciones);
	return soluciones;
}


bool ejecuta_caso() {
	int d;
	cin >> d;
	if (d == -1) {
		return false;
	}
	else {
		unsigned short alpha; 
		unsigned int s;
		t_num n;
		cin >> alpha >> s >> n;
		cout << num_limpios(d, alpha, n, s) << endl;
		return true;
	}
}


int main() {
	while (ejecuta_caso());
}