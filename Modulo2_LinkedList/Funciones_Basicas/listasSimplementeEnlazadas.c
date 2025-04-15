#include <stdio.h>
#include <stdlib.h>

struct Nodo {
	int valor;           // Contenido del nodo
	struct Nodo *sig;    // Puntero al siguiente nodo
};

struct Nodo *crearNodo(int valor) {
	struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));

	nuevo->valor = valor;
	nuevo->sig = NULL;

	return nuevo;
}

int enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (nuevo == NULL) return 1; // por si crearNodo() es usado como parámetro y no se alcanza a validar su retorno

	if (*head == NULL) { // Si no hay elementos en la lista
		*head = nuevo; // Se asigna nuevo al head

		return 0;
	}

	struct Nodo *rec = *head;

	while (rec->sig != NULL) // Recorremos la lista hasta el último elemento
		rec = rec->sig;

	rec->sig = nuevo;

	return 0;
}

struct Nodo *buscarNodo(struct Nodo *head, int valor) {
	while (head != NULL) {
		if (head->valor == valor) return head;

		head = head->sig;
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
	struct Nodo *act, *prev; // nodo acutal, nodo previo

	act = *head;
	prev = NULL;

	if ((*head)->valor == valor) { // hay que eliminar el head
		*head = act->sig;

		return act;
	}

	while (act != NULL && act->valor != valor) { // recorremos la lista hasta encontrar el valor buscado
		prev = act;
		act = act->sig;
	}

	if (act == NULL || prev == NULL) return NULL; // Si no encontró el valor

	prev->sig = act->sig;

	return act;
}

void mostrarLista(struct Nodo *head) {
	if (head == NULL)
		printf("NULL\n");

	while (head != NULL) {
		printf("%d -> ", head->valor);

		if (head->sig == NULL)
			printf("NULL\n");

		head = head->sig;
	}
}

void mostrarListaReversa(struct Nodo *head) {
	if (head == NULL) {
		printf("NULL");
		return;
	}

	mostrarListaReversa(head->sig);

	printf(" <- %d", head->valor);
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
