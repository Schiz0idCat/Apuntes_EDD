#include <stdlib.h>

struct Banco {
	char *nombre;
	char *direccion;
	int saldo;
};

struct NodoBanco { // nodo fantasma
	struct Banco *datosBanco;
	struct NodoBanco *sig, *ant;
};

struct Robo {
	char *fecha;
	int monto;
	struct Banco *bancoRobado;
};

struct Ladron {
	char *apodo;
	char *rut;
	int maxRobos;
	struct Robo **robos;
	int pLibreRobos;
};

struct NodoLadron { // lista circular
	struct Ladron *datosLadron;
	struct NodoLadron *sig;
};

struct BandaCriminal {
	char *nombre;
	struct NodoLadron *headLadrones;
	struct NodoBanco *headBancos;
};

float promedioRobos(struct Robo **robos, int pLibre) {
	if (robos == NULL || pLibre == 0) return 0.0f;

	int i, totalRobado = 0;

	for (i = 0; i < pLibre && robos[i] != NULL; i++) {
		totalRobado += robos[i]->monto;
	}

	return (float)totalRobado / (float)pLibre;
}

float promedioTotalRobado(struct NodoLadron *ladrones) {
	if (ladrones == NULL) return 0.0f;

	struct NodoLadron *rec = ladrones;
	struct Ladron *ladron;
	int i, cantidadLadrones = 0, totalRobado = 0;

	do {
		ladron = rec->datosLadron;
		cantidadLadrones++;

		for (i = 0; i < ladron->pLibreRobos && ladron->robos[i] != NULL; i++) {
			totalRobado += ladron->robos[i]->monto;
		}

		rec = rec->sig;
	} while (rec != ladrones);

	if (cantidadLadrones == 0) return 0.0f;

	return (float)totalRobado / (float)cantidadLadrones;
}

struct Ladron **quitarLadronesMenosRentables(struct BandaCriminal *LosCareNodo) {

}