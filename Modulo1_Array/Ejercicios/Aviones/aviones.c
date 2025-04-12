#include <stdio.h>
#include <stdlib.h>

struct Avion {
	int id;
	char *marca;
	char *modelo;
	int capacidad;
};

float promedio(struct Avion **aviones, int pLibre) {
	int i, total = 0;

	for (i = 0; i < pLibre; i++)
		total += aviones[i]->capacidad;

	return (float)total / (float)pLibre;
}

int cantidadBajaCapacidad(struct Avion **aviones, int pLibre, float capacidadPromedio) {
	int i, totalBajaCapacidad = 0;

	for (i = 0; i < pLibre; i++) {
		if (aviones[i]->capacidad < (int)capacidadPromedio)
			totalBajaCapacidad++;
	}

	return totalBajaCapacidad;
}

int quitarCompactar(struct Avion **aviones, int *pLibre, int id) {
	int i, j;

	for (i = 0; i < *pLibre; i++) {
		if (aviones[i] == NULL || aviones[i]->id != id) continue;

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

void poblarAvionesBajaCapacidad(struct Avion **bajaCapacidad, struct Avion **aviones, int *pLibre, float promedioCapacidad) {
	int i, iBajaCapacidad = 0;

	for (i = 0; i < *pLibre; i++) {
		if (aviones[i]->capacidad < (int)promedioCapacidad) {
			bajaCapacidad[iBajaCapacidad++] = aviones[i];

			quitarCompactar(aviones, pLibre, aviones[i]->id);
		}
	}
}

struct Avion **quitarAvionesBajaCapacidad(struct Avion **aviones, int *pLibre) {
	float promedioCapacidad = promedio(aviones, *pLibre);
	int nBajaCapacidad = cantidadBajaCapacidad(aviones, *pLibre, promedioCapacidad);

	if (nBajaCapacidad <= 0) return NULL;

	struct Avion **bajaCapacidad = (struct Avion **)malloc(nBajaCapacidad * sizeof(struct Avion *));

	if (bajaCapacidad == NULL) return NULL;

	poblarAvionesBajaCapacidad(bajaCapacidad, aviones, pLibre, promedioCapacidad);

	return bajaCapacidad;
}