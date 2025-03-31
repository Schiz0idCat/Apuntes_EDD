#include <stdio.h>
#include <string.h>

#define maxArreglo 100000

struct Usuario {
	char *userId;
	char *username;
};

struct Juego {
	char *nombreJuego;
	int maxApuesta;
};

struct Bet {
	struct Usuario *usuario;
	struct Juego *juego;
	int montoApostado;
	int resultado;
};

struct Casino {
	char *nombreGerente;
	struct Bet **bets;
};

int cantidadApuestasUsuario(struct Casino *casino, char *userId) {
	if (casino == NULL || userId == NULL || casino->bets == NULL) return 0;

	int i, totalApuestas;

	totalApuestas = 0;

	for (i = 0; i < maxArreglo; i++) { // se recorre el array de apuestas
		if (casino->bets[i] == NULL ||					// se revisa si la posición i-ésima es nula
			casino->bets[i]->usuario == NULL ||			// se revisa si la estructura usuario es nula
			casino->bets[i]->usuario->userId == NULL)	// se revisa si el puntero a char es nulo
				continue;								// si algo es true, se pasa a la siguiente iteración

		if (strcmp(casino->bets[i]->usuario->userId, userId) == 0)
			totalApuestas++;
	}

	return totalApuestas;
}

float promedioMontoPorJuego(struct Casino *casino, char *nombreJuego) {
	if (casino == NULL || nombreJuego == NULL || casino->bets == NULL) return 0.0f;

	int i, totalApostado, totalApuestas;

	totalApostado = 0;
	totalApuestas = 0;

	for (i = 0; i < maxArreglo; i++) {
		if (casino->bets[i] == NULL ||						// se revisa si la posición i-ésima es nula
			casino->bets[i]->juego == NULL ||				// se revisa si la estructura es nula
			casino->bets[i]->juego->nombreJuego == NULL)	// se revisa si el puntero a char es nulo
				continue;									// si algo es true, se pasa a la siguiente iteración

		if (strcmp(casino->bets[i]->juego->nombreJuego, nombreJuego) == 0) {
			totalApostado += casino->bets[i]->montoApostado;
			totalApuestas++;
		}
	}

	if (totalApuestas > 0)
		return (float)totalApostado / (float)totalApuestas;

	return 0.0f;
}