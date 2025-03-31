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
		struct Video *video;
		video = usuario->videosSubidos[i]; // desempaquetando el video por legibilidad

		if (video == NULL) continue;

		if (strcmp(video->estadoVideo, "Infraccion") != 0) continue;

		video = NULL;
		usuario->infracciones++;
	}

	return 0;
}

int quitarVideosInfraccion(struct INFTube *itube) {
	if (itube == NULL) return 1;

	int i;

	for (i = 0; i < MAX_USERS; i++) { // recorriendo la lista de usuarios
		struct Usuario *usuario;
		usuario = itube->usuarios[i]; // desempaquetando el usuario por legibilidad

		if (usuario == NULL) continue;

		procesarVideosInfracciones(usuario); // analizar si el usuario tiene videos con infracciones

		if (usuario->infracciones <= 3) continue;

		usuario = NULL;
	}

	return 0;
}

int main() {
	struct INFTube *itube;
}