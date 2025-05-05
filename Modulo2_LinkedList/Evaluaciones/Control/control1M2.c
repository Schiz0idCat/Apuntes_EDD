#include <stdlib.h>

struct Evaluacion {
	int id;
	char *fecha;
	int nota;
};

struct Alumno {
	char *rut;
	char *nombre;
	struct Evaluacion **evaluaciones;
	int tam;
};

struct NodoAlumno { // lista simplemente enlazada
	struct Alumno *datoAlumno;
	struct NodoAlumno *sig;
};

struct Curso {
	int sigla;
	struct NodoAlumno *head;
};

float promedio(struct Evaluacion **notas, int max) {
	int i, suma = 0;

	for (i = 0; i < max; i++) {
		if (notas[i] == NULL)
			suma += 1;
		else
			suma += notas[i]->nota;
	}

	return (float)suma / (float)max;
}

int calcularCantidadAprobados(struct Curso *curso, float umbral) {
	int total = 0;
	struct NodoAlumno *rec = curso->head;

	while (rec != NULL) {
		if (promedio(rec->datoAlumno->evaluaciones, rec->datoAlumno->tam) >= umbral)
			total++;

		rec = rec->sig;
	}

	return total;
}