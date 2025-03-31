#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_CANCIONES 1000

struct Spotify {
    /*
    Spotify contiene un arreglo compacto con pLibre a Playlists.
    Además contiene el nombre del CEO.
    */
    char *nombreCEO;
    struct Playlist **playlists;
    int pLibre;
};

struct Playlist {
    /*
    Playlist contiene un arreglo no compacto de tamaño máximo MAX_CANCIONES
    de punteros a Canciones. Además del nombre y descripción.
    */
    char *nombre;
    char *descripcion;
    struct Cancion **canciones;
};

struct Cancion {
    /*
    Cancion contiene el nombre, artista y duración en segundos.
    */
    char *nombre;
    char *artista;
    int duracion; // en segundos
};

/*
Esta función recibe por parámetro un puntero a Spotify y debe devolver un arreglo
de tamaño exacto de punteros a las Playlist que tienen una duración total mayor a 1 hora.
*/
struct Playlist **getPlaylistsLargas(struct Spotify *spotify) {

}

int main(void) {
	printf("Hello, World!\n");
	return 0;
}