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

// el código a partir de esta linea es solo para comprobar el correcto funcionamiento del código
void mostrarNotas(struct Evaluacion **evaluaciones, int tam) {
	if (evaluaciones == NULL || tam == 0) {
		printf("  []\n");
		return;
	}

	int i;

	printf("  Notas: ");
	for (i = 0; i < tam; i++) {
		if (evaluaciones[i] == NULL) continue;

		printf("%d ", evaluaciones[i]->nota);
	}
	printf("\n");
}

void mostrarAlumno(struct Alumno *alumno) {
	if (alumno == NULL) return;

	printf("RUT: %s, Nombre: %s, Evaluaciones: %d\n", alumno->rut, alumno->nombre, alumno->tam);
	mostrarNotas(alumno->evaluaciones, alumno->tam);
	printf("Promedio: %.2f\n\n", promedio(alumno));
}

void mostrarListaAlumnos(struct NodoAlumno *head) {
	if (head == NULL) {
		printf("NULL\n");
		return;
	}

	printf("Lista de Alumnos:\n");
	while (head != NULL) {
		mostrarAlumno(head->dataAlumno);

		head = head->sig;
	}
}

char *inputStr(char *msj) {
	if (msj == NULL) return NULL;

	char buffer[50];
	char *str;
	int size;

	printf("%s", msj);

	scanf(" %[^\n]", buffer);

	size = strlen(buffer);

	str = (char *)malloc(size * sizeof(char));

	if (str == NULL) return NULL;

	strcpy(str, buffer);

	return str;
}

void poblarEvaluaciones(struct Evaluacion **evaluaciones, int tam) {
	if (evaluaciones == NULL) return;

	struct Evaluacion *prueba;
	int i;

	for (i = 0; i < tam; i++) {
		prueba = (struct Evaluacion *)malloc(sizeof(struct Evaluacion));

		if (prueba == NULL) return;

		prueba->id = i; // por poner algo
		prueba->fecha = "01-01-2025"; // por poner algo

		printf("Ingrese la nota %d: ", i + 1);
		scanf("%d", &prueba->nota);

		evaluaciones[i] = prueba;
	}
}

struct Alumno *crearAlumno() {
	struct Alumno *alumno;

	alumno = (struct Alumno *)malloc(sizeof(struct Alumno));

	if (alumno == NULL) return NULL;

	alumno->rut = inputStr("Ingrese Rut: ");

	if (alumno->rut == NULL) return NULL;

	alumno->nombre = inputStr("Ingrese Nombre: ");

	if (alumno->nombre == NULL) return NULL;

	printf("Ingrese cantidad de evaluaciones: ");
	scanf("%d", &alumno->tam);

	alumno->evaluaciones = (struct Evaluacion**)malloc(alumno->tam * sizeof(struct Evaluacion *));

	if (alumno->evaluaciones == NULL) return NULL;

	poblarEvaluaciones(alumno->evaluaciones, alumno->tam);

	return alumno;
}

int main() {
	struct NodoAlumno *lista;
	struct Alumno *alumno;
	int opcion;

	lista = NULL;
	alumno = NULL;

	do {
		printf("\nMenu:\n");
		printf("1. Agregar alumno\n");
		printf("2. Mostrar alumnos\n");
		printf("3. Mostrar peor promedio\n");
		printf("4. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);

		switch (opcion) {
			case 1:
				alumno = crearAlumno();
				if (alumno != NULL)
					agregarAlumno(&lista, alumno);
				else
					printf("Error al crear alumno.\n");
				break;
			case 2:
				mostrarListaAlumnos(lista);
				break;
			case 3:
				alumno = getAlumnoPeorPromedio(&lista);
				if (alumno != NULL) {
					printf("\nEl alumno con peor promedio es:\n");
					printf("RUT: %s, Nombre: %s, Promedio: %.2f\n", alumno->rut, alumno->nombre, promedio(alumno));
				}
				else
					printf("\nNo hay alumnos en la lista.\n");
				break;
			case 4:
				printf("Saliendo...\n");
				break;
			default:
				printf("Opcion invalida.\n");
		}
	} while (opcion != 4);

	return 0;
}