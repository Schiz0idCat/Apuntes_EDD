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
	int i;
	struct Auto *ganador = NULL;

	for (i = 0; i < pLibre; i++) {
		if (ganador == NULL || autos[i]->cantidadVictorias > ganador->cantidadVictorias)
			ganador = autos[i];
	}

	return ganador;
}

int cantGanadores(struct Equipo **equipos) {
	int i, nGanadores = 0;

	for (i = 0; i < cantEquipos; i++) {
		if (equipos[i] != NULL && ganadorEnEquipo(equipos[i]->Autos, equipos[i]->pLibre) != NULL)
			nGanadores++;
	}

	return nGanadores;
}

void poblarGanadores(struct Auto **ganadores, struct Equipo **equipos) {
	int i, iGanadores = 0;
	struct Auto *ganador;

	for (i = 0; i < cantEquipos; i++) {
		if (equipos[i] != NULL) {
			ganador = ganadorEnEquipo(equipos[i]->Autos, equipos[i]->pLibre);

			if (ganador != NULL) {
				ganadores[iGanadores] = ganador;
				iGanadores++;
			}
		}
	}
}

struct Auto **getAutosGanadoresPorEquipo(struct Equipo **equipos) {
	int nGanadores = cantGanadores(equipos);

	if (nGanadores == 0) return NULL;

	struct Auto **ganadores = (struct Auto **)malloc(nGanadores * sizeof(struct Auto *));

	if (ganadores == NULL) return NULL;

	poblarGanadores(ganadores, equipos);

	return ganadores;
}

int main() {
	struct Equipo **equiposF1;
}