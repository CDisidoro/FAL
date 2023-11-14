
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
    n es el numero que estamos operando
    T(n) = C0 (Caso Base, n <= 9)
    T(n) = C1 + T(n/10) (Caso Recursivo, n > 9)
    a = 1
    b = 10
    k = 0
    b^k = 10^0 = 1
    a = b^k
    Complejidad O(n^k log n) = O(n^0 log n) = O(log n)
*/
bool esDivisor(const int &digito, const long long int &valor){
    return (digito != 0) && (valor % digito == 0);
}

pair<bool, int> es_interesante_aux(const unsigned int &n, const long long int &sumDerecha){
    //Caso Base
    /*Para este caso si solo tenemos un digito, si ese digito no es cero y la suma de 
    todo lo que este a la derecha de ese digito es divisible por este, acumulara el digito
    a la suma izquierda y determinara que el numero es interesante.
    En caso contrario determinara que no lo es y las recursiones terminaran dando false*/
    if(n <= 9){
        if(esDivisor(n, sumDerecha)){
            return {true, n};
        }else{
            return {false, n};
        }
    }else{ //Caso Recursivo
        auto next = es_interesante_aux(n / 10, sumDerecha + (n % 10));
        if(!next.first || !esDivisor(n%10, sumDerecha) || !esDivisor(n%10, next.second)){
            return {false, 0};
        }else{
            return {true, next.second + (n % 10)};
        }
    }
}

bool es_interesante(const unsigned int &n) {
    return es_interesante_aux(n, 0).first;
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
