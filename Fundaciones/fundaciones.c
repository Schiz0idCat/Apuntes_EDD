#include <stdio.h>
#include <stdlib.h>

#define cantFundaciones 1000

struct Traspaso {
	int numero;
	char *nombre;
	int monto;
	char *nombreAutorizacion;
};

struct Fundacion {
	int id;
	char *representante;
	char *nombreFundacion;
	int pLibre;
	struct Traspaso **traspasos;
};

int totalTraspasos(struct Fundacion *fundacion) {
	if (fundacion == NULL || fundacion->traspasos == NULL) return NULL;

	int i, totalMontos;

	totalMontos = 0;

	for (i = 0; i < fundacion->pLibre; i++) {
		if (fundacion->traspasos[i] == NULL) continue;

		totalMontos += fundacion->traspasos[i]->monto;
	}

	return totalMontos;
}

int nFundasMenorQueMonto(struct Fundacion **fundaciones, int montoReferencia) {
	if (fundaciones == NULL) return 0;

	int i, nFundacionesMenorQueMonto;

	nFundacionesMenorQueMonto = 0;

	for (i = 0; i < cantFundaciones; i++) {
		if (fundaciones[i] == NULL || fundaciones[i]->traspasos == NULL) return 0;

		if (totalTraspasos(fundaciones[i]) >= montoReferencia) continue;

		nFundacionesMenorQueMonto++;
	}

	return nFundacionesMenorQueMonto;
}

struct Fundacion **quitarFundaciones(struct Fundacion **fundaciones, int montoReferencia) {
	if (fundaciones == NULL) return NULL;

	int nQuitadas, iQuitadas, i;
	struct Fundacion **quitadas;

	nQuitadas = nFundasMenorQueMonto(fundaciones, montoReferencia);

	if (nQuitadas < 1) return NULL;

	iQuitadas = 0;
	quitadas = (struct Fundacion **)malloc(nQuitadas * sizeof(struct Fundacion *));

	for (i = 0; i < cantFundaciones; i++) {
		if (fundaciones[i] == NULL) continue;

		if (totalTraspasos(fundaciones[i]) >= montoReferencia) continue;

		quitadas[iQuitadas] = fundaciones[i];
		iQuitadas++;

		fundaciones[i] = NULL;
	}

	return quitadas;
}