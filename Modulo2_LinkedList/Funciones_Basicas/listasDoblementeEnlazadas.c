#include <stdio.h>
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

int enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (head == NULL || nuevo == NULL) return 1;

	if (*head == NULL) {
		*head = nuevo;

		return 0;
	}

	struct Nodo *rec;

	rec = *head;

	while (rec->next != NULL)
		rec = rec->next;

	rec->next = nuevo;
	nuevo->prev = rec;

	return 0;
}

struct Nodo *buscarNodo(struct Nodo *head, int valor) {
	while (head != NULL) {
		if (head->valor == valor) return head;

		head = head->next;
	}

	return NULL;
}

int modificarNodo(struct Nodo *head, int valorViejo, int valorNuevo) {
	if (head == NULL) return 1;

	struct Nodo *nodoBuscado;

	nodoBuscado = buscarNodo(head, valorViejo);

	if (nodoBuscado == NULL) return 1;

	nodoBuscado->valor = valorNuevo;

	return 0;
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

void mostrarLista(struct Nodo *head) {
	if (head == NULL) {
		printf("NULL\n");

		return;
	}

	printf("NULL <- ");

	while (head != NULL) {
		if (head->next != NULL)
			printf("%d <-> ", head->valor);
		else
			printf("%d -> NULL\n", head->valor);

		head = head->next;
	}
}

int main() {
	struct Nodo *numeros;

	numeros = NULL;

	mostrarLista(numeros);

	enlazarNodo(&numeros, crearNodo(0)); // eliminar
	enlazarNodo(&numeros, crearNodo(1)); // modificar por 0
	enlazarNodo(&numeros, crearNodo(2));
	enlazarNodo(&numeros, crearNodo(3));
	enlazarNodo(&numeros, crearNodo(11)); // eliminar
	enlazarNodo(&numeros, crearNodo(4));
	enlazarNodo(&numeros, crearNodo(10)); // modificar por 5
	enlazarNodo(&numeros, crearNodo(6));
	enlazarNodo(&numeros, crearNodo(7));
	enlazarNodo(&numeros, crearNodo(8)); // modificar por 9
	enlazarNodo(&numeros, crearNodo(9)); // eliminar

	mostrarLista(numeros);

	eliminarNodo(&numeros, 0);

	mostrarLista(numeros);

	modificarNodo(numeros, 1, 0);

	mostrarLista(numeros);

	eliminarNodo(&numeros, 11);

	mostrarLista(numeros);

	modificarNodo(numeros, 10, 5);

	mostrarLista(numeros);

	eliminarNodo(&numeros, 9);

	mostrarLista(numeros);

	modificarNodo(numeros, 8, 9);

	mostrarLista(numeros);

	return 0;
}
