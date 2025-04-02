#include <stdio.h>
#include <stdlib.h>

struct Avion {
	int id;
	char *marca;
	char *modelo;
	int capacidad;
};

float promedio(struct Avion **aviones, int pLibre) {
	if (aviones == NULL || pLibre <= 0) return 0.0f;

	int i, total;

	total = 0;

	for (i = 0; i < pLibre; i++) {
		if (aviones[i] == NULL) continue; // No es necesario, dado que el array es compacto

		total += aviones[i]->capacidad;
	}

	return (float)total / (float)pLibre;
}

int cantidadBajaCapacidad(struct Avion **aviones, int pLibre, float capacidadPromedio) {
	if (aviones == NULL || pLibre <= 0) return 0;

	int i, totalBajaCapacidad;

	totalBajaCapacidad = 0;

	for (i = 0; i < pLibre; i++) {
		if (aviones[i] == NULL) continue; // No es necesario, dado que el array es compacto

		if (aviones[i]->capacidad < (int)capacidadPromedio)
			totalBajaCapacidad++;
	}

	return totalBajaCapacidad;
}

int quitarCompactar(struct Avion **aviones, int *pLibre, int id) {
	if (aviones == NULL) return 1;

	int i, j;

	for (i = 0; i < *pLibre; i++) {
		if (aviones[i] == NULL || aviones[i]->id != id) continue; // No es necesario lo de NULL, sabes porqué

		aviones[i] == NULL;

		// Compactación
		for (j = i; j < *pLibre - 1; j++) {
			aviones[j] = aviones[j + 1];
		}

		aviones[*pLibre - 1] == NULL;
		(*pLibre)++;
	}

	return 0;
}

struct Avion **quitarAvionesBajaCapacidad(struct Avion **aviones, int *pLibre) {
	if (aviones == NULL || pLibre == NULL) return NULL;

	int i, totalAvionesQuitados, iQuitados;
	float promedioCapacidad;
	struct Avion **quitados;

	iQuitados = 0;
	promedioCapacidad = promedio(aviones, *pLibre);
	totalAvionesQuitados = cantidadBajaCapacidad(aviones, *pLibre, promedioCapacidad);

	if (totalAvionesQuitados <= 0) return NULL;

	quitados = (struct Avion **)malloc(totalAvionesQuitados * sizeof(struct Avion *));

	if (quitados == NULL) return NULL;

	for (i = 0; i < *pLibre; i++) {
		if (aviones[i] == NULL) continue; // No es necesario, dado que el array es compacto

		if (aviones[i]->capacidad < (int)promedioCapacidad) {
			quitados[iQuitados] = aviones[i];
			iQuitados++;

			quitarCompactar(aviones, pLibre, aviones[i]->id);
		}
	}

	return quitados;
}