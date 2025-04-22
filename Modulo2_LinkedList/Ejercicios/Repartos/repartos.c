#include <string.h>

#define maxDestinatarios 5000

struct Destinatario {
    char *rut;
    char *nombre;
    char *direccion;
};

struct Reparto {
    int numero;
    char *fecha;
    char *ciudadOrigen;
    struct Destinatario *destino;
};

struct NodoReparto {
    struct Reparto *datosReparto;
    struct NodoReparto *sig;
};

struct ServiExpress {
    struct NodoReparto *headRepartos;
    struct Destinatario **destinatarios;
};

int contarRepartosDestinatario(struct NodoReparto *head, char *rut) {
    int totalRepartos = 0;

    while (head != NULL) {
        if (strcmp(head->datosReparto->destino->rut, rut) == 0)
            totalRepartos++;

        head = head->sig;
    }

    return totalRepartos;
}

struct Destinatario *destinatarioMayorRepartos(struct ServiExpress *serviExpress) {
    struct Destinatario *masRepartos = NULL;
    int i, cantidadMayorRepartos = 0;

    for (i = 0; i < maxDestinatarios; i++) {
        if (serviExpress->destinatarios[i] == NULL) continue;

        int cantidadAux = contarRepartosDestinatario(serviExpress->headRepartos, serviExpress->destinatarios[i]->rut);

        if (masRepartos == NULL || cantidadAux > cantidadMayorRepartos) {
            masRepartos = serviExpress->destinatarios[i];
            cantidadMayorRepartos = cantidadAux;
        }
    }

    return masRepartos;
}

struct Reparto *quitarRepartoSinNodoFantasma(struct NodoReparto **repartos, int numeroReparto) {
    struct NodoReparto *act = *repartos, *ant = NULL;

    if ((*repartos)->datosReparto->numero == numeroReparto) { // Hay que eliminar el head
        *repartos = (*repartos)->sig;

        return act->datosReparto;
    }

    while (act != NULL && act->datosReparto->numero == numeroReparto) {
        ant = act;
        act = act->sig;
    }

    if (act == NULL) return NULL;

    ant->sig = act->sig;

    return act->datosReparto;
}

struct Reparto *quitarRepartoConNodoFantasma(struct NodoReparto **repartos, int numeroReparto) {
    struct NodoReparto *act = (*repartos)->sig, *ant = (*repartos); // nos saltamos el primer nodo (nodo fantasma)

    while (act != NULL && act->datosReparto->numero == numeroReparto) {
        ant = act;
        act = act->sig;
    }

    if (act == NULL) return NULL;

    ant->sig = act->sig;

    return act->datosReparto;

}
