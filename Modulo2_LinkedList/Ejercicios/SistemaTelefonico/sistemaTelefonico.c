#include <stdlib.h>
#include <string.h>

#define maxContratos 1000

struct Cliente {
	char *dni;
	char *nombre;
	char *direccion;
	int edad;
};

struct NodoCliente {
	struct Cliente *dataCliente;
	struct NodoCliente *sig;
};

struct Plan {
	int id;
	char *nombre;
	int valor;
};

struct NodoPlan {
	struct Plan *dataPlan;
	struct NodoPlan *sig;
};

struct Contrato {
	int id;
	char *fecha;
	struct Plan *plan;
	struct Cliente *cliente;
};

struct Compania {
	char *nombre;
	char *direccion;
	struct NodoPlan *headPlanes;
	struct Contrato **contratos;
};

struct NodoCompania {
	struct Compania *dataCompania;
	struct NodoCompania *ant, *sig;
};

struct Sistema {
	struct NodoCliente *headClientes;
	struct NodoCompania *headCompanias;
};

struct Cliente *buscarCliente(struct NodoCliente *clientes, char *dni) {
	if (clientes == NULL || dni == NULL) return NULL;

	struct NodoCliente *rec = clientes;

	do {
		if (strcmp(rec->dataCliente->dni, dni) == 0)
			return rec->dataCliente;

		rec = rec->sig;
	} while (rec != clientes);

	return NULL;
}

struct Compania *buscarCompania(struct NodoCompania *companias, char *nombre) {
	if (companias == NULL || nombre == NULL) return NULL;

	while (companias != NULL) {
		if (strcmp(companias->dataCompania->nombre, nombre) == 0)
			return companias->dataCompania;

		companias = companias->sig;
	}

	return NULL;
}

struct Plan *buscarPlan(struct NodoPlan *planes, int id) {
	if (planes == NULL) return NULL;

	planes = planes->sig; // como hay nodo fantasma, en el primer nodo nunca hay datos

	while (planes != NULL) {
		if (planes->dataPlan->id == id)
			return planes->dataPlan;

		planes = planes->sig;
	}

	return NULL;
}

struct Contrato *buscarContrato(struct Contrato **contratos, int id) {
	if (contratos == NULL) return NULL;

	int i;

	for (i = 0; i < maxContratos && contratos[i] != NULL; i++) {
		if (contratos[i]->id == id) return contratos[i];
	}

	return NULL;
}

int agregarContrato(struct Contrato **contratos, struct Contrato *nuevo) {
	if (contratos == NULL || nuevo == NULL) return 1;

	int i;

	for (i = 0; i < maxContratos; i++) {
		if (contratos[i] != NULL) continue; // espacio ocupado, no podemos agregar ahí el contrato

		contratos[i] = nuevo;
		return 0;
	}

	return 1;
}

int contratarPlan(struct Sistema *telefonia, int idPlan, char *nombreCompania, char *dniCliente, int idContrato, char *fechaContrato) {
	if (telefonia == NULL || dniCliente == NULL || fechaContrato == NULL) return 1;

	struct Cliente *cliente = buscarCliente(telefonia->headClientes, dniCliente);
	if (cliente == NULL) return 1;

	struct Compania *compania = buscarCompania(telefonia->headCompanias, nombreCompania);
	if (compania == NULL || buscarContrato(compania->contratos, idContrato) != NULL) return 1;

	struct Plan *plan = buscarPlan(compania->headPlanes, idPlan);
	if (plan == NULL) return 1;

	struct Contrato *nuevoContrato = (struct Contrato *)malloc(sizeof(struct Contrato));
	if (nuevoContrato == NULL) return 1;

	nuevoContrato->id = idContrato;
	nuevoContrato->fecha = fechaContrato;
	nuevoContrato->cliente = cliente;
	nuevoContrato->plan = plan;

	return agregarContrato(compania->contratos, nuevoContrato);
}