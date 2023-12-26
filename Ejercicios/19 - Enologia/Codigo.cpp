#include <iostream>
using namespace std;

/* Estructura utilizada para almacenar la información de un tema */
typedef struct {
	float tiempo_req;  // tiempo requerido para estudiar el tema
	float nota_prim;   // aportación a la nota de la primera parte
	float nota_sec;    // aportación a la nota de la segunda parte
} tInfoTema;
/*
DISEÑO DEL ALGORITMO

Para superar este ejercicio, aparte de programar el algoritmo, debes
describir aqui detalladamente su diseño (parámetros y variables utilizados,
y su cometido, cometido de los resultados devueltos por las funciones,
idea general del algoritmo, estructura de las soluciones,
análisis de casos, acciones realizadas para cada caso...)
	posActual (Entrada): Posicion actual en la lista de temas
	sumNota1 (Entrada): Suma de nota de la primera parte del examen
	sumNota2 (Entrada): Suma de nota de la segunda parte del examen
	tiempo_usado (Entrada): Tiempo de estudio utilizado
	max_nota (Entrada/Salida): Nota maxima obtenible
	La funcion mejor_puntuacion_aux retorna en la variable de entrada/salida max_nota la nota máxima obtenible, esto se hace siguiendo esta idea:

	Como caso base si hemos llegado al final de la lista de temas a estudiar, comprobamos si la suma de nota de las dos partes es >= 5,
	y si la media con las sumas de notas actuales supera la nota maxima hallada hasta ahora, entonces actualizara la nota maxima.

	En caso de no haber llegado al final de la lista, comprobamos la mejor puntuacion sin estudiar el tema en posActual, y luego de volver de ese caso
	estudiamos si con el tiempo que hemos usado hasta ahora más el que implica estudiar el tema en posActual nos queda tiempo disponible. De ser el caso,
	hacemos marcaje sumando las notas correspondientes y el tiempo usado y llamando a la recursión, y al volver de esta deshacemos el marcaje
*/
void mejor_puntuacion_aux(const tInfoTema info_temas[], unsigned int num_temas, float tiempo_disponible, unsigned int posActual, float sumNota1, float sumNota2, float tiempo_usado, float& maxNota) {
	if (posActual == num_temas) {
		if (sumNota1 >= 5 && sumNota2 >= 5 && ((sumNota1 + sumNota2) / 2) > maxNota) {
			maxNota = (sumNota1 + sumNota2) / 2;
		}
	}else {
		mejor_puntuacion_aux(info_temas, num_temas, tiempo_disponible, posActual + 1, sumNota1, sumNota2, tiempo_usado, maxNota);
		if ((tiempo_usado + info_temas[posActual].tiempo_req) <= tiempo_disponible) {
			sumNota1 += info_temas[posActual].nota_prim;
			sumNota2 += info_temas[posActual].nota_sec;
			tiempo_usado += info_temas[posActual].tiempo_req;
			mejor_puntuacion_aux(info_temas, num_temas, tiempo_disponible, posActual + 1, sumNota1, sumNota2, tiempo_usado, maxNota);
			sumNota1 -= info_temas[posActual].nota_prim;
			sumNota2 -= info_temas[posActual].nota_sec;
			tiempo_usado -= info_temas[posActual].tiempo_req;
		}
	}
}

/* temas: Información sobre los temas de los que consta el examen (ver tInfoTema)
   num_temas: Numero de temas de los que consta el examen -su información aparece
			  al principio de info_temas
   tiempo_disponible: Tiempo total disponible para realizar el examen.
   Valor devuelto: La puntuación media máxima que se puede conseguir, o -1 si no
				   es posible aprobar el examen */
float mejor_puntuacion(const tInfoTema info_temas[], unsigned int num_temas, float tiempo_disponible) {
	/* ESTA FUNCIÓN SERÁ EL PUNTO DE ENTRADA AL ALGORITMO. Puedes, después, utilizar las
	   funciones auxiliares que consideres oportuno, pero debes incluir la justificación para ello
	   en el comentario de descripción detallado del diseño de dicho algoritmo */
	float maxNota = -1;
	mejor_puntuacion_aux(info_temas, num_temas, tiempo_disponible, 0, 0, 0, 0, maxNota);
	return maxNota >= 10 ? 10 : maxNota;
}

/* Código para leer y ejecutar casos de prueba: no debe modificarse */
const unsigned int MAX_TEMAS = 20;

bool procesa_caso() {
	int num_temas;
	tInfoTema info_temas[MAX_TEMAS];
	cin >> num_temas;
	if (num_temas != -1) {
		float tiempo_disponible;
		cin >> tiempo_disponible;
		for (int i = 0; i < num_temas; i++) {
			cin >> info_temas[i].tiempo_req;
			cin >> info_temas[i].nota_prim;
			cin >> info_temas[i].nota_sec;
		}
		cout << mejor_puntuacion(info_temas, num_temas, tiempo_disponible) << endl;
		return true;
	}
	else {
		return false;
	}
}

int main() {
	while (procesa_caso());
}
