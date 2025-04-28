#include <stdlib.h>

struct Producto {
	int id;
	char *nombre;
	float precio;
};

struct NodoProducto { // Lista doblemente enlazada con nodo dummy (fantasma)
	struct Producto *producto;
	struct NodoProducto *sig, *ant;
};

struct Usuario {
	int id;
	char *nombre;
	struct NodoProducto *carrito;
};

struct NodoUsuario { // Lista enlazada circular
	struct Usuario *usuario;
	struct NodoUsuario *sig;
};

struct Supermercado {
	struct NodoProducto *productos;
	struct NodoUsuario *usuarios;
};

struct Usuario *buscarUsuario(struct NodoUsuario *head, int id) {
	struct NodoUsuario *rec = head;

	do {
		if (rec->usuario->id == id)
			return rec->usuario;

		rec = rec->sig;
	} while (rec != head);

	return NULL;
}

struct Producto *buscarProducto(struct NodoProducto *head, int id) {
	head = head->sig;

	while (head != NULL) {
		if (head->producto->id == id)
			return head->producto;

		head = head->sig;
	}

	return NULL;
}

struct NodoProducto *crearNodoProducto(struct Producto *producto) {
	struct NodoProducto *nodo = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));

	nodo->producto = producto;
	nodo->sig = NULL;
	nodo->ant = NULL;

	return nodo;
}

void enlazarNodoProducto(struct NodoProducto *carrito, struct NodoProducto *producto) {
	while (carrito->sig != NULL)
		carrito = carrito->sig;

	carrito->sig = producto;
	producto->sig = NULL;
	producto->ant = carrito;
}

// La función debe agregar la referencia al producto con idProducto al carrito del usuario con idUsuario.
// Si la operación es exitosa, debe retornar 1. Si el usuario o el producto no existen, debe retornar 0.
int agregarProductoACarrito(struct Supermercado *super, int idUsuario, int idProducto) {
	struct Usuario *usuario = buscarUsuario(super->usuarios, idUsuario);
	struct Producto *producto = buscarProducto(super->productos, idProducto);

	if (usuario == NULL || producto == NULL) return 0;

	enlazarNodoProducto(usuario->carrito, crearNodoProducto(producto));

	return 1;
}