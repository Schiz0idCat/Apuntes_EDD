#include <stdlib.h>

#define maxInv 4000

struct Administradora {
	int rolUnicoTributario;
	char *nombre;
	char *nombreGerente;
	float clasificadorRiesgo;
};

struct NodoAdministradora { // lista circular
	struct Administradora *detalle;
	struct NodoAdministradora *sig;
};

struct Fondo {
	int id;
	char *fecha;
	int monto;
	struct Administradora *administradora;
};

struct Inversionista {
	char *rut;
	char *nombre;
	struct Fondo **inversiones; // #define maxInv
};

struct NodoInversionista { // nodo fantasma
	struct Inversionista *datosInversionista;
	struct NodoInversionista *ant, *sig;
};

struct SistemaInversiones {
	struct NodoAdministradora *headAdmin; // lista circular simplemente enlazada
	struct NodoInversionista *headInv; // lista doblemente enlazada con nodo fantasma
};

float calcularIGR(struct NodoInversionista *inversionistas, struct Administradora *admin, float tasaInteres) {
	int i, montoTotal = 0;

	struct NodoInversionista *rec = inversionistas->sig;

	while (rec != NULL) {
		struct Inversionista *inv = rec->datosInversionista;

		for (i = 0; i < maxInv; i++) {
			struct Fondo *fondo = inv->inversiones[i];

			if (fondo != NULL && fondo->administradora == admin)
				montoTotal += fondo->monto;
		}

		rec = rec->sig;
	}

	return (float)montoTotal * admin->clasificadorRiesgo * (1.0f / tasaInteres);
}

struct Administradora *adminMayorIGR(struct NodoInversionista *inver, struct NodoAdministradora *admin, float tasaIteres) {
	struct Administradora *adminMayorIGR = admin->detalle;
	float mayorIGR = calcularIGR(inver, adminMayorIGR, tasaIteres);

	struct NodoAdministradora *rec = admin->sig;

	do {
		float IGRActual = calcularIGR(inver, rec->detalle, tasaIteres);

		if (IGRActual > mayorIGR) {
			adminMayorIGR = rec->detalle;
			mayorIGR = IGRActual;
		}

		rec = rec->sig;
	} while (rec != admin);

	return adminMayorIGR;
}

struct Administradora *adminMenorIGR(struct NodoInversionista *inver, struct NodoAdministradora *admin, float tasaIteres) {
	struct Administradora *adminMenorIGR = admin->detalle;
	float menorIGR = calcularIGR(inver, adminMenorIGR, tasaIteres);

	struct NodoAdministradora *rec = admin->sig;

	do {
		float IGRActual = calcularIGR(inver, rec->detalle, tasaIteres);

		if (IGRActual < menorIGR) {
			adminMenorIGR = rec->detalle;
			menorIGR = IGRActual;
		}

		rec = rec->sig;
	} while (rec != admin);

	return adminMenorIGR;
}

struct Administradora *desenlazarAdministradora(struct NodoAdministradora **head, struct Administradora *admin) {
	struct NodoAdministradora *act = *head;

	if ((*head)->detalle == admin) {
		if ((*head)->sig == *head)
			*head = NULL;
		else {
			struct NodoAdministradora *ultimo = *head;

			while (ultimo->sig != *head)
				ultimo = ultimo->sig;

			*head = (*head)->sig;
			ultimo->sig = *head;
		}

		return act->detalle;
	}

	act = (*head)->sig;
	struct NodoAdministradora *ant = (*head);

	while (act != *head) {
		if (act->detalle == admin) {
			ant->sig = act->sig;
			return act->detalle;
		}

		ant = act;
		act = act->sig;
	}

	return NULL;
}

void moverFondos(struct Fondo **fondos, struct Administradora *adminMayorIGR, struct Administradora *adminMenorIGR) {
	int i;
	for (i = 0; i < maxInv; i++) {
		if (fondos [i] != NULL && fondos[i]->administradora == adminMayorIGR)
			fondos[i]->administradora = adminMenorIGR;
	}
}

struct Administradora *quitarAdministradoraRiesgosa(struct SistemaInversiones *SI, float tasaIteres) {
	if (SI->headAdmin == SI->headAdmin->sig) return NULL; // no se hará nada si solo hay una administradora

	struct Administradora *mayorIGR = adminMayorIGR(SI->headInv, SI->headAdmin, tasaIteres);
	struct Administradora *menorIGR = adminMenorIGR(SI->headInv, SI->headAdmin, tasaIteres);

	struct NodoInversionista *rec = SI->headInv->sig;

	while (rec != NULL) {
		moverFondos(rec->datosInversionista->inversiones, mayorIGR, menorIGR);

		rec = rec->sig;
	}

	return desenlazarAdministradora(&SI->headAdmin, mayorIGR);
}