#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Evaluacion {
	int id;
	char *fecha;
	int nota;
};

struct Alumno {
	char *rut;
	char *nombre;
	struct Evaluacion **evaluaciones; // no compacto
	int tam;
};

struct NodoAlumno {
	struct Alumno *dataAlumno;
	struct NodoAlumno *sig;
};

struct Curso {
	int sigla;
	struct NodoAlumno *head;
};

struct NodoAlumno *crearNodo(struct Alumno *alumno) {
	struct NodoAlumno *nuevo = (struct NodoAlumno *)malloc(sizeof(struct NodoAlumno));

	if (nuevo == NULL) return NULL;

	nuevo->dataAlumno = alumno;
	nuevo->sig = NULL;

	return nuevo;
}

int enlazarNodo(struct NodoAlumno **head, struct NodoAlumno *nuevo) {
	if (*head == NULL) { // la lista está vacía
		*head = nuevo;

		return 0;
	}

	struct NodoAlumno *rec = *head;

	while (rec->sig != NULL) // se llega al último elemento
		rec = rec->sig;

	rec->sig = nuevo;

	return 0;
}

struct Alumno *buscarAlumno(struct NodoAlumno *head, char *rut) {
	while (head != NULL) {
		if (strcmp(head->dataAlumno->rut, rut) == 0)
			return head->dataAlumno;

		head = head->sig;
	}

	return NULL;
}

int agregarAlumno(struct NodoAlumno **head, struct Alumno *nuevoAlumno) {
	struct Alumno *alumnoAux = buscarAlumno(*head, nuevoAlumno->rut);

	if (alumnoAux != NULL) return 1; // se econtró al alumno, no se agrega

	enlazarNodo(head, crearNodo(nuevoAlumno));

	return 0;
}

struct Alumno *quitarAlumno(struct NodoAlumno **head, char *rut) {
	struct NodoAlumno *act = *head, *prev = NULL;

	if (strcmp((*head)->dataAlumno->rut, rut) == 0) {
		*head = act->sig;

		return act->dataAlumno;
	}

	while (act != NULL && strcmp(act->dataAlumno->rut, rut) != 0) {
		prev = act;
		act = act->sig;
	}

	if (act == NULL) return NULL;

	prev->sig = act->sig;

	return act->dataAlumno;
}

float promedio(struct Evaluacion **evaluaciones, int tam) {
	int i, totalPuntaje, cantidadEvaluaciones;

	totalPuntaje = 0;
	cantidadEvaluaciones = 0;

	for (i = 0; i < tam; i++) {
		if (evaluaciones[i] != NULL) {
			totalPuntaje += evaluaciones[i]->nota;
			cantidadEvaluaciones++;
		}
	}

	if (cantidadEvaluaciones <= 0) return 0.0f;

	return (float)totalPuntaje / (float)cantidadEvaluaciones;
}

struct Alumno *getAlumnoPeorPromedio(struct NodoAlumno *head) {
	struct NodoAlumno *rec = head;
	struct Alumno *alumnoPeorPromedio = NULL;
	float peorPromedio = 0.0f;

	while (rec != NULL) {
		struct Alumno *alumno = rec->dataAlumno;

		if (alumnoPeorPromedio == NULL || promedio(alumno->evaluaciones, alumno->tam) < peorPromedio) {
			alumnoPeorPromedio = rec->dataAlumno;
			peorPromedio = promedio(alumno->evaluaciones, alumno->tam);
		}

		rec = rec->sig;
	}

	return alumnoPeorPromedio;
}

struct Alumno *quitarAlumnoPeorPromedio(struct NodoAlumno **head) {
	struct Alumno *alumnoPeorPromedio = getAlumnoPeorPromedio(*head);

	if (alumnoPeorPromedio == NULL) return NULL;

	return quitarAlumno(head, alumnoPeorPromedio->rut);
}