#include <iostream>
#include <algorithm>
using namespace std;

/*
(1) Precondición
    P = { 0 < n <= tam(v) }
(2) Postcondición
	numPares(v, ini, fin) = #i: 0 <= ini <= i <= fin < n: v[i] % 2 = 0
	sumPares(v, ini, fin) = Sum i: 0 <= ini <= i <= fin < n ^ v[i] % 2 = 0: v[i]
	numImpares(v, ini, fin) = #i: 0 <= ini <= i <= fin < n: v[i] % 2 != 0
	sumImpares(v, ini, fin) = #i: 0 <= ini <= i <= fin < n ^ v[i] % 2 != 0: v[i]
    parcurioso(v, ini, fin) = numPares(v, 0, n/2) <= numImpares(v, n/2 + 1, n) ^
							  sumPares(v, 0, n/2) <= sumImpares(v, n/2 + 1, n) ^
							  (parcurioso(v, 0, n/2) v parcurioso(v, n/2 + 1, n)):
							  0 <= ini <= fin < n
	Q = { resul = parcurioso(v, 0, n) }
(3) Si vas a utilizar una generalización, especificación
    pre-pos de la generalización
	P = {0 <= ini <= fin <= tam(v)}
	tSol es_parcurioso_aux(v, ini, fin);
	Q = { tSol.result = parcurioso(v, ini, fin),
		  tSol.numPares = numPares(v, ini, fin),
		  tSol.numImpares = numImpares(v, ini, fin),
		  tSol.sumPares = sumPares(v, ini, fin),
		  tSol.sumImpares = sumImpares(v, ini, fin) }
(4) Casos no recursivos
	(fin - ini) + 1 = 1:
		tSol.result = true
		if(v[ini] % 2 == 0){
			tSol.numPares = 1;
			tSol.sumPares = v[ini];
			tSol.numImpares = 0;
			tSol.sumImpares = 0;
		}else{
			tSol.numPares = 0;
			tSol.sumPares = 0;
			tSol.numImpares = 1;
			tSol.sumImpares = v[ini];
		}
		return tSol;
(5) Casos recursivos
	(fin - ini) + 1 > 1
		solIzq = es_parcurioso_aux(v, ini, (ini + fin) / 2)
		solDer = es_parcurioso_aux(v, ((ini + fin) / 2) + 1, fin)
		tSol.resul = solIzq.numPares <= solDer.numImpares ^ solIzq.sumPares <= solDer.sumImpares ^
		(solIzq.result v solDer.result)
		tSol.numPares = solIzq.numPares + solDer.numPares;
		tSol.sumPares = solIzq.sumPares + solDer.sumPares;
		tSol.numImpares = solIzq.numImpares + solDer.numImpares;
		tSol.sumImpares = solIzq.sumImpares + solDer.sumImpares;
		return tSol;
(6) Terminación (expresión de cota)

(7) Si has usado una generalización, definición por
    inmersión de es_paracurioso

(8) Determinación de la complejidad (recurrencias y su resolución)
	T(1) = C0 (Caso Base)
	T(n) = C1 + 2T(n/2) (Caso Recursivo)
	a = 2
	b = 2
	k = 0
	b^k = 1
	2 > 1
	O(n^log_2 2) = O(n)
*/
typedef struct{
	bool result;
	int numPares, sumPares, numImpares, sumImpares;
}tSol;

tSol es_parcurioso_aux(const int v[], const unsigned int &ini, const unsigned int &fin){
	if((fin - ini) + 1 == 1){ //Caso Base
		if(v[ini] % 2 == 0){
			return {true, 1, v[ini], 0, 0};
		}else{
			return {true, 0, 0, 1, v[ini]};
		}
	}else{//Caso Recursivo
		tSol solIzq = es_parcurioso_aux(v, ini, (ini + fin) / 2);
		tSol solDer = es_parcurioso_aux(v, ((ini + fin) / 2) + 1, fin);
		bool result = 	(solIzq.numPares <= solDer.numImpares) &&
						(solIzq.sumPares <= solDer.sumImpares) &&
						(solIzq.result || solDer.result);
		return {result,
				solIzq.numPares + solDer.numPares,
				solIzq.sumPares + solDer.sumPares,
				solIzq.numImpares + solDer.numImpares,
				solIzq.sumImpares + solDer.sumImpares};
	}
}

bool es_parcurioso(int v[], int n) {
	return es_parcurioso_aux(v, 0, n - 1).result;
}

// NO MODIFICAR

const static int MAX_ELEMENTS = 100000;

void ejecuta_caso() {
		static int v[MAX_ELEMENTS];
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		if (es_parcurioso(v, n)) {
			cout << "SI" << endl;;
		}
		else {
			cout << "NO" << endl;
		}
}


int main() {
	int n;
	cin >> n;
	for (int i=0; i < n; i++)
	  ejecuta_caso();
	return 0;
}