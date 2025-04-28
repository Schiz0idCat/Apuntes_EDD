#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Auto {
	char *marca;
	int codigoMotor;
};

// Nodo de autos (por si quieres una lista enlazada de autos, opcional)
struct Nodoautos {
	struct Auto *datos;
	struct Nodoautos *sig;
};

struct Pista {
	char *nombrePista;
	char *pais;
	float longitud; // en km
};

struct TiempoPista {
	struct Pista *pista;     // Referencia a la pista
	int tiempo;              // Tiempo en segundos
	struct TiempoPista *sig;
};

struct Piloto {
	char *nombre;
	struct Nodoautos *autoPiloto;
	struct TiempoPista *tiempos; // Lista de tiempos en distintas pistas
};

struct NodoPistas {
	struct Pista *pista;
	struct NodoPistas *sig;
};

struct Campeonato {
	struct Piloto **pilotos;      // Lista de pilotos
	int cantidadPilotos;
	struct NodoPistas *pistas;    // Lista enlazada de pistas
};

int getTiempoPista(struct TiempoPista *head, char *nombrePista) {
	while (head != NULL) {
		if (strcmp(head->pista->nombrePista, nombrePista) == 0)
			return head->tiempo;

		head = head->sig;
	}

	return 0;
}

struct Auto *buscarAutoEnLista(struct Nodoautos *head, int codigo) {
	while (head != NULL) {
		if (head->datos->codigoMotor == codigo)
			return head->datos;
	}

	return NULL;
}

struct Piloto *ganador(struct Campeonato *campeonato, char *nombrePista) {
	int i;
	struct Piloto *ganador = NULL;
	int tiempoGanador = 0;

	for (i = 0; i < campeonato->cantidadPilotos; i++) {
		int tiempoAux = getTiempoPista(campeonato->pilotos[i]->tiempos, nombrePista);

		if (ganador == NULL || tiempoAux < tiempoGanador) {
			ganador = campeonato->pilotos[i];
			tiempoGanador = tiempoAux;
		}
	}

	return ganador;
}

//crea una funcion para detectar un auto con motor ilegal (se ingresara el codigo del motor ilegal)//
struct Auto *Autoilegal(struct Campeonato *campeonato, int codigoIlegal) {
	int i;

	for (i = 0; i < campeonato->cantidadPilotos; i++) {
		struct Auto *ilegal = buscarAutoEnLista(campeonato->pilotos[i]->autoPiloto, codigoIlegal);

		if (ilegal != NULL)
			return ilegal;
	}

	return NULL;
}