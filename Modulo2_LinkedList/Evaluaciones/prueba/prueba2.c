#include <stdlib.h>

struct Cardenal {
	char *DNI;
	char *nombre;
	int edad;
	int cantidadMisas;
};

struct NodoCardenal { // simplemente enlazada circular
	struct Cardenal *datosCardenal;
	struct NodoCardenal *sig;
};
struct Clero { // array no compacto
	char *nombre; // nombre único
	struct NodoCardenal *cardenales; // simplemente enlazada circular
};

struct Ciudad {
	char *nombre; // nombre único
	char *ubicacion;
	struct Clero **cleros; // array no compacto
	int tamCleros;
};

struct NodoCiudad { // simplemente enlazada con nodo fantasma
	struct Ciudad *datosCiudad;
	struct NodoCiudad *sig;
};

struct Iglesia {
	struct Cardenal *pontifice;
	struct NodoCiudad *ciudades; // simplemente enlazada con nodo fantasma
	struct Cardenal **curia; // array compacto
	int tamCuria;
	int PLibreCuria;
};

void eliminarFlojo(struct NodoCardenal **cardenales, struct Cardenal *cardenalFlojo) {
	if ((*cardenales)->datosCardenal == cardenalFlojo) {
		if (*cardenales == (*cardenales)->sig)
			*cardenales = NULL;
		else {
			struct NodoCardenal *ultimo = *cardenales;

			while (ultimo->sig != *cardenales)
				ultimo = ultimo->sig;

			*cardenales = (*cardenales)->sig;
			ultimo->sig = *cardenales;
		}
	}

	struct NodoCardenal *act = (*cardenales)->sig, *ant = *cardenales;

	while (act != *cardenales) {
		if (act->datosCardenal == cardenalFlojo) {
			ant->sig = act->sig;
			return;
		}

		ant = act;
		act = act->sig;
	}
}

// eliminar al cardenal con menos misas
void eliminarMenosMisas(struct NodoCardenal **cardenales) {
	struct NodoCardenal *cardenalRec = *cardenales;
	struct Cardenal *cardenalMenosMisas = NULL;

	do {
		struct Cardenal *cardenalActual = cardenalRec->datosCardenal;

		if (cardenalMenosMisas == NULL || cardenalActual->cantidadMisas < cardenalMenosMisas->cantidadMisas)
			cardenalMenosMisas = cardenalActual;

		cardenalRec = cardenalRec->sig;
	} while (cardenalRec != *cardenales);

	eliminarFlojo(cardenales, cardenalMenosMisas);
}

// nombrar a un papa (cardenal con más misas)
struct Cardenal *nombrarPapa(struct NodoCardenal **cardenales) {
	struct NodoCardenal *cardenalRec = *cardenales;
	struct Cardenal *cardenalMasMisas = NULL;

	do {
		struct Cardenal *cardenalActual = cardenalRec->datosCardenal;

		if (cardenalMasMisas == NULL || cardenalActual->cantidadMisas > cardenalMasMisas->cantidadMisas)
			cardenalMasMisas = cardenalActual;

		cardenalRec = cardenalRec->sig;
	} while (cardenalRec != *cardenales);

	return cardenalMasMisas;
}

int contarCleros(struct Clero **cleros, int maxCleros) {
	int i, total = 0;

	for (i = 0; i < maxCleros; i++) {
		if (cleros[i] != NULL)
			total++;
	}

	return total;
}

// ciudad con más cleros
char *ciudadMasCleros(struct NodoCiudad *ciudades) {
	char *ciudadMayorCleros = NULL;
	int cantidadMasCleros = 0;

	ciudades = ciudades->sig; // por nodo fantasma
	while (ciudades != NULL) {
		struct Ciudad *ciudadActual = ciudades->datosCiudad;
		int cantidadActual = contarCleros(ciudadActual->cleros, ciudadActual->tamCleros);

		if (ciudadMayorCleros == NULL || cantidadActual > cantidadMasCleros) {
			ciudadMayorCleros = ciudadActual->nombre;
			cantidadMasCleros = cantidadActual;
		}

		ciudades = ciudades->sig;
	}

	return ciudadMayorCleros;
}

// promedio de cleros por ciudad
float promCleros(struct NodoCiudad *ciudades) {
	int totalCleros = 0;
	int totalCiudades = 0;

	ciudades = ciudades->sig;
	while (ciudades != NULL) {
		totalCleros += contarCleros(ciudades->datosCiudad->cleros, ciudades->datosCiudad->tamCleros);
		totalCiudades++;
	}

	if (totalCiudades == 0) return 0.0f;

	return (float)totalCleros / (float)totalCiudades;
}