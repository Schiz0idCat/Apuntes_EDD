#include <stdlib.h>

struct Piloto {
	int id; // único en todo el sistema
	char *nombre;
	int edad;
	float sueldo;
};

struct NodoPiloto {
	struct Piloto *datosPiloto;
	struct NodoPiloto *ant, *sig;
};

struct Tecnico {
	char *nombre;
	int edad;
	char *especialidad;
};

struct Equipo {
	char *nombreJefe;
	int cantidadTecnicos;
	struct Tecnico **tecnicos;
	int pLibreTecnicos;
	struct Piloto *pilotos[3];
};

struct Scuderia {
	char *nombre;
	char *fechaCreacion;
	int campeonatosGanados;
	struct Equipo *equipo;
};

struct NodoScuderia {
	struct Scuderia *datosScuderia;
	struct NodoScuderia *sig;
};

struct Formula1 {
	struct NodoScuderia *headScuderia;
	struct NodoPiloto *headPilotos;
};

struct Piloto *buscarPilotoEnSistema(struct NodoPiloto *head, int id) {
	while (head != NULL) {
		if (head->datosPiloto->id == id)
			return head->datosPiloto;

		head = head->sig;
	}

	return NULL;
}

struct Piloto *modificarEquipo(struct Piloto **pilotos, struct Piloto *saliente, struct Piloto *entrante) {
	int i;

	for (i = 0; i < 3; i++) { // 3 es la cantidad de pilotos en un equipo
		if (pilotos[i] == saliente) {
			pilotos[i] = entrante;
			return saliente;
		}
	}

	return NULL;
}

struct Piloto *AsignarPilotoScuderia(struct Formula1 *f1, int idPilotoSaliente, int idPilotoEntrante) {
	struct Piloto *pilotoSaliente = buscarPilotoEnSistema(f1->headPilotos, idPilotoSaliente);
	struct Piloto *pilotoEntrante = buscarPilotoEnSistema(f1->headPilotos, idPilotoEntrante);

	if (pilotoSaliente == NULL || pilotoEntrante == NULL) return NULL;

	struct NodoScuderia *rec = f1->headScuderia;

	while (rec != NULL) {
		if (modificarEquipo(rec->datosScuderia->equipo->pilotos, pilotoSaliente, pilotoEntrante) == pilotoSaliente)
			return pilotoSaliente;

		rec = rec->sig;
	}

	return NULL;
}