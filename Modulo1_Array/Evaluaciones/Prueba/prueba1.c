#include <stdlib.h>

#define tamArreglo 1000

struct Piloto {
	char *nombre;
	char *nacionalidad;
	char *scuderia;
	int vecesCampeon;
};

int cantidadGanadores(struct Piloto **pilotos, int pLibre) {
	int i, cantidad = 0;

	for (i = 0; i < pLibre; i++) {
		if (pilotos[i]->vecesCampeon > 0)
			cantidad++;
	}

	return cantidad;
}

void poblarCampeones(struct Piloto **ganadores, struct Piloto **pilotos, int pLibre) {
	int i, iCampeones = 0;

	for (i = 0; i < pLibre; i++) {
		if (pilotos[i]->vecesCampeon > 0)
			ganadores[iCampeones++] = pilotos[i];
	}
}

struct Piloto **getHistoricoCampeones(struct Piloto **pilotos, int pLibre) {
	int nGanadores = cantidadGanadores(pilotos, pLibre);

	if (nGanadores <= 0) return NULL;

	struct Piloto **ganadores = (struct Piloto **)malloc(nGanadores * sizeof(struct Piloto*));

	if (ganadores == NULL) return NULL;

	poblarCampeones(ganadores, pilotos, pLibre);

	return ganadores;
}