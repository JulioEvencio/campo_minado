/*
    Campo Minado versao 2.0
*/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cabecalho.h"

int main(void) {
    //  Code

    if (SDLInit(SDL_INIT_VIDEO)) {
        puts("Erro ao inicializar SDL 2...");
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG)) {
        puts("Erro ao inicializar SDL IMAGE...");
        SDL_Quit();
        return 1;
    }

    //  Code

    IMG_Quit();
    SDL_Quit();

    return 0;
}