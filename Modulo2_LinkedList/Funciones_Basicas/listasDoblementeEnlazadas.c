#include <stdlib.h>

struct Nodo {
	int valor;
	struct Nodo *prev, *next;
};

struct Nodo *crearNodo(int valor) {
	struct Nodo *nuevo;

	nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

	if (nuevo == NULL) return NULL;

	nuevo->valor = valor;
	nuevo->prev = NULL;
	nuevo->next = NULL;

	return nuevo;
}

void enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (head == NULL || nuevo == NULL) return;

	if (*head == NULL) {
		*head = nuevo;

		return;
	}

	struct Nodo *rec;

	rec = *head;

	while (rec->next != NULL)
		rec = rec->next;

	rec->next = nuevo;
	nuevo->prev = rec;
}