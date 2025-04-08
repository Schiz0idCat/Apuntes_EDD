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
	if (fundacion == NULL || fundacion->traspasos == NULL) return 0;

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

int poblarFundacionesQuitadas(struct Fundacion **quitadas, struct Fundacion **fundaciones, int montoReferencia) {
	if (quitadas == NULL || fundaciones == NULL) return 1;

	int i, iQuitadas;

	iQuitadas = 0;

	for (i = 0; i < cantFundaciones; i++) {
		if (fundaciones[i] == NULL) continue;

		if (totalTraspasos(fundaciones[i]) < montoReferencia) {
			quitadas[iQuitadas] = fundaciones[i];
			iQuitadas++;

			fundaciones[i] = NULL;
		}
	}

	return 0;
}

struct Fundacion **quitarFundaciones(struct Fundacion **fundaciones, int montoReferencia) {
	if (fundaciones == NULL) return NULL;

	int nQuitadas;
	struct Fundacion **quitadas;

	nQuitadas = nFundasMenorQueMonto(fundaciones, montoReferencia);

	if (nQuitadas < 1) return NULL;

	quitadas = (struct Fundacion **)malloc(nQuitadas * sizeof(struct Fundacion *));

	if (quitadas == NULL) return NULL;

	poblarFundacionesQuitadas(quitadas, fundaciones, montoReferencia);

	return quitadas;
}