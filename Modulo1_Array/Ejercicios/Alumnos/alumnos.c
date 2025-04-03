#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAYMAX 1000

struct Alumno {
	char *rut;
	char *nombre;
	float promedio;
};

int buscarAlumno(struct Alumno **alumnos, int pLibre, char *rut) {
	if (alumnos == NULL) return 0;

	int i;

	for (i = 0; i < pLibre; i ++) {
		if (alumnos[i] == NULL || alumnos[i]->rut == NULL) continue;

		if (strcmp(alumnos[i]->rut, rut) == 0) return 0;
	}

	return 1;
}

int agregarAlumnos(struct Alumno **alumnos, int *pLibre, char *rut, char *nombre, float promedio) {
	if (alumnos == NULL || rut == NULL || nombre == NULL) return 1;

	// si el array se encuentra lleno o el estudiante ya está en el array, retorna 1
	if (*pLibre >= ARRAYMAX || buscarAlumno(alumnos, *pLibre, rut) == 0) return 1;

	struct Alumno *nuevoAlumno;

	nuevoAlumno = (struct Alumno *)malloc(sizeof(struct Alumno));

	if (nuevoAlumno == NULL) return 1;

	nuevoAlumno->rut = rut;
	nuevoAlumno->nombre = nombre;
	nuevoAlumno->promedio = promedio;

	alumnos[*pLibre] = nuevoAlumno;
	(*pLibre)++;

	return 0;
}

char *getAlumnoMejorPromedio(struct Alumno **alumnos, int pLibre) {
	if (alumnos == NULL) return NULL;

	int i;
	struct Alumno *mejorPromedio;

	mejorPromedio = NULL;

	for (i = 0; i < pLibre; i++) {
		if (alumnos[i] == NULL || alumnos[i]->rut == NULL) continue;

		if (mejorPromedio == NULL || alumnos[i]->promedio > mejorPromedio->promedio)
			mejorPromedio = alumnos[i];
	}

	if (mejorPromedio == NULL) return NULL;

	return mejorPromedio->rut;
}

int main() {
	struct Alumno **alumnos;
}