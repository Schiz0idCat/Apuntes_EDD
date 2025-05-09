#include <stdio.h>
#include <string.h>

#define MAX 46352

struct Loteria {
	struct Cliente **clientes;
	char *pais;
};

struct Cliente {
	char *nombre;
	char *apellido;
	int edad;
	struct Carton **comprados;
	int pLibre;
};

struct Carton {
	char tipoSorteo;
	char *numSorteo;
	int dia;
	int mes;
	int anio;
};

int comprobarGanador(struct Cliente *cliente, char *numGanador, char *nombre, char *apellido) {
	if (cliente == NULL || numGanador == NULL || nombre == NULL || apellido == NULL) return 0;

	int i;

	for (i = 0; i < cliente->pLibre; i++) {
		if (cliente->comprados[i] == NULL ||
			cliente->comprados[i]->tipoSorteo != 'A' ||
			strcmp(cliente->comprados[i]->numSorteo, numGanador) != 0 ||
			strcmp(cliente->nombre, nombre) != 0 ||
			strcmp(cliente->apellido, apellido) != 0)
				continue;

		return 1;
	}

	return 0;
}

int verificarGanador(struct Loteria *kino, char *numGanador, char *nombre, char *apellido) {
	if (kino == NULL || numGanador == NULL || nombre == NULL || apellido == NULL) return 1;

	int i;

	for (i = 0; i < MAX; i++) { // recorriendo la lista de clientes
		struct Cliente **cliente;
		cliente = &kino->clientes[i]; // desempaquetamiento

		if (cliente != NULL && comprobarGanador((*cliente), numGanador, nombre, apellido))
			return 1;
	}

	return 0;
}

int main() {
	struct Loteria *kino;
}