#include <stdlib.h>

struct Lord {
	char *nombre;
	char *apellido;
	int batallasGanadas;
	float oroInvertido;
};

struct NodoLord {
	struct Lord *datosLord;
	struct NodoLord *sig, *ant;
};

struct Casa {
	char *nombre;
	int cantidadMilitares;
	int oroAlmacenado;
	struct NodoLord *headLords;
};

struct NodoCasa {
	struct Casa *datosCasa;
	struct NodoCasa *sig;
};

struct TronoDeHierro {
	struct Lord *rey;
	int deuda;
	struct NodoCasa *casas;
};

float calcularIndicadorLord(struct Lord *lord, int cantidadMilitares) {
	if (lord == NULL) return 0.0f;

	return lord->batallasGanadas * .2f + lord->oroInvertido * .5f + cantidadMilitares * .3;
}

struct Lord *getMayorLordEnCasa(struct NodoLord *head, int cantidadMilitares) {
	if (head == NULL) return NULL;

	struct Lord *lordMayor;
	float lordMayorIndicador;

	lordMayor = NULL;
	lordMayorIndicador = 0;

	while (head != NULL) {
		if (lordMayor == NULL || calcularIndicadorLord(head->datosLord, cantidadMilitares) > lordMayorIndicador) {
			lordMayor = head->datosLord;
			lordMayorIndicador = calcularIndicadorLord(head->datosLord, cantidadMilitares);
		}

		head = head->sig;
	}

	return lordMayor;
}

struct Lord *elegirNuevoRey(struct TronoDeHierro *corona) {
	if (corona == NULL) return NULL;

	struct Lord *nuevoRey, *candidato;
	struct Casa *casaGanadora;
	struct NodoCasa *recCasas;
	float indicadorNuevoRey, indicadorCandidato;

	nuevoRey = NULL;
	casaGanadora = NULL;
	recCasas = corona->casas;

	while (recCasas != NULL) {
		candidato = getMayorLordEnCasa(recCasas->datosCasa->headLords, recCasas->datosCasa->cantidadMilitares);

		if (candidato == NULL) {
			recCasas = recCasas->sig;
			continue;
		}

		indicadorCandidato = calcularIndicadorLord(candidato, recCasas->datosCasa->cantidadMilitares);

		if (nuevoRey  == NULL ||                        // caso 1: Aún no hay rey asignado
			indicadorCandidato > indicadorNuevoRey ||   // caso 2: La casa que recorremos supera al actual nuevoRey
			(indicadorCandidato == indicadorNuevoRey &&	// caso 3: la casa que recorremos empata con el actual nuevoRey
			recCasas->datosCasa->oroAlmacenado > casaGanadora->oroAlmacenado)) {
				nuevoRey = candidato;
				casaGanadora = recCasas->datosCasa;
				indicadorNuevoRey = indicadorCandidato;
		}

		/* Versión no compacta
		// caso 1: Aún no hay rey asignado
		if (nuevoRey == NULL) {
			nuevoRey = candidato;
			casaGanadora = recCasas->datosCasa;
			indicadorNuevoRey = indicadorCandidato;
		}
		// caso 2: La casa que recorremos supera al actual nuevoRey
		else if (indicadorCandidato > indicadorNuevoRey) {
			nuevoRey = candidato;
			casaGanadora = recCasas->datosCasa;
			indicadorNuevoRey = indicadorCandidato;
		}
		// caso 3: la casa que recorremos empata con el actual nuevoRey
		else if (indicadorCandidato == indicadorNuevoRey && recCasas->datosCasa->oroAlmacenado > casaGanadora->oroAlmacenado)) {
			nuevoRey = candidato;
			casaGanadora = recCasas->datosCasa;
			indicadorNuevoRey = indicadorCandidato;
		}
		*/

		recCasas = recCasas->sig;
	}

	return nuevoRey;
}

int desenlazarLord(struct NodoCasa **head, struct Lord *lord) {

}

void EliminarReyActual(struct TronoDeHierro *corona) {
	if (corona == NULL) return;

	struct Lord *nuevoRey;

	nuevoRey = elegirNuevoRey(corona);

	desenlazarLord(&corona->casas, nuevoRey);

	corona->rey = nuevoRey;
}