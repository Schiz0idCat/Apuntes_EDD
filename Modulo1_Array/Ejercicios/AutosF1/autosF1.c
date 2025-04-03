#include <stdio.h>
#include <stdlib.h>

#define cantEquipos 1000
#define cantAutos 500

struct Equipo {
	int id;
	char *nombre;
	char *nombreDirector;
	int pLibre;
	struct Auto **Autos;
};

struct Auto {
	int numero;
	char *nombrePiloto;
	int cantidadVictorias;
};

struct Auto *ganadorEnEquipo(struct Auto **autos, int pLibre) {
	if (autos == NULL) return NULL;

	int i;
	struct Auto *ganador;

	ganador = NULL;

	for (i = 0; i < pLibre; i++) {
		if (autos[i] == NULL || autos[i]->cantidadVictorias == 0) continue;

		if (ganador == NULL || autos[i]->cantidadVictorias > ganador->cantidadVictorias)
			ganador = autos[i];
	}

	return ganador;
}

int cantGanadores(struct Equipo **equipos) {
	if (equipos == NULL) return 0;

	int i, nGanadores;

	nGanadores = 0;

	for (i = 0; i < cantEquipos; i++) {
		if (equipos[i] == NULL) continue;

		if (ganadorEnEquipo(equipos[i]->Autos, equipos[i]->pLibre) != NULL)
			nGanadores++;
	}

	return nGanadores;
}

void poblarGanadores(struct Auto **ganadores, struct Equipo **equipos) {
	if (ganadores == NULL || equipos == NULL) return;

	int i, iGanadores;
	struct Auto *ganador;

	iGanadores = 0;

	for (i = 0; i < cantEquipos; i++) {
		if (equipos[i] == NULL) continue;

		ganador = ganadorEnEquipo(equipos[i]->Autos, equipos[i]->pLibre);

		if (ganador == NULL) continue;

		ganadores[iGanadores] = ganador;
		iGanadores++;
	}
}

struct Auto **getAutosGanadoresPorEquipo(struct Equipo **equipos) {
	if (equipos == NULL) return NULL;

	int nGanadores;
	struct Auto **ganadores;

	nGanadores = cantGanadores(equipos);

	if (nGanadores == 0) return NULL;

	ganadores = (struct Auto **)malloc(nGanadores * sizeof(struct Auto *));
	if (ganadores == NULL) return NULL;

	poblarGanadores(ganadores, equipos);

	return ganadores;
}

int main() {
	struct Equipo **equiposF1;
}