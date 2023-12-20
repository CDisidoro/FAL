
#include <iostream>
using namespace std;

const unsigned int MAX_CLIENTES = 10; // maximo numero de clientes
  // Representacion de la matriz de afinidades
typedef struct {
	unsigned int n_clientes;                              // numero de clientes. 
	unsigned int afinidades[MAX_CLIENTES][MAX_CLIENTES];  // la matriz se almacena en las 'n_clientes' primeras filas,
	                                                      // 'n_clientes' primeras columnas	                                                      
} tMatrizAfinidad;
/*

(1) En caso de utilizar una generalizacion, indicar su parametros, y explicar para que
sirven cada uno de ellos
	afinidades[MAX_CLIENTES][MAX_CLIENTES] (Entrada): Matriz de afinidades de los clientes
	num_cliente (Entrada): Numero de cliente que estamos comprobando
	parejas[MAX_CLIENTES] (Entrada): Lista de parejas construidas hasta ahora
	hay_pareja (Entrada/Salida): Indica si hemos encontrado ya una pareja
	mejor_pareja[MAX_CLIENTES] (Entrada): Guarda la mejor combinacion de parejas halladas
	total_clientes (Entrada): Cantidad total de clientes
(2) Como son las soluciones parciales de este problema?
	Un emparejamiento de X cantidad de clientes
(3) Cuando una solucion parcial es viable?
	Cuando en el emparejamiento no hay parejas que se llevan mal (afinidad = 0)
(4) Cuando una solucion parcial es una solucion final al problema?
	Cuando todos los clientes hayan sido emparejados
(5) Dada una solucion parcial, como se generan las siguientes soluciones
parciales viables?
	Intentas emparejar a un cliente X con los clientes que no estén emparejados y pruebas para cada caso
(6) Analisis de casos
	(6.1) Caso(s) base
		if (num_cliente == total_clientes){
			if (!hay_pareja || (afinidad(afinidades, parejas, total_clientes) > afinidad(afinidades, mejor_pareja, total_clientes))){
				actualiza_parejas(parejas, mejor_pareja, total_clientes);
				hay_pareja = true;
			}
		}
	(6.2) Caso(s) recursivos
		else{
			for (unsigned int cliente = 0; cliente < total_clientes; cliente++){
				if (!contiene(parejas, num_cliente, cliente)){
					parejas[num_cliente] = cliente;
					encuentra_pareja(afinidades, num_cliente + 1, parejas, hay_pareja, mejor_pareja, total_clientes);
				}
			}
		}
(7) En caso de utilizar una generalizacion, explicar como se define el algoritmo final
a partir de la misma, por inmersion.
	encuentra_pareja(as.afinidades, 1, total_parejas, hay_pareja, mejor_pareja, as.n_clientes);
	return afinidad(as.afinidades, mejor_pareja, as.n_clientes);
*/

bool contiene(int parejas[MAX_CLIENTES], unsigned int n, int cliente){
    bool enc = false;
    unsigned int c = 0;
    while (!enc && c < n){
        enc = parejas[c] == cliente;
        c++;
    }
    return enc;
}

void actualiza_parejas(int parejas[MAX_CLIENTES], int mejor_parejas[MAX_CLIENTES], int total_clientes){
    for (int client = 0; client < total_clientes; client++){
        mejor_parejas[client] = parejas[client];
    }
}

int afinidad(const unsigned int afinidades[MAX_CLIENTES][MAX_CLIENTES], int parejas[MAX_CLIENTES], unsigned int total_clientes){
    int k = 0;
    bool hay_pareja = true;
    unsigned int i = 1;
    while (hay_pareja && i <= total_clientes - 1){
        if (afinidades[parejas[i]][parejas[i - 1]] == 0 || afinidades[parejas[i - 1]][parejas[i]] == 0){
            hay_pareja = false;
        }
        k += afinidades[parejas[i]][parejas[i - 1]] + afinidades[parejas[i - 1]][parejas[i]];
        i += 2;
    }
    return hay_pareja ? k : 0;
}

void encuentra_pareja(const unsigned int afinidades[MAX_CLIENTES][MAX_CLIENTES], unsigned int num_cliente, int parejas[MAX_CLIENTES], bool &hay_pareja, int mejor_pareja[MAX_CLIENTES], unsigned int total_clientes){
    if (num_cliente == total_clientes){
        if (!hay_pareja || (afinidad(afinidades, parejas, total_clientes) > afinidad(afinidades, mejor_pareja, total_clientes))){
            actualiza_parejas(parejas, mejor_pareja, total_clientes);
            hay_pareja = true;
        }
    }
    else{
        for (unsigned int cliente = 0; cliente < total_clientes; cliente++){
            if (!contiene(parejas, num_cliente, cliente)){
                parejas[num_cliente] = cliente;
                encuentra_pareja(afinidades, num_cliente + 1, parejas, hay_pareja, mejor_pareja, total_clientes);
            }
        }
    }
}

int maxima_afinidad(const tMatrizAfinidad &as)
{
    // Punto de entrada al algoritmo: as representa la matriz de afinidades
    // (ver definicion de tMatrizAfinidad). Una vez finalizado el algoritmo,
    // debera devolverse el valor pedido. Pueden definirse todas las
    // funciones auxiliares que se considere oportuno.
	if (as.n_clientes <= 0 || as.n_clientes % 2 != 0){
        return 0;
    }
    int mejor_pareja[MAX_CLIENTES];
    int total_parejas[MAX_CLIENTES];
    bool hay_pareja = false;
    total_parejas[0] = 0;
    encuentra_pareja(as.afinidades, 1, total_parejas, hay_pareja, mejor_pareja, as.n_clientes);
    return afinidad(as.afinidades, mejor_pareja, as.n_clientes);
}


void ejecuta_caso() {
	tMatrizAfinidad as;
	cin >> as.n_clientes;
	for (unsigned int i = 0; i < as.n_clientes; i++) {
		for (unsigned int j = 0; j < as.n_clientes; j++) {
			cin >> as.afinidades[i][j];
		}
	}
	cout << maxima_afinidad(as) << endl;
}


int main() {
	unsigned int num_casos;
	cin >> num_casos;
	for (unsigned int i = 0; i < num_casos; i++) {
		ejecuta_caso();
	}
}