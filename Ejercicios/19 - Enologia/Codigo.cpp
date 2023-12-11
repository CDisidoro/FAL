
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

*/

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