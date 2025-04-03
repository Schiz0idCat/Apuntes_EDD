#include <stdio.h>
#include <string.h>

#define MAX_USERS 10000
#define MAX_ADMINS 20

#define MAX_A 1000
#define MAX_B 500
#define MAX_C 50

struct Video {
	int id;
	char *nombreVideo;
	char *fechaPublicacion;
	char *tipoContenido;
	int segundos;
	int minutos;
	int comentarios;
	char *estadoVideo;
};

struct Usuario {
	int id;
	char *username;
	char tipoCuenta;
	struct Video **videosSubidos;
	int cantVideosSubidos;
	int infracciones;
};

struct Admin {
	int id;
	char *username;
	int nivelAcceso;
	struct Video **videosModerados;
	int cantVideosModerados;
};

struct INFTube {
	struct Usuario **usuarios;
	struct Admin **administradores;
};

int procesarVideosInfracciones(struct Usuario *usuario) {
	if (usuario == NULL || usuario->videosSubidos == NULL) return 1;

	int maxVideos, i;

	// detectar el largo del array
	switch (usuario->tipoCuenta) {
		case 'A':
			maxVideos = MAX_A;
			break;
		case 'B':
			maxVideos = MAX_B;
			break;
		case 'C':
			maxVideos = MAX_C;
			break;
		default:
			return 1;
	}

	for (i = 0; i < maxVideos; i++) { // recorriendo la lista de videos
		if (usuario->videosSubidos[i] == NULL) continue;

		if (strcmp(usuario->videosSubidos[i]->estadoVideo, "Infraccion") != 0) continue;

		usuario->videosSubidos[i] = NULL;
		usuario->infracciones++;
	}

	return 0;
}

int quitarVideosInfraccion(struct INFTube *itube) {
	if (itube == NULL || itube->usuarios == NULL) return 1;

	int i;

	for (i = 0; i < MAX_USERS; i++) { // recorriendo la lista de usuarios
		if (itube->usuarios[i] == NULL) continue;

		procesarVideosInfracciones(itube->usuarios[i]); // analizar si el usuario tiene videos con infracciones

		if (itube->usuarios[i]->infracciones <= 3) continue;

		itube->usuarios[i] = NULL;
	}

	return 0;
}

int main() {
	struct INFTube *itube;
}