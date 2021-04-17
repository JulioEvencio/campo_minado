/*
    Campo Minado versao 2.0
*/
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cabecalho.h"

int main(void) {
    int loop = 1; // Deixando true o loop
    SDL_Window *janela = NULL;
    SDL_Renderer *tela = NULL;
    SDL_Event evento;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        puts("Erro ao inicializar SDL 2...");
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        puts("Erro ao inicializar SDL IMAGE...");
        SDL_Quit();
        return 1;
    }

    janela = SDL_CreateWindow(
        JANELA_NOME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        JANELA_LARGURA,
        JANELA_ALTURA,
        SDL_WINDOW_SHOWN
    );

    if (janela == NULL) {
        puts("Erro ao criar janela...");
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    tela = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (tela == NULL) {
        puts("Erro ao renderizar tela...");
        SDL_DestroyWindow(janela);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    while (loop) {
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                loop = SAIR;
            }
        }

        SDL_SetRenderDrawColor(tela, 155, 155, 155, 255);
        SDL_RenderClear(tela);

        SDL_RenderPresent(tela);

        SDL_Delay(JANELA_DELAY);
    }

    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}