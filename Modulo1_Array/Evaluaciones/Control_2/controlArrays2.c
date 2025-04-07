#include <stdlib.h>

struct Video {
	int duracion; // en segundos
	char *fecha; // DD-MM-AA
};

struct Usuario {
	char *nombreUsuario;
	struct Video **videos;
	int totalVideos;
};

struct TokTok {
	struct Usuario **usuarios;
	int totalUsuarios;
};

int hayVideoLargo(struct Usuario *usuario, int duracionReferencia) {
	if (usuario == NULL || usuario->videos == NULL) return 0;

	int i;

	for (i = 0; i < usuario->totalVideos; i++) { // se recorre el array de videos
		if (usuario->videos[i] == NULL) continue;

		if (usuario->videos[i]->duracion > duracionReferencia)
			return 1;
	}

	return 0;
}

int contarUsuariosConVideosLargos(struct TokTok *plataforma) {
	if (plataforma == NULL || plataforma->usuarios == NULL) return 0;

	int i, count, duracionReferencia;

	count = 0;
	duracionReferencia = 3600; // 3600 segundos = 1 hora

	for (i = 0; i < plataforma->totalUsuarios; i++) { // se recorre el array de usuarios
		if (plataforma->usuarios[i] == NULL) continue;

		if (hayVideoLargo(plataforma->usuarios[i], duracionReferencia) == 1) count++;
	}

	return count;
}

struct Usuario *usuarioVideoMasLargo(struct TokTok *plataforma) {
	if (plataforma == NULL || plataforma->usuarios == NULL) return NULL;

	int i, j, duracionMayor;
	struct Usuario *usuarioDuracionMayor;

	duracionMayor = 0;
	usuarioDuracionMayor = NULL;

	for (i = 0; i < plataforma->totalUsuarios; i++) {
		if (plataforma->usuarios[i] == NULL) continue;

		for (j = 0; j < plataforma->usuarios[i]->totalVideos; j++) {
			if (plataforma->usuarios[i]->videos[j] == NULL) continue;

			if (plataforma->usuarios[i]->videos[j]->duracion > duracionMayor) {
				duracionMayor = plataforma->usuarios[i]->videos[j]->duracion;
				usuarioDuracionMayor = plataforma->usuarios[i];
			}
		}
	}

	return usuarioDuracionMayor;
}