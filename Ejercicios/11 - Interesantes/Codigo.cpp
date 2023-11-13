
#include <iostream>
using namespace std;

/*
DISEÑO DEL ALGORITMO:
-- Describe con claridad, justificando las decisiones de diseño realizadas,
-- el funcionamiento de tu algoritmo. Especifica claramente el cometido de cada 
-- parametro (en caso de que utilices una generalizacion), los casos base, y los 
-- casos recursivos
    es_interesante_aux(n, interesante, sumDerecha, sumIzquierda)
    interesante = Comprueba que el numero sigue siendo interesante o no
    sumDerecha = Suma de los digitos a la parte de la derecha del digito a comprobar
    sumIzquierda = Suma de los digitos en la parte izquierda del digito a comprobar
    Vamos dividiendo el numero entre 10 y sumando los digitos que vamos quitando en sumDerecha
    hasta llegar a un digito, que comprobara si es interesante o no y si lo es aumentara la sumIzquierda
    con el digito faltante
    Luego a medida que sube en la recursion se comprueba si sumDerecha-Digito % digito y sumIzquierda%Digito son cero,
    y que el digito sea distinto de cero. Si se cumplen las condiciones el numero es interesante, y el digito
    que hemos revisado lo sumamos a sumIzquierda y restamos de sumDerecha hasta terminar la recursion

ANALISIS DE LA COMPLEJIDAD:
-- Determina justificadamente el orden de complejidad del algoritmo diseñado.
-- Escribe y resuelve las ecuaciones de recurrencia.
    T(n) = C0 (Caso Base, n <= 9)
    T(n) = C1 + T(n/10) (Caso Recursivo, n > 9)
    a = 1
    b = 10
    k = 0
    b^k = 10^0 = 1
    a = b^k
    Complejidad O(n^k log n) = O(n^0 log n) = O(log n)
*/

bool es_interesante_aux(unsigned int n, bool &interesante, int &sumDerecha, int &sumIzquierda){
    //Caso Base
    /*Para este caso si solo tenemos un digito, si ese digito no es cero y la suma de 
    todo lo que este a la derecha de ese digito es divisible por este, acumulara el digito
    a la suma izquierda y determinara que el numero es interesante.
    En caso contrario determinara que no lo es y las recursiones terminaran dando false*/
    if(n <= 9){
        if(n != 0 && sumDerecha % n == 0){
            sumIzquierda = n;
            interesante = true;
        }else{
            sumIzquierda = 0;
            interesante = false;
        }
    }else{ //Caso Recursivo
        /*A medida que vamos reduciendo el numero vamos comprobando la parte derecha del numero.
        Si el digito es cero o la suma de la parte derecha no es divisible por el digito, harcodea
        la suma izquierda a cero y retorna interesante como falso.*/
        if((n % 10) == 0 || sumDerecha % (n % 10) != 0){
            sumIzquierda = 0;
            interesante = false;
        }else{
            /*En caso contrario acumula a la suma derecha el digito evaluado, hara la llamada recursiva
            y revisara si una vez hecha la recursion el numero es interesante, el digito a revisar no es cero y
            que la suma izquierda sea divisible por el digito. Si se cumple el caso, acumula el digito a la suma izquierda
            y pone interesante como true. Sino, sera false y harcodea suma izquierda a cero*/
            sumDerecha = sumDerecha + (n % 10);
            es_interesante_aux(n / 10, interesante, sumDerecha, sumIzquierda);
            if(interesante && (n % 10) != 0 && (sumIzquierda % (n % 10) == 0) ){
                sumIzquierda += (n % 10);
                interesante = true;
            }else{
                sumIzquierda = 0;
                interesante = false;
            }
        }
    }
    return interesante;
}

bool es_interesante(unsigned int n) {
	bool interesante;
    int sumDerecha, sumIzquierda;
    return es_interesante_aux(n, interesante, sumDerecha, sumIzquierda);
}

void ejecuta_caso() {
	unsigned int n;
	cin >> n;
	if (es_interesante(n)) {
		cout << "SI" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

int main() {
	unsigned int num_casos;
	cin >> num_casos;
	for (int i = 0; i < num_casos; i++) {
		ejecuta_caso();
    }
}