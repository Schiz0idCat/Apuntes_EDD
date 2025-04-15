#include <stdio.h>
#include <stdlib.h>

struct Nodo {
	int valor;                   // Contenido del nodo
	struct Nodo *prev, *next;    // Puntero al siguiente nodo y al anterior
};

struct Nodo *crearNodo(int valor) {
	struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

	nuevo->valor = valor;
	nuevo->prev = NULL;
	nuevo->next = NULL;

	return nuevo;
}

int enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (nuevo == NULL) return 1; // por si crearNodo() es usado como parámetro y no se alcanza a validar su retorno

	if (*head == NULL) { // Si no hay elementos en la lista
		*head = nuevo;

		return 0;
	}

	struct Nodo *rec = *head;

	while (rec->next != NULL) // Recorremos la lista hasta el último elemento
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
	struct Nodo *nodoBuscado = buscarNodo(head, valorViejo);

	if (nodoBuscado == NULL) return 1;

	nodoBuscado->valor = valorNuevo;

	return 0;
}

struct Nodo *desenlazarNodo(struct Nodo **head, int valor) {
	struct Nodo *nodoEliminar = buscarNodo(*head, valor);

	if (nodoEliminar == NULL) return NULL; // valor no encontrado

	if (nodoEliminar->prev == NULL) { // hay que eliminar el head
		*head = nodoEliminar->next;

		if (*head != NULL)
			(*head)->prev = NULL;
	}
	else
		nodoEliminar->prev->next = nodoEliminar->next;

	if (nodoEliminar->next != NULL) // si nodoEliminar no es el último
		nodoEliminar->next->prev = nodoEliminar->prev;

	nodoEliminar->next = NULL;
	nodoEliminar->prev = NULL;

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

void mostrarListaReversa(struct Nodo *head) {
	if (head == NULL) {
		printf("NULL\n");

		return;
	}

	struct Nodo *last;

	last = head;

	while (last->next != NULL)
		last = last->next;

	printf("NULL <- ");

	while (last != NULL) {
		if (last->prev != NULL)
			printf("%d <-> ", last->valor);
		else
			printf("%d -> NULL\n", last->valor);

		last = last->prev;
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

	desenlazarNodo(&numeros, 0);

	mostrarLista(numeros);

	modificarNodo(numeros, 1, 0);

	mostrarLista(numeros);

	desenlazarNodo(&numeros, 11);

	mostrarLista(numeros);

	modificarNodo(numeros, 10, 5);

	mostrarLista(numeros);

	desenlazarNodo(&numeros, 9);

	mostrarLista(numeros);

	modificarNodo(numeros, 8, 9);

	mostrarLista(numeros);

	mostrarListaReversa(numeros);

	return 0;
}
