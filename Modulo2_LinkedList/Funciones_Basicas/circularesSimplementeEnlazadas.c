#include <stdio.h>
#include <stdlib.h>

struct Nodo {
	int valor;
	struct Nodo *sig;
};

struct Nodo *crearNodo(int valor) {
	struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

	if (nuevo == NULL) return NULL;

	nuevo->valor = valor;
	nuevo->sig = NULL;

	return nuevo;
}

int enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (nuevo == NULL) return 1; // por si crearNodo() es usado como parámetro y no se alcanza a validar su retorno

	if (*head == NULL) { // Si no hay elementos en la lista
		*head = nuevo;
		(*head)->sig = *head;

		return 0;
	}

	struct Nodo *rec = *head;

	while (rec->sig != *head) // Recorremos la lista hasta el último elemento
		rec = rec->sig;

	rec->sig = nuevo;
	nuevo->sig = *head;

	return 0;
}

struct Nodo *buscarNodo(struct Nodo *head, int valorBuscado) {
	struct Nodo *rec = head;

	do {
		if (rec->valor == valorBuscado)
			return rec;

		rec = rec->sig;
	} while (rec != head);

	return NULL;
}

int modificarNodo(struct Nodo *head, int valorViejo, int valorNuevo) {
	struct Nodo *nodo = buscarNodo(head, valorViejo);

	if (nodo == NULL) return 1;

	nodo->valor = valorNuevo;

	return 0;
}


int desenlazarNodo(struct Nodo **head, int valor) {
	if ((*head)->valor == valor) { // hay que eliminar el head
		if ((*head)->sig == *head)    // solo un nodo
			*head = NULL;
		else {                        // múltiples nodos
			struct Nodo *ultimo = *head;

			while (ultimo->sig != *head)
				ultimo = ultimo->sig;

			*head = (*head)->sig;
			ultimo->sig = *head;
		}

		return 0;
	}

	struct Nodo *act = (*head)->sig, *ant = *head;

	while (act != *head) {
		if (act->valor == valor) {
			ant->sig = act->sig;
			return 0;
		}

		ant = act;
		act = act->sig;
	}

	return 1; // valor no encontrado
}

void mostrarLista(struct Nodo *head) {
	if (head == NULL) {
		printf("NULL\n");
		return;
	}

	struct Nodo *rec = head;

	do {
		printf("%d ", rec->valor);
		rec = rec->sig;
	} while (rec != head);

	printf("\n");
}

int main() {
	struct Nodo *numeros = NULL;

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

	return 0;
}