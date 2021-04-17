/*
    Implementacao de funcoes genericas
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cabecalho.h"
#include "tabuleiro.h"

void exibir_textura(SDL_Renderer *tela, SDL_Texture *textura[], int valor, int x, int y, int largura, int altura);

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

void exibir_graficos(SDL_Renderer *tela, SDL_Texture *textura[], Tabuleiro **tabuleiro) {
    int quadrado_x, quadrado_y;
    int quadrado_largura = JANELA_LARGURA / MATRIZ_COLUNA;
    int quadrado_altura = JANELA_ALTURA / MATRIZ_LINHA;

    for (int linha = 0; linha < MATRIZ_LINHA; linha++) {

        for (int coluna = 0; coluna < MATRIZ_COLUNA; coluna++) {

            quadrado_x = coluna * quadrado_largura;
            quadrado_y = linha * quadrado_altura;

            exibir_textura(
                tela,
                textura,
                obter_valor(tabuleiro, linha, coluna),
                quadrado_x,
                quadrado_y,
                quadrado_largura,
                quadrado_altura
            );

        }

    }
}

void exibir_textura(SDL_Renderer *tela, SDL_Texture *textura[], int valor, int x, int y, int largura, int altura) {
    SDL_Rect retangulo = {x, y, largura, altura};

    SDL_RenderCopy(tela, textura[valor], NULL, &retangulo);
}

int clicar_mouse(SDL_Event *evento, Tabuleiro **tabuleiro, int linha_mouse, int coluna_mouse) {
    if (evento->button.button == SDL_BUTTON_LEFT) {
        if (abrir_posicao(tabuleiro, linha_mouse, coluna_mouse)) return -1;
    }

    if (evento->button.button == SDL_BUTTON_RIGHT) {
        //colocar_bandeira(linha_mouse, coluna_mouse);
    }

    return 0;
}