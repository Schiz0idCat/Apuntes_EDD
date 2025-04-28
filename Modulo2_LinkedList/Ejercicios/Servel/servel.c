#include <stdlib.h>

struct Candidato {
    int idCandidato;
    char *nombre;
    char *nombrePartidoPolitico;
};

struct NodoCandidato {
    struct Candidato *datosCandidato;
    struct NodoCandidato *izq, *der;
};

struct Region {
    int numeroRegion;
    char *nombre;
    struct Votante **votantes;
    int cantMaximaVotantes;
};

struct NodoRegion {
    struct Region *datosRegion;
    struct NodoRegion *sig;
};

struct Votante {
    char *rut;
    char *nombre;
    struct Candidato *voto;
};

struct Servel {
    char *nombreEncargado;
    struct NodoRegion *regiones;
    struct NodoCandidato *candidatos;
};

struct Candidato *buscarCandidato(struct NodoCandidato *head, int idCandidato) {
    while (head != NULL) {
        if (head->datosCandidato->idCandidato == idCandidato)
return head->datosCandidato;

        head = head->der;
    }

    return NULL;
}

int contarVotosRegion(struct Votante **votantes, int max, struct Candidato *candidato) {
    int i, totalVotos = 0;

    for (i = 0; i < max; i++) {
        if (votantes[i] == NULL) continue;

        if (votantes[i]->voto == candidato)
            totalVotos++;
    }

    return totalVotos;
}

int contarVotosPais(struct NodoRegion *head, struct Candidato *candidato) {
    int totalVotos = 0;

    while (head != NULL) {
        totalVotos += contarVotosRegion(head->datosRegion->votantes, head->datosRegion->cantMaximaVotantes, candidato);

        head = head->sig;
    }

    return totalVotos;
}

int contarVotantesRegion(struct Votante **votantes, int max) {
    int i, totalVotantes = 0;

    for (i = 0; i < max; i++) {
        if (votantes[i] != NULL)
            totalVotantes++;
    }

    return totalVotantes;
}

int contarVotantesPais(struct NodoRegion *head) {
    int totalVotantes = 0;

    while (head != NULL) {
        totalVotantes += contarVotantesRegion(head->datosRegion->votantes, head->datosRegion->cantMaximaVotantes);

        head = head->sig;
    }

    return totalVotantes;
}

float porcetajeVotosCandidato(struct Servel *elecciones, int idCandidato) {
    struct Candidato *candidato = buscarCandidato(elecciones->candidatos, idCandidato);

    if (candidato == NULL) return 0.0f;

    int votosCandidato = contarVotosPais(elecciones->regiones, candidato);

    if (votosCandidato == 0) return 0.0f;

    int totalVotos = contarVotantesPais(elecciones->regiones);

    return (float)votosCandidato / (float)totalVotos;
}
