#include <stdio.h>
#include <stdlib.h>
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

void procesarVideosInfracciones(struct Usuario *usuario) {
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
			return;
	}

	for (i = 0; i < maxVideos; i++) { // recorriendo la lista de videos
		struct Video *video;
		video = usuario->videosSubidos[i]; // desempaquetando el video por legibilidad

		if (video == NULL) continue;

		if (strcmp(video->estadoVideo, "Infraccion") != 0) continue;

		video = NULL;
		usuario->infracciones++;
	}
}

void quitarVideosInfraccion(struct INFTube *itube) {
	int i;

	for (i = 0; i < MAX_USERS; i++) { // recorriendo la lista de usuarios
		struct Usuario *usuario;
		usuario = itube->usuarios[i]; // desempaquetando el usuario por legibilidad

		if (usuario == NULL) continue;

		procesarVideosInfracciones(usuario); // analizar si el usuario tiene videos con infracciones

		if (usuario->infracciones <= 3) continue;

		usuario = NULL;
	}
}

int main() {
	struct INFTube *itube;
}