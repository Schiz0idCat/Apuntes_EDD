#include <stdio.h>
#include <string.h>

struct Candidato{
	char *rut;
	char *nombre;
	char *partidoPolitico;
	char *comunaPostulante;
};

struct EleccionesMunicipales {
	struct Candidato **candidatosConcejales;
	struct Candidato **candidatosAlcalde;
	int plibreAlcaldes;
};

int agregarCandidatoAlcalde(struct Candidato **alcaldes, int max, int *pLibre, struct Candidato *nuevo) {
	if (*pLibre >= max) return 1;

	int i;

	for (i = 0; i < *pLibre; i++) {
		if (alcaldes[i] == NULL || strcmp(alcaldes[i]->rut, nuevo->rut) == 0)
			return 1;
	}

	alcaldes[*pLibre] = nuevo;
	(*pLibre)++;

	return 0;
}

void compactarArray(struct Candidato **arr, int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		if (arr[i] != NULL) continue;

		for (j = i; j < n; j++) {
			if (arr[j] == NULL) continue;

			arr[i] = arr[j];
			arr[j] = NULL;

			break;
		}
	}
}

struct Candidato *quitarCandidato(struct EleccionesMunicipales *elecciones, int tamConcejales, int tamAlcaldes, char *rutCandidato) {
	if (elecciones == NULL) return NULL;

	int i;
	struct Candidato *candidatoQuitado;

	candidatoQuitado = NULL;

	for (i = 0; i < tamConcejales; i++) {
		if (elecciones->candidatosConcejales[i] == NULL) continue;

		if (strcmp(elecciones->candidatosConcejales[i]->rut, rutCandidato) == 0) {
			candidatoQuitado = elecciones->candidatosConcejales[i];
			elecciones->candidatosConcejales[i] = NULL;

			return candidatoQuitado;
		}
	}

	for (i = 0; i < elecciones->plibreAlcaldes; i++) {
		if (strcmp(elecciones->candidatosAlcalde[i]->rut, rutCandidato) == 0) {
			candidatoQuitado = elecciones->candidatosAlcalde[i];
			elecciones->candidatosAlcalde[i] = NULL;

			compactarArray(elecciones->candidatosAlcalde, tamAlcaldes);

			return candidatoQuitado;
		}
	}

	return candidatoQuitado;
}

int main(void) {
	struct EleccionesMunicipales *Municipales2024;
	return 0;
}