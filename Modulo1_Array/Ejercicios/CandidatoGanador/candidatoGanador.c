#include <stdio.h>
#include <string.h>

struct Candidato {
	char *rut;
	char *nombre;
	char *partidoPolitico;
	char *comunaPostulante;
};

struct EleccionesMunicipales {
	struct Candidato **candidatosConcejales;
	struct Candidato **candidatosAlcaldes;
	int pLibreAlcaldes;
};

int contarVotos(struct Candidato **candidatos, int max, char *rut) {
	int i, totalVotos = 0;

	for (i = 0; i < max; i++) {
		if (candidatos[i] != NULL && strcmp(candidatos[i]->rut, rut) == 0)
			totalVotos++;
	}

	return totalVotos;
}

struct Candidato *determinarAlcaldeGanador(struct Candidato **alcaldes, int pLibreAlcaldes, char *comuna) {
	int i, votosGanador = 0;
	struct Candidato *ganador = NULL;

	for (i = 0; i < pLibreAlcaldes; i++) {
		if (strcmp(alcaldes[i]->comunaPostulante, comuna) == 0) {
			int votosAlcalde = contarVotos(alcaldes, pLibreAlcaldes, alcaldes[i]->rut);

			if (ganador == NULL || votosAlcalde > votosGanador) {
				votosGanador = votosAlcalde;
				ganador = alcaldes[i];
			}
		}
	}

	return ganador;
}