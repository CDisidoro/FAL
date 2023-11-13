
#include <iostream>

using namespace std;


/*
DISEÑO DEL ALGORITMO:
-- Describe con claridad, justificando las decisiones de diseño realizadas,
-- el funcionamiento de tu algoritmo. Especifica claramente el cometido de cada 
-- parámetro (en caso de que utilices una generalización), los casos base, y los 
-- casos recursivos
    sumdivisibleAux(n, &esSd', &numDigitos', &suma')
        n = Numero que se está comprobando
        esSd' = Validacion que el numero anterior es sumdivisible
        numDigitos' = Numero de digitos de la llamada recursiva
        suma' = Suma parcial de la llamada recursiva
    Caso Base (n <= 9):
        numDigitos = 1
        suma = n
        esSd = true
    Caso Recursivo (n > 9):
        numDigitos = numDigitos + numDigitos'
        suma = suma + suma'
        esSd = suma % numDigitos = 0 ^ esSd'

ANALISIS DE LA COMPLEJIDAD:
-- Determina justificadamente el orden de complejidad del algoritmo diseñado.
-- Escribe y resuelve las ecuaciones de recurrencia.
    T(0) = C0 (Caso Base)
    T(n) = C1 + T(n/10) (Caso Recursivo)
    a = 1
    b = 10
    k = 0
    b^k = 10^0 = 1
    a = b^k (1 = 1)
    Complejidad O(n^k log n) = O(n^0 log n) = O(log n)
*/

bool sumDivisibleAux(int n, bool &esSd, int &numDigitos, int &suma){
    //Caso Base
    if(n <= 9){
        numDigitos = 1;
        suma = n;
        esSd = true;
    }else{ //Caso Recursivo
        sumDivisibleAux(n / 10, esSd, numDigitos, suma);
        suma = suma + n % 10;
        numDigitos = numDigitos + 1;
        esSd = esSd && (suma % numDigitos == 0);
    }
    return esSd;
}

bool sumdivisible(int n) {
	int suma, numDigitos;
    bool esSd;
    return sumDivisibleAux(n, esSd, numDigitos, suma);
}   


/* CODIGO DE LECTURA Y EJECUCION DE CASOS DE PRUEBA: 
   NO MODIFICAR */

int main() {
	int n;
	do {
		cin >> n;
		if (n > 0) {
			if (sumdivisible(n)) 
				 cout << "SI" << endl;
			else 
                 cout << "NO" << endl;				
		}
	} while (n > 0);
}
	
	