#include <stdlib.h>

#define maxCiudades 10000

struct Candidato {
	int numero;
	char *nombre;
	char *partidoPolitico;
};

struct NodoCandidato { // lista circular
	struct Candidato *candidato;
	struct NodoCandidato *sig;
};

struct Votante {
	int id;
	char *nombre;
	struct Candidato *voto;
};

struct NodoVotante { // uso de nodo fantasma
	struct Votante *votante;
	struct NodoVotante *sig;
};

struct Ciudad {
	int numeroUnico;
	char *nombre;
	char *nombreAlcalde;
	struct NodoVotante *votantes;
};

struct Pais {
	char *nombrePresidente;
	char *nombre;
	struct Ciudad **ciudades;
	struct NodoCandidato *candidatos;
};

int votosCandidatoCiudad(struct NodoVotante *votantes, struct Candidato *candidato) {
	int votos = 0;
	votantes = votantes->sig;

	while (votantes != NULL) {
		if (votantes->votante->voto == candidato)
			votos++;

		votantes = votantes->sig;
	}

	return votos;
}

int votosCandidatoPais(struct Ciudad **ciudades, struct Candidato *candidato) {
	int i, votos = 0;

	for (i = 0; i < maxCiudades; i++)
		votos += votosCandidatoCiudad(ciudades[i]->votantes, candidato);

	return votos;
}

int maxVotos(struct Ciudad **ciudades, struct NodoCandidato *headCandidatos) {
	int topVotos = 0;
	struct NodoCandidato *rec = headCandidatos;

	do {
		int votosCandidato = votosCandidatoPais(ciudades, rec->candidato);

		if (votosCandidato > topVotos)
			topVotos = votosCandidato;

		rec = rec->sig;
	} while (rec != headCandidatos);

	return topVotos;
}

int cantidadEmpatados(struct Ciudad **ciudades, struct NodoCandidato *headCandidatos, int topVotos) {
	int nEmpatados = 0;
	struct NodoCandidato *rec = headCandidatos;

	do {
		if (votosCandidatoPais(ciudades, rec->candidato) == topVotos)
			nEmpatados++;

		rec = rec->sig;
	} while (rec != headCandidatos);

	return nEmpatados;
}

void poblarEmpatados(struct Candidato **empatados, struct Ciudad **ciudades, struct NodoCandidato *headCandidatos, int topVotos) {
	int iEmpatados = 0;
	struct NodoCandidato *rec = headCandidatos;

	do {
		if (votosCandidatoPais(ciudades, rec->candidato) == topVotos)
			empatados[iEmpatados++] = rec->candidato;

		rec = rec->sig;
	} while (rec != headCandidatos);
}

struct Candidato **candidatosMasVotados(struct Pais *pais) {
	int topVotos = maxVotos(pais->ciudades, pais->candidatos);
	int nEmpatados = cantidadEmpatados(pais->ciudades, pais->candidatos, topVotos);

	if (nEmpatados == 0) return NULL;

	struct Candidato **empatados = (struct Candidato **)malloc(nEmpatados * sizeof(struct Candidato *));

	if (empatados == NULL) return NULL;

	poblarEmpatados(empatados, pais->ciudades, pais->candidatos, topVotos);

	return empatados;
}