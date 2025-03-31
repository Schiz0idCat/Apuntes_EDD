#include <stdio.h>
#include <stdlib.h>

#define MAX_CANCIONES 1000

struct Spotify {
    char *nombreCEO;
    struct Playlist **playlists; // arreglo compacto de tamaño MAX_CANCIONES
    int pLibre;
};

struct Playlist {
    char *nombre;
    char *descripcion;
    struct Cancion **canciones; // arreglo no compacto de tamaño MAX_CANCIONES
};

struct Cancion {
    char *nombre;
    char *artista;
    int duracion; // en segundos
};

int duracionPlaylist(struct Playlist *playlist) {
    if (playlist == NULL || playlist->canciones == NULL) return 0;

    int i, duracion;

    duracion = 0;

    for (i = 0; i < MAX_CANCIONES; i++) {
        if (playlist->canciones[i] == NULL) continue;

        duracion += playlist->canciones[i]->duracion;
    }

    return duracion;
}

int nPlaylistDuracionMayorA(struct Spotify *spotify, int duracionReferencia) {
    if (spotify == NULL || spotify->playlists == NULL) return 0;

    int i, cantidad;

    cantidad = 0;

    for (i = 0; i < spotify->pLibre; i++) {
        if (spotify->playlists[i] == NULL) continue; // esto no es necesario, dado que el array es compacto

        if (duracionPlaylist(spotify->playlists[i]) > duracionReferencia)
            cantidad++;
    }

    return cantidad;
}

int poblarPlaylistLargas(struct Playlist **largas, struct Spotify *spotify, int duracionReferencia) {
    if (largas == NULL || spotify == NULL || spotify->playlists == NULL) return 1;

    int i, iLargas;

    iLargas = 0;

    for (i = 0; i < spotify->pLibre; i++) {
        if (spotify->playlists[i] == NULL) continue;

        if (duracionPlaylist(spotify->playlists[i]) > duracionReferencia) {
            largas[iLargas] = spotify->playlists[i];
            iLargas++;
        }
    }

    return 0;
}

/*
Esta función recibe por parámetro un puntero a Spotify y debe devolver un arreglo
de tamaño exacto de punteros a las Playlists que tienen una duración total mayor a 1 hora.
*/
struct Playlist **getPlaylistsLargas(struct Spotify *spotify) {
    if (spotify == NULL || spotify->playlists == NULL) return NULL;

    int nLargas, duracionReferencia;
    struct Playlist **largas;

    // no es necesario crear esta variable, pero los "números mágicos" son mal vistos en la programación
    duracionReferencia = 3600; // 1 hora = 3600 segundos
    nLargas = nPlaylistDuracionMayorA(spotify, duracionReferencia);

    if (nLargas <= 0) return NULL;

    largas = (struct Playlist **)malloc(nLargas * sizeof(struct Playlist *));

    if (largas == NULL) return NULL;

    poblarPlaylistLargas(largas, spotify, duracionReferencia);

    return largas;
}