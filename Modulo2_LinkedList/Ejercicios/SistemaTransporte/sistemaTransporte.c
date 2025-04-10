#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define cantViajes 1000

struct Bus {
	char *patente;
	char *marca;
	char *modelo;
	int capacidadTotal;
	char *destino;
};

struct NodoBus {
	struct Bus *datosBus;
	struct NodoBus *sig;
};

struct Pasajero {
	int id;
	char *nombre;
	struct Bus **viajes;
	int pLibre;
};

struct NodoPasajero {
	struct Pasajero *datosPasajero;
	struct NodoPasajero *ant, *sig;
};

struct SistemaTransporte {
	struct NodoBus *headBuses;
	struct NodoPasajero *headPasajeros;
};

int pasajeroEnBus(struct Bus *bus, struct Bus **viajes, int pLibre) {
	if (bus == NULL || viajes == NULL) return 0;

	int i;

	for (i = 0; i < pLibre; i++) {
		if (viajes[i] == NULL) continue;

		if (viajes[i] == bus) return 1;
	}

	return 0;
}

int contarPasajerosEnBus(struct Bus *bus, struct NodoPasajero *headPasajeros) {
	if (bus == NULL || headPasajeros == NULL) return 0;

	struct NodoPasajero *recPasajeros = headPasajeros;
	int pasajerosCount = 0;

	do {
		pasajerosCount += pasajeroEnBus(bus, recPasajeros->datosPasajero->viajes, recPasajeros->datosPasajero->pLibre);
		recPasajeros = recPasajeros->sig;
	} while (recPasajeros != headPasajeros);

	return pasajerosCount;
}

struct Bus *buscarBus(struct NodoBus *headBuses, char *patenteBuscada) {
	if (headBuses == NULL || patenteBuscada == NULL) return NULL;

	while (headBuses != NULL) {
		if (strcmp(headBuses->datosBus->patente, patenteBuscada) == 0)
			return headBuses->datosBus;

		headBuses = headBuses->sig;
	}

	return NULL;
}

int getDisponibilidadADestino(struct NodoBus *headBuses, struct NodoPasajero *headPasajeros, char *destino) {
	if (headBuses == NULL || headPasajeros == NULL || destino == NULL) return 0;

	int espaciosLibres = 0;

	while (headBuses != NULL) {
		if (strcmp(headBuses->datosBus->destino, destino) == 0)
			espaciosLibres += headBuses->datosBus->capacidadTotal + contarPasajerosEnBus(headBuses->datosBus, headPasajeros);

		headBuses = headBuses->sig;
	}

	return espaciosLibres;
}

struct Bus *buscarOtroBusConDisponibilidad(struct NodoBus *headBuses, struct Bus *busVetado, char *destino) {
	if (headBuses == NULL || busVetado == NULL || destino == NULL) return NULL;

	while (headBuses != NULL) {
		if (headBuses->datosBus != busVetado && strcmp(headBuses->datosBus->destino, destino) == 0)
			return headBuses->datosBus;

		headBuses = headBuses->sig;
	}

	return NULL;
}

void reemplazarBusEnPasajero(struct Bus **viajesPasajero, int pLibre, struct Bus *origen, struct Bus *reemplazo) {
	if (viajesPasajero == NULL || origen == NULL || reemplazo  == NULL) return;

	int i;

	for (i = 0; i < pLibre; i++) {
		if (viajesPasajero[i] == NULL) continue;

		if (viajesPasajero[i] == origen) {
			viajesPasajero[i] = reemplazo;
			break;
		}
	}
}

void moverPasajeros(struct NodoPasajero *headPasajeros, struct NodoBus *headBuses, struct Bus *busAveriado) {
	if (headPasajeros == NULL || headBuses == NULL || busAveriado == NULL) return;

	struct NodoPasajero *recPasajeros = headPasajeros;

	do {
		if (pasajeroEnBus(busAveriado, recPasajeros->datosPasajero->viajes, recPasajeros->datosPasajero->pLibre) == 1) {
			struct Bus *busConDisponibilidad = buscarOtroBusConDisponibilidad(headBuses, busAveriado, busAveriado->destino);
			reemplazarBusEnPasajero(recPasajeros->datosPasajero->viajes, recPasajeros->datosPasajero->pLibre, busAveriado, busConDisponibilidad);
		}

		recPasajeros = recPasajeros->sig;
	} while (recPasajeros != headPasajeros);
}

struct Bus *quitarBus(struct NodoBus **headBuses, struct Bus *busQuitar) {
	if (headBuses == NULL || *headBuses == NULL || busQuitar == NULL) return NULL;

	struct NodoBus *actBus = *headBuses;
	struct NodoBus *prevBus = NULL;

	if ((*headBuses)->datosBus == busQuitar) {
		*headBuses = (*headBuses)->sig;

		return actBus->datosBus;
	}

	while (actBus != NULL && actBus->datosBus != busQuitar) {
		prevBus = actBus;
		actBus = actBus->sig;
	}

	if (actBus == NULL) return NULL; // no se encontró el bus

	prevBus->sig = actBus->sig;

	return actBus->datosBus;
}

struct Bus *quitarBusAveriado(struct SistemaTransporte *TMV, char *patenteBus) {
	if (TMV == NULL || patenteBus == NULL) return NULL;

	// 0.- Buscar el bus con dicha patente
	struct Bus *busAveriado = buscarBus(TMV->headBuses, patenteBus);

	if (busAveriado == NULL) return NULL;

	// 1.- Verificar si hay espacio disponible para mover a los pasajeros
	int capacidadTotalDestino = getDisponibilidadADestino(TMV->headBuses, TMV->headPasajeros, busAveriado->destino);

	/* La capacidad real es:
	capacidad real = capacidad total a destino - capacidad libre del bus a eliminar
	capacidad real = capacidad total a destino - (capacidad del bus - capacidad ocupada del bus) */

	int capacidadOcupada = contarPasajerosEnBus(busAveriado, TMV->headPasajeros);
	int capacidadDisponibleEnBus = busAveriado->capacidadTotal - capacidadOcupada;
	capacidadTotalDestino -= capacidadDisponibleEnBus;

	// 2.- Verificar si la capacidad de recepción es mayor o igual a la cantidad de pasajeros en el bus averiado
	if (capacidadTotalDestino < capacidadOcupada) return NULL;

	moverPasajeros(TMV->headPasajeros, TMV->headBuses, busAveriado);

	// 3.- Quitar el bus
	return quitarBus(&TMV->headBuses, busAveriado);
}

// PD: ejercicio QLO, no se lo deseo ni a mi peor enemigo