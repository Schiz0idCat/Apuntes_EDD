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
	if (candidatos == NULL || rut == NULL) return 0;

	int i, totalVotos;

	totalVotos = 0;

	for (i = 0; i < max; i++) {
		if (candidatos[i] == NULL || candidatos[i]->rut == NULL) continue;

		if (strcmp(candidatos[i]->rut, rut) == 0) totalVotos++;
	}

	return totalVotos;
}

struct Candidato *determinarAlcaldeGanador(struct Candidato **alcaldes, int pLibreAlcaldes, char *comuna) {
	if (alcaldes == NULL || comuna == NULL) return NULL;

	int i, votosGanador;
	struct Candidato *ganador;

	votosGanador = 0;
	ganador = NULL;

	for (i = 0; i < pLibreAlcaldes; i++) {
		if (alcaldes[i] == NULL || alcaldes[i]->comunaPostulante == NULL) continue;

		if (strcmp(alcaldes[i]->comunaPostulante, comuna) == 0) {
			if (ganador == NULL || contarVotos(alcaldes, pLibreAlcaldes, alcaldes[i]->rut) > votosGanador) {
				votosGanador = contarVotos(alcaldes, pLibreAlcaldes, alcaldes[i]->rut);
				ganador = alcaldes[i];
			}
		}
	}

	return ganador;
}