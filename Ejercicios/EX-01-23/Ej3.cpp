/*
NOMBRE Y APELLIDOS: Camilo Andres D'isidoro
*/
#include <iostream>
using namespace std;
static const int MAX_MONEDAS = 100;

/* Tipo para representar los datos de entrada */
typedef struct {
  int num_monedas;     /* Numero de monedas a repartir */
  int min_monedas;     /* Minimo de monedas que debe recibir cada pirata -los dos deben
                          recibir este minimo numero de monedas */
  int valor_monedas[MAX_MONEDAS];  /* Valor de las distintas monedas a repartir */
} tEntrada;

typedef struct{
	int numMonedasPirata1;
	int numMonedasPirata2;
	int valorPirata1;
	int valorPirata2;
	int monedasPirata1[MAX_MONEDAS/2];
	int monedasPirata2[MAX_MONEDAS/2];
}tDatos;
/*
(1) Como son las soluciones parciales viables de este problema?
	Se tiene la suma de valor de las monedas del pirata 1 y del pirata 2, y el numero de monedas que tienen
	Una solucion es viable siempre que la diferencia de monedas entre los dos piratas sea menor o igual que 1
(2) Cuando una solucion es final?
	Cuando ya no quedan mas monedas que repartir. Para la mejor solucion se comprueba la diferencia de valores,
	y si se encuentra una nueva mejor solucion se restablece la cantidad de mejores soluciones
(3) Dada una solucion viable, como se generan nuevas soluciones viables a partir de ella?
	Revisando que la diferencia de monedas entre los piratas no supere 1
(4) Como se representaran las soluciones en este problema? Describe los distintos elementos
    de informacion que las componen, indicando si se representan como parametros de entrada,
	de entrada/salida (estado global), si se representan implicitamente...
	tEntrada entrada (Entrada): Informacion de entrada
		int num_monedas: Numero de monedas a repartir
		int min_monedas: Monedas minimas que tendra cada pirata
		int valor_monedas[MAX_MONEDAS]: Valor de cada moneda
	tDatos datos (Entrada): Informacion de la solucion parcial
		int numMonedasPirata1: Numero de monedas del pirata 1
		int numMonedasPirata2: Numero de monedas del pirata 2
		int valorPirata1: Suma de valor del pirata 1
		int valorPirata2: Suma de valor del pirata 2
	int minDiff (Entrada/Salida): Diferencia minima del valor de los dos piratas
	int soluciones (Salida): Cantidad de soluciones que tienen la diferencia minima
(5) Que marcadores utiliza el algoritmo? Describe claramente su proposito, los elementos
    de informacion que los componen, asi como si dichos elementos se representan como parametros
	de entrada, de entrada/salida (estado global)... 
	tDatos datos: Informacion de la solucion parcial. Para probar una solucion nueva se añade a los datos, y despues de probarla se deshacen los cambios
(6) Si el algoritmo utiliza generalizacion, indica como es la misma, describiendo claramente
    el proposito de cada parametro.
	reparte_aux(const tEntrada &entrada, const tDatos datos, int &min_diff, int &num_formas)
	tEntrada entrada: Datos de entrada
	tDatos datos: Datos de la solucion parcial
	int min_diff: Diferencia minima de los valores de los piratas
	int num_formas: Numero de formas de repartir el botin con la diferencia de valor minima
(7) Analisis de casos: casos base, casos recursivos
	Caso Base:
		if((datos.monedasPîrata1 + datos.numMonedasPirata2) == entrada.num_monedas){
			if(abs(datos.valorPirata1 - datos.valorPirata2) == min_diff){
				num_formas++;
			}else if(abs(datos.valorPirata1 - datos.valorPirata2) < min_diff){
				min_diff = abs(datos.valorPirata1 - datos.valorPirata2);
				num_formas = 1;
			}
		}
	Caso Recursivo:
		else{
			for(int i = (datos.monedasPîrata1 + datos.numMonedasPirata2); i < num_monedas; i++){
				if(datos.numMonedasPirata1 - datos.numMonedasPirata2 == 0){
					//Agregar moneda a pirata 1
						datos.numMonedasPirata1++;
						datos.valorPîrata1 += entrada.valor_monedas[i];
						reparte_aux(entrada, datos, min_diff, num_formas);
						datos.numMonedasPirata1--;
						datos.valorPîrata1 -= entrada.valor_monedas[i];
					//Agregar moneda a pirata 2
						datos.numMonedasPirata2++;
						datos.valorPîrata2 += entrada.valor_monedas[i];
						reparte_aux(entrada, datos, min_diff, num_formas);
						datos.numMonedasPirata2--;
						datos.valorPîrata2 -= entrada.valor_monedas[i];
				}else{
					if(datos.numMonedasPirata1 > datos.numMonedasPirata2){
						datos.numMonedasPirata2++;
						datos.valorPîrata2 += entrada.valor_monedas[i];
						reparte_aux(entrada, datos, min_diff, num_formas);
						datos.numMonedasPirata2--;
						datos.valorPîrata2 -= entrada.valor_monedas[i];
					}else{
						datos.numMonedasPirata1++;
						datos.valorPîrata1 += entrada.valor_monedas[i];
						reparte_aux(entrada, datos, min_diff, num_formas);
						datos.numMonedasPirata1--;
						datos.valorPîrata1 -= entrada.valor_monedas[i];
					}
				}
			}
		}
(8) Si el algoritmo utiliza una generalizacion, describe como se implementa el algoritmo
    en terminos de la misma (inmersion)
	min_diff = sumMonedas(entrada);
	num_formas = 0;
	datos = {0, 0, 0, 0};
	reparte_aux(entrada, datos, min_diff, num_formas)
*/
/* 
- En min_dif debe devolverse la minima diferencia que puede conseguirse.
- En num_formas debe devolverse el numero de soluciones que presentan dicha diferencia minima.
*/

