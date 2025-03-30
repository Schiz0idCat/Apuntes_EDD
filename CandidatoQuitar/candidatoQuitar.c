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

int agregarCandidatoAlcalde(struct Candidato **alcaldes, int n, int *pLibre, struct Candidato *nuevo) {
	if (*pLibre >= n) return 0;

	int i;

	for (i = 0; i < *pLibre; i++) {
		if (alcaldes[i] == NULL || strcmp(alcaldes[i]->rut, nuevo->rut) == 0)
			return 0;
	}

	alcaldes[*pLibre] = nuevo;
	(*pLibre)++;

	return 1;
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
	int i;
	struct Candidato *candidatoQuitado;

	candidatoQuitado = NULL;

	for (i = 0; i < tamConcejales; i++) {
		if (elecciones->candidatosConcejales[i] == NULL) continue;

		if (strcmp(elecciones[i].candidatosConcejales[i]->rut, rutCandidato) == 0) {
			candidatoQuitado = elecciones[i].candidatosConcejales[i];
			elecciones[i].candidatosConcejales[i] = NULL;

			return candidatoQuitado;
		}
	}

	for (i = 0; i < elecciones->plibreAlcaldes; i++) {
		if (strcmp(elecciones[i].candidatosAlcalde[i]->rut, rutCandidato) == 0) {
			candidatoQuitado = elecciones[i].candidatosAlcalde[i];
			elecciones[i].candidatosAlcalde[i] = NULL;

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