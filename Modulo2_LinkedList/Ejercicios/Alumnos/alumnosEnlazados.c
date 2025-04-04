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
	if (alumno == NULL) return NULL;

	struct NodoAlumno *nuevo;

	nuevo = (struct NodoAlumno *)malloc(sizeof(struct NodoAlumno));

	if (nuevo == NULL) return NULL;

	nuevo->dataAlumno = alumno;
	nuevo->sig = NULL;

	return nuevo;
}

int enlazarNodo(struct NodoAlumno **head, struct NodoAlumno *nuevo) {
	if (head == NULL || nuevo == NULL) return 1;

	if (*head == NULL) { // la lista está vacía
		*head = nuevo;

		return 0;
	}

	struct NodoAlumno *rec;

	rec = *head;

	while (rec->sig != NULL) // se llega al último elemento
		rec = rec->sig;

	rec->sig = nuevo;

	return 0;
}

struct Alumno *buscarAlumno(struct NodoAlumno *head, char *rut) {
	if (head == NULL || rut == NULL) return NULL;

	while (head != NULL) {
		if (strcmp(head->dataAlumno->rut, rut) == 0)
			return head->dataAlumno;

		head = head->sig;
	}

	return NULL;
}

int agregarAlumno(struct NodoAlumno **head, struct Alumno *nuevoAlumno) {
	if (head == NULL || nuevoAlumno == NULL) return 1;

	struct NodoAlumno *nuevoNodo, *rec;
	struct Alumno *alumnoAux;

	alumnoAux = buscarAlumno(*head, nuevoAlumno->rut);

	if (alumnoAux != NULL) return 1; // se econtró al alumno, no se agrega

	enlazarNodo(head, crearNodo(nuevoAlumno));

	return 0;
}

struct Alumno *quitarAlumno(struct NodoAlumno **head, char *rut) {
	if (head == NULL || *head == NULL) return NULL;

	struct NodoAlumno *act, *prev;

	act = *head;
	prev = NULL;

	if (strcmp(act->dataAlumno->rut, rut) == 0) {
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

/*
float calcularPromedio(struct NodoAlumno *head, char *rut) { // esta fue la función promedio pedida en clases
	if (rut == NULL) return 0.0f;

	struct Alumno *alumno;

	alumno = buscarAlumno(head, rut);

	if (alumno == NULL || alumno->evaluaciones == NULL) return 0.0f;

	int i, totalPuntaje, cantidadEvaluaciones;

	totalPuntaje = 0;
	cantidadEvaluaciones = 0;

	for (i = 0; i < alumno->tam; i++) {
		if (alumno->evaluaciones[i] == NULL) continue;

		totalPuntaje += alumno->evaluaciones[i]->nota;
		cantidadEvaluaciones++;
	}

	if (cantidadEvaluaciones <= 0) return 0.0f;

	return (float)totalPuntaje / (float)cantidadEvaluaciones;
}
*/

float promedio(struct Alumno *alumno) { // mi versión de la función promedio (pensé que sería mejor para la sgte función)
	if (alumno == NULL || alumno->evaluaciones == NULL) return 0.0f;

	int i, totalPuntaje, cantidadEvaluaciones;

	totalPuntaje = 0;
	cantidadEvaluaciones = 0;

	for (i = 0; i < alumno->tam; i++) {
		if (alumno->evaluaciones[i] == NULL) continue;

		totalPuntaje += alumno->evaluaciones[i]->nota;
		cantidadEvaluaciones++;
	}

	if (cantidadEvaluaciones <= 0) return 0.0f;

	return (float)totalPuntaje / (float)cantidadEvaluaciones;
}

struct Alumno *getAlumnoPeorPromedio(struct NodoAlumno **head) {
	if (head == NULL || *head == NULL) return NULL;

	struct NodoAlumno *rec;
	struct Alumno *alumnoPeorPromedio;
	float peorPromedio;

	alumnoPeorPromedio = NULL;
	rec = *head;

	while (rec != NULL) {
		if (alumnoPeorPromedio == NULL || promedio(rec->dataAlumno) < peorPromedio) {
			alumnoPeorPromedio = rec->dataAlumno;
			peorPromedio = promedio(alumnoPeorPromedio);
		}

		rec = rec->sig;
	}

	quitarAlumno(head, alumnoPeorPromedio->rut);

	return alumnoPeorPromedio;
}