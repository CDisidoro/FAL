
#include <iostream>

using namespace std;


/*
(1) En caso de utilizar una generalizacion,
determinacion de los parametros de la generalizacion.
Determina los parametros de la generalizacion. Para cada parametro
indica: (i) su tipo; (ii) su nombre; (iii) si es un parametro
de entrada, de salida, o de entrada / salida; (iv) su proposito,
descrito de manera clara y concisa.
	Entradas:		int minP -> Poder minimo para pelear
					int maxP -> Poder maximo para pelear
	Entrada/Salida: int midP -> Valor medio para pelear
(2) Analisis de casos:
(2.1) Casos base
	max_duelos <= 1 && n >= 0
		return sum i: 0 <= i < n: a[i] (Suma de poder de los n oponentes)
(2.2) Casos recursivos
	max_duelos > 1 && n > 0
		acota(enemigos, n, max_duelos, minP, maxP);
		midP = (minP + maxP) / 2;
		if(vence(enemigos, n, max_duelos, midP)){
			if(!vence(enemigos, n, max_duelos, midP - 1)){
				return maxP;
			}else{
				return min_poder_aux(enemigos, n, max_duelos, minP, midP - 1);
			}
		}else{
			return min_poder_aux(enemigos, n, max_duelos, midP + 1, maxP);
		}
(3) En caso de utilizar una generalizacion, definicion por inmersion
del algoritmo. Describe de manera clara y concisa como se lleva a
cabo el algoritmo, en que punto o puntos se invoca a la generalizacion,
con que parametros reales, y como se genera el resultado
a partir de los devueltos por la generalizacion.
	acota(enemigos, n, max_duelos, minP, maxP);
	min_poder_aux(enemigos, n, max_duelos, minP, maxP);
	Tras acotar el minimo y maximo de poder, se llama a la generalizacion
	Esta va modificando minP y maxP para obtener el poder minimo para ganar
(4) Analisis de la complejidad del algoritmo
	T(n) = n * C0 (Caso Base)
	T(n) = C1 + T(n/2) (Caso Recursivo)
	a = 1 (Dividimos el problema en 1 subproblema)
	b = 2 (Dividimos el problema a la mitad)
	k = 1
	b^k = 2
	a < b^k
	O(n^k) = O(n^2)
*/
bool vence(int enemigos[], int n, int max_duelos, int poder){
	int i = 0, combate = 1, suma = 0;
	while(i < n && (enemigos[i] <= poder) && (combate <= max_duelos)){
		suma += enemigos[i];
		if(suma > poder){
			suma = enemigos[i];
			combate++;
		}
		i++;
	}
	return i == n && combate <= max_duelos;
}

void acota(int enemigos[], int n, int max_duelos, int &minP, int &maxP){
	minP = 0;
	maxP = 2;
	while(!vence(enemigos, n, max_duelos, maxP)){
		minP = maxP;
		maxP *= 2;
	}
}

int min_poder_aux(int enemigos[], int n, int max_duelos, int minP, int maxP){
	int mid = (minP + maxP) / 2;
	if(vence(enemigos, n, max_duelos, mid)){
		if(!vence(enemigos, n, max_duelos, mid-1)){
			return mid;
		}else{
			return min_poder_aux(enemigos, n, max_duelos, minP, mid - 1);
		}
	}else{
		return min_poder_aux(enemigos, n, max_duelos, mid + 1, maxP);
	}
}

int min_poder(int enemigos[], int n, int max_duelos) {
	int minP, maxP;
	acota(enemigos, n, max_duelos, minP, maxP);
	return min_poder_aux(enemigos, n, max_duelos, minP, maxP);
}


const int MAX_ENEMIGOS = 1000;
bool ejecuta_caso() {
	int enemigos[MAX_ENEMIGOS];
	int num_enemigos;
	cin >> num_enemigos;
	if (num_enemigos == -1) {
		return false;
	}
	else {
		int max_torneos;
		cin >> max_torneos;
		for (int i = 0; i < num_enemigos; i++) {
			cin >> enemigos[i];
		}
		cout << min_poder(enemigos, num_enemigos, max_torneos) << endl;
		return true;
	}
}

int main() {
	while (ejecuta_caso());
}