#ifndef SDL2_H_INCLUDED
#define SDL2_H_INCLUDED

//  Bibliotecas
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*  Constantes */
#define SDL2_BRANCO 255,255,255
#define SDL2_PRETO 0,0,0
#define SDL2_VERMELHO 255,0,0
#define SDL2_VERDE 0,128,0
#define SDL2_AZUL 0,0,255
#define SDL2_CINZA 128,128,128
#define SDL2_CIANO 0,255,255
#define SDL2_LIMAO 0,255,0
#define SDL2_MARROM 139,69,19
#define SDL2_ROXO 128,0,128
#define SDL2_MAGENTA 139,0,139
#define SDL2_ROSA 255,20,147
#define SDL2_LARANJA 255,165,0
#define SDL2_AMARELO 255,255,0

/*  Funcoes */
//  Inicializacao e finalizacao: SDL, IMG e TTF
void sdl2_iniciar_SDL2(void);
void sdl2_finalizar_SDL2(void);

//  Funcoes da janela e tela
SDL_Window* sdl2_criar_janela(char nome[], int largura, int altura);
SDL_Renderer* sdl2_criar_tela(SDL_Window *janela);
void sdl2_limpar_tela(SDL_Renderer *tela, int r, int g, int b);
void sdl2_atualizar_tela(SDL_Renderer *tela);
void sdl2_fechar_janela(SDL_Window *janela);
void sdl2_fechar_tela(SDL_Renderer *tela);

//  Funcoes de desenhos geometricos
void sdl2_desenhar_retangulo(SDL_Renderer *tela, SDL_Rect retangulo, int x, int y, int largura, int altura, int r, int g, int b);

//  Funcoes de arquivos .png
SDL_Texture* sdl2_carregar_textura(SDL_Renderer *tela, char arquivo[]);
void sdl2_desenhar_textura(SDL_Renderer *tela, SDL_Texture *textura, int x, int y, int largura, int altura);
void sdl2_fechar_textura(SDL_Texture *textura);

//  Funcoes TTF
TTF_Font* sdl2_carregar_fonte(char arquivo[], int tamanho);
int sdl2_exibir_texto_solid(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b);
int sdl2_exibir_texto_shaded(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b, int R, int G, int B);
int sdl2_exibir_texto_blended(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b);
void sdl2_fechar_fonte(TTF_Font *fonte);

#endif // SDL2_H_INCLUDED