void agregaAPirata(const tEntrada& entrada, tDatos& datos, int pos, int pirata){
	if(pirata == 1){
		datos.monedasPirata1[datos.numMonedasPirata1] = pos;
		datos.numMonedasPirata1++;
		datos.valorPirata1 += entrada.valor_monedas[pos];
	}else if(pirata == 2){
		datos.monedasPirata2[datos.numMonedasPirata2] = pos;
		datos.numMonedasPirata2++;
		datos.valorPirata2 += entrada.valor_monedas[pos];
	}
}

void quitaAPirata(const tEntrada& entrada, tDatos& datos, int pos, int pirata){
	if(pirata == 1){
		datos.numMonedasPirata1--;
		datos.valorPirata1 -= entrada.valor_monedas[pos];
		datos.monedasPirata1[datos.numMonedasPirata1] = -1;
	}else if(pirata == 2){
			datos.numMonedasPirata2--;
			datos.valorPirata2 -= entrada.valor_monedas[pos];
			datos.monedasPirata2[datos.numMonedasPirata2] = -1;
	}
}

bool monedaYaAgregada(const tEntrada& entrada, tDatos& datos, int pos){
	for(int i = 0; i < datos.numMonedasPirata1; i++){
		if(datos.monedasPirata1[i] == pos){ //Si el pirata 1 tiene la moneda devuelve true
			return true;
		}
	}
	for(int i = 0; i < datos.numMonedasPirata2; i++){
		if(datos.monedasPirata2[i] == pos){ //Si el pirat 2 tiene la moneda devuelve true
			return true;
		}
	}
	return false; //Si no se encuentra la moneda devuelve false
}

int sumMonedas(const tEntrada& entrada){ //Acota el valor minimo de suma para el inicio
	int suma = 0;
	for(int i = 0; i < entrada.num_monedas; i++){
		suma += entrada.valor_monedas[i];
	}
	return suma;
}

void reparte_aux(const tEntrada& entrada, tDatos& datos, int monedaActual, int& min_dif, int& num_formas){
	if((datos.numMonedasPirata1 + datos.numMonedasPirata2) == entrada.num_monedas){ //Si ya se han repartido todas las monedas
		if(datos.numMonedasPirata1 >= entrada.min_monedas && datos.numMonedasPirata2 >= entrada.min_monedas){ //Si los dos piratas tienen el minimo de monedas
			if(abs(datos.valorPirata1 - datos.valorPirata2) == min_dif){ //La diferencia de valores es igual a la diferencia minima
				num_formas++;
			}else if(abs(datos.valorPirata1 - datos.valorPirata2) < min_dif){ //Hay nueva diferencia minima -> Se actualiza la dif. minima y resetea el contador de soluciones
				min_dif = abs(datos.valorPirata1 - datos.valorPirata2);
				num_formas = 1;
			}
		}
	}else{
		if(datos.numMonedasPirata1 == datos.numMonedasPirata2){ //Tienen la misma cantidad de monedas
			//Prueba la combinacion para el pirata 1
			agregaAPirata(entrada, datos, monedaActual, 1);//Agregar moneda a pirata 1
			reparte_aux(entrada, datos, monedaActual + 1, min_dif, num_formas);
			quitaAPirata(entrada, datos, monedaActual, 1);//Restaura al estado anterior
			//Prueba la combinacion para el pirata 2
			agregaAPirata(entrada, datos, monedaActual, 2);//Agregar moneda a pirata 2
			reparte_aux(entrada, datos, monedaActual + 1, min_dif, num_formas);
			quitaAPirata(entrada, datos, monedaActual, 2);//Restaura al estado anterior
		}else{
			if(datos.numMonedasPirata1 <= entrada.num_monedas/2){
				agregaAPirata(entrada, datos, monedaActual, 1);//Agregar moneda a pirata 1
				reparte_aux(entrada, datos, monedaActual + 1, min_dif, num_formas);
				quitaAPirata(entrada, datos, monedaActual, 1);//Restaura al estado anterior
			}
			if(datos.numMonedasPirata2 <= entrada.num_monedas/2){
				agregaAPirata(entrada, datos, monedaActual, 2);//Agregar moneda a pirata 2
				reparte_aux(entrada, datos, monedaActual + 1, min_dif, num_formas);
				quitaAPirata(entrada, datos, monedaActual, 2);//Restaura al estado anterior
			}
		}
	}
}

void reparte(const tEntrada& entrada, int& min_dif, int& num_formas) {
	min_dif = sumMonedas(entrada);
	num_formas = 0;
	tDatos datos = {0, 0, 0, 0};
	reparte_aux(entrada, datos, 0, min_dif, num_formas);
}

/**** PROGRAMA DE PRUEBA: NO MODIFICAR ****/

 bool ejecuta_caso() {
	 int num_monedas;
	 cin >> num_monedas;
	 if (num_monedas == -1) return false;
	 else {
		 tEntrada entrada;
		 entrada.num_monedas = num_monedas;
		 cin >> entrada.min_monedas;
		 for (int m = 0; m < num_monedas; m++) {
			 cin >> entrada.valor_monedas[m];
		 }
		 int min_dif;
		 int num_formas;
		 reparte(entrada, min_dif, num_formas);
		 cout << min_dif << " " << num_formas << endl;
		 return true;
	 }
 }

 int main() {
	 while (ejecuta_caso());
	 return 0;
 }