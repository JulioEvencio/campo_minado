/*
    Implementacao de funcoes genericas
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cabecalho.h"

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]) {
    SDL_Surface *imagem = NULL;

    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        imagem = IMG_Load(textura_arquivo[i]);
        if (imagem == NULL) return -1;
        textura[i] = SDL_CreateTextureFromSurface(tela, imagem);
        SDL_FreeSurface(imagem);
    }

    return 0;
}

void liberar_texturas(SDL_Texture *textura[]) {
    for (int i = 0; i < TEXTURA_QUANTIDADE; i++) {
        SDL_DestroyTexture(textura[i]);
    }
}