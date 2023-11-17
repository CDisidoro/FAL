/*
NOMBRES Y APELLIDOS DE LOS MIEMBROS DEL GRUPO QUE HAN REALIZADO LA PRACTICA:
    CAMILO ANDRES D'ISIDORO
    JUAN ISRAEL BAROFFI GONZALEZ
Si alguno de los miembros del grupo no ha realizado
la practica, indicarlo aqui, junto con el motivo:


*/

#include <iostream>

using namespace std;


/* Representacion de los personajes */
typedef enum {PRINCESA,CABALLERO,DRAGON} tPersonaje;

typedef struct{
    bool divertido;
    int numCaballero;
    int numDragon;
    int numPrincesa;
}tSol;
/*
(1) GENERALIZACION (EN CASO DE QUE PROCEDA): Entradas y salidas
    ENTRADAS:
        tPersonaje personajes[]
        int ini
        int fin

    SALIDAS:
        tSol solucion:
            bool divertido
            int numCaballero
            int numDragon
            int numPrincesa

    tSol es_divertida_aux(tPersonaje personaje[], int ini, int fin);

(2) DISEÑO

    CASO BASE ((fin - ini) <= 0): //Hay menos de dos personajes
        switch(p[ini]){
            case CABALLERO:
                numPrincesa = 0;
                numCaballero = 1;
                numDragon = 0;
                break;
            case DRAGON:
                numPrincesa = 0;
                numCaballero = 0;
                numDragon = 1;
                break;
            case PRINCESA:
                numPrincesa = 1;
                numCaballero = 0;
                numDragon = 0;
                break;
        }
        return {true, numCaballero, numDragon, numPrincesa};
    CASO RECURSIVO ((fin - ini) > 0): //Hay mas de dos personajes
        int medio = (fin + ini) / 2;
        mitadInf = es_divertida_aux(p, ini, medio - 1);
        mitadSup = es_divertida_aux(p, medio + 1, fin);
        esDivertido = ( (mitadInf.numDragon > mitadSup.numCaballero && p[medio] == CABALLERO) || 
                           (mitadInf.numDragon == mitadSup.numCaballero && p[medio] == PRINCESA) ||
                           (mitadInf.numDragon < mitadSup.numCaballero && 
                                (mitadInf.numPrincesa + mitadSup.numPrincesa > 0 && p[medio] == DRAGON) ||
                                (mitadInf.numPrincesa + mitadSup.numPrincesa == 0 && p[medio] == PRINCESA) )
                            && (mitadInf.divertido && mitadSup.divertido) );
        numCaballero = mitadInf.numCaballero + mitadSup.numCaballero;
        numDragon = mitadInf.numDragon + mitadSup.numDragon;
        numPrincesa = mitadInf.numPrincesa + mitadSup.numPrincesa;
        switch(p[medio]){
            case CABALLERO:
                numCaballero++;
                break;
            case DRAGON:
                numDragon++;
                break;
            case PRINCESA:
                numPrincesa++;
                break;
        }
        return {esDivertido, numCaballero, numDragon, numPrincesa};
(3) TERMINACION: 
    fin - ini, porque estamos filtrando casos y reduciendo fin o aumentando ini hasta que seran iguales y llegan al caso base
(4) IMPLEMENTACION POR INMERSION DEL ALGORITMO, SI PROCEDE:

(5) DETERMINACION DEL COSTE DEL ALGORITMO EN EL PEOR CASO:
    T(0) = C0, (fin - ini <= 0)
    T(n) = C1 + 2T(n/2)
    a = 2
    b = 2
    k = 0
    b^k = 1
    a > b^k => 2 > 1
    O(n^log_2 2) = O(n)
*/
tSol es_divertida_aux(tPersonaje p[], int ini, int fin){
    bool esDivertido;
    int numCaballero, numDragon, numPrincesa;
    if((fin - ini) <= 0){
        switch(p[ini]){
            case CABALLERO:
                numPrincesa = 0;
                numCaballero = 1;
                numDragon = 0;
                break;
            case DRAGON:
                numPrincesa = 0;
                numCaballero = 0;
                numDragon = 1;
                break;
            case PRINCESA:
                numPrincesa = 1;
                numCaballero = 0;
                numDragon = 0;
                break;
        }
        return {true, numCaballero, numDragon, numPrincesa};
    }else{
        tSol mitadInf, mitadSup;
        int medio = (fin + ini) / 2;
        mitadInf = es_divertida_aux(p, ini, medio - 1);
        mitadSup = es_divertida_aux(p, medio + 1, fin);
        esDivertido = ( (mitadInf.numDragon > mitadSup.numCaballero && p[medio] == CABALLERO) || 
                           (mitadInf.numDragon == mitadSup.numCaballero && p[medio] == PRINCESA) ||
                           (mitadInf.numDragon < mitadSup.numCaballero && 
                                (mitadInf.numPrincesa + mitadSup.numPrincesa > 0 && p[medio] == DRAGON) ||
                                (mitadInf.numPrincesa + mitadSup.numPrincesa == 0 && p[medio] == PRINCESA) )
                            && (mitadInf.divertido && mitadSup.divertido) );
        numCaballero = mitadInf.numCaballero + mitadSup.numCaballero;
        numDragon = mitadInf.numDragon + mitadSup.numDragon;
        numPrincesa = mitadInf.numPrincesa + mitadSup.numPrincesa;
        switch(p[medio]){
            case CABALLERO:
                numCaballero++;
                break;
            case DRAGON:
                numDragon++;
                break;
            case PRINCESA:
                numPrincesa++;
                break;
        }
        return {esDivertido, numCaballero, numDragon, numPrincesa};
    }
}

bool es_divertida(tPersonaje personajes[], int n) {
	return es_divertida_aux(personajes, 0, n - 1).divertido;
}

// NO MODIFICAR NADA A PARTIR DE AQUI

const int MAX_TAM = 1000000;
const int REPS = 500;

bool ejecuta_caso() {
  int n;
  cin >> n;
  if (n== -1) {
    return false;
  }
  else {
    static tPersonaje personajes[MAX_TAM];
	for (int i = 0; i < n; i++) {
		int p;
	    cin >> p;
		personajes[i] = tPersonaje(p);
     }
	
	if(n == MAX_TAM) {
	 for (int i=0; i < REPS; i++) {
	   es_divertida(personajes,n);
	 }
	}
	if (es_divertida(personajes,n)) {
	  cout << "SI" << endl;
	}
	else {
	  cout << "NO" << endl;
	}
	return true;
  }
}

int main() {
  while(ejecuta_caso());
  return 0;
}