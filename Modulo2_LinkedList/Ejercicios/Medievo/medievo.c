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

void EliminarReyActual(struct TronoDeHierro *corona) {

}

struct Lord *elegirNuevoRey(struct TronoDeHierro *corona) {

}