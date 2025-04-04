#include <stdio.h>
#include <stdlib.h>

struct Nodo {
	int valor;			// Contenido del nodo
	struct Nodo *sig;	// Puntero al siguiente nodo
};

struct Nodo *crearNodo(int valor) { // Se recibe por parámetro el elemento que queremos agregar
	struct Nodo *nuevo;

	nuevo = (struct Nodo *)malloc(sizeof(struct Nodo)); // Se reserva memoria para cada nodo nuevo

	if (nuevo == NULL) return NULL;

	nuevo->valor = valor;		// Asignando el elemento
	nuevo->sig = NULL;			// Asignando el siguiente nodo;

	return nuevo;
}

// El head se recibe como doble puntero en caso de tener que modificar el primer elemento
// Si NO hay elementos en la lista, se debe asignar al head (modificando el primer elemento)
// En caso contrario, no se asigna al head (no se modifica el primer elemento) y se añade el nodo al final de la lista
void enlazarNodo(struct Nodo **head, struct Nodo *nuevo) {
	if (head == NULL || nuevo == NULL) return;

	if (*head == NULL) { // Si no hay elementos en la lista
		*head = nuevo; // Se asigna nuevo al head

		return;
	}

	struct Nodo *rec; // rec viene de recorrido, será una copia del puntero head que usaremos para recorrer la lista

	rec = *head;

	// Recorremos la lista
	while (rec->sig != NULL)
		rec = rec->sig;

	rec->sig = nuevo;
}

struct Nodo *buscarNodo(struct Nodo *head, int valor) {
	while (head != NULL) {
		if (head->valor == valor) return head;

		head = head->sig;
	}

	return NULL;
}

void modificarNodo(struct Nodo **head, struct Nodo *nodoViejo, struct Nodo *nodoNuevo) {
	if (head == NULL || nodoViejo == NULL || nodoNuevo == NULL) return;

	struct Nodo *act, *prev;

	act = *head;
	prev = NULL;

	while (act != NULL && act != nodoViejo) {
		prev = act;
		act = act->sig;
	}

	if (act == NULL) return; // no se encontró el nodo

	if (prev == NULL) // el head es el nodo buscado
		*head = nodoNuevo;
	else
		prev->sig = nodoNuevo;

	nodoNuevo->sig = act->sig;

	free(act);
}

void eliminarNodo(struct Nodo **head, int valor) {
	if (head == NULL || *head == NULL) return;

	struct Nodo *act, *prev; // nodo acutal, nodo previo

	act = *head;
	prev = NULL;

	if (act->valor == valor) { // Si hay que eliminar el head
		*head = act->sig;
		free(act);

		return;
	}

	while (act != NULL && act->valor != valor) {
		prev = act;
		act = act->sig;
	}

	if (act == NULL || prev == NULL) return; // Si no encontró el valor

	prev->sig = act->sig;
	free(act);
}

void mostrarNodos(struct Nodo *head) {
	while (head != NULL) {
		printf("%d -> ", head->valor);
		head = head->sig; // como el parámetro no es un doble puntero, se puede recorrer con el head sin problemas
	}
	printf("NULL\n");
}

int main() {
	struct Nodo *numeros;

	numeros = NULL;

	mostrarNodos(numeros);

	enlazarNodo(&numeros, crearNodo(0));
	enlazarNodo(&numeros, crearNodo(1));
	enlazarNodo(&numeros, crearNodo(6)); // modificar por 2
	enlazarNodo(&numeros, crearNodo(3));
	enlazarNodo(&numeros, crearNodo(9)); // eliminar
	enlazarNodo(&numeros, crearNodo(4));
	enlazarNodo(&numeros, crearNodo(5));

	mostrarNodos(numeros);

	modificarNodo(&numeros, buscarNodo(numeros, 6), crearNodo(2));

	mostrarNodos(numeros);

	eliminarNodo(&numeros, 9);

	mostrarNodos(numeros);

	return 0;
}
