#include <stdio.h>
#include <stdlib.h>

struct Compra {
	char *nombreCliente;
	int montoCompra;
	char *fecha;
};

float promedioCompras(struct Compra **compras, int max) {
	int i, totalMonto = 0, totalClientes = 0;

	for (i = 0; i < max; i++) {
		if (compras[i] == NULL) continue;

		totalMonto += compras[i]->montoCompra;
		totalClientes++;
	}

	if (totalClientes == 0)
		return 0.0f;

	return (float)totalMonto / (float)totalClientes;
}

int totalClientesBajoPromedio(struct Compra **compras, int max, float promedio) {
	if (compras == NULL) return 0;

	int i, nClientesBajoPromedio;

	nClientesBajoPromedio = 0;

	for (i = 0; i < max; i++) {
		if (compras[i] == NULL || (float)compras[i]->montoCompra >= promedio) continue;

		nClientesBajoPromedio++;
	}

	return nClientesBajoPromedio;
}

void reemplazarClientes(struct Compra **compras, struct Compra **bajoPromedio, float promedio, int max) {
	if (compras == NULL || bajoPromedio == NULL) return;

	int i, iBajoPromedio;

	iBajoPromedio = 0;

	for (i = 0; i < max; i++) {
		if (compras[i] == NULL || (float)compras[i]->montoCompra >= promedio) continue;

		bajoPromedio[iBajoPromedio] = compras[i];
		iBajoPromedio++;

		compras[i] = NULL;
	}
}

struct Compra **quitarClientesMenorCantidadCompras(struct Compra **compras, int max) {
	if (compras == NULL) return NULL;

	int nClientesBajoPromedio;
	float promedio;
	struct Compra **clientesBajoPromedio;

	promedio = promedioCompras(compras, max);
	nClientesBajoPromedio = totalClientesBajoPromedio(compras, max, promedio);

	if (nClientesBajoPromedio < 1) return NULL;

	clientesBajoPromedio = (struct Compra **)malloc(nClientesBajoPromedio * sizeof(struct Compra *));
	if (clientesBajoPromedio == NULL) return NULL;

	reemplazarClientes(compras, clientesBajoPromedio, promedio, max);

	return clientesBajoPromedio;
}

int main() {
	struct Compra **compras;
}