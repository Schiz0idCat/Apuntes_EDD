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

struct Nodo *buscarNodo(struct Nodo *head, int valor) {
	while (head != NULL) {
		if (head->valor == valor) return head;

		head = head->next;
	}

	return NULL;
}

struct Nodo *eliminarNodo(struct Nodo **head, int valor) {
	if (head == NULL || *head == NULL) return NULL;

	struct Nodo *nodoEliminar;

	nodoEliminar = buscarNodo(*head, valor);

	if (nodoEliminar == NULL) return NULL; // valor no encontrado

	if (nodoEliminar->prev == NULL) { // si es el primero
		*head = nodoEliminar->next;

		if (*head != NULL) (*head)->prev = NULL;
	}
	else
		nodoEliminar->prev->next = nodoEliminar->next;

	if (nodoEliminar->next != NULL) // si nodoEliminar no es el último
		nodoEliminar->next->prev = nodoEliminar->prev;

	return nodoEliminar;
}