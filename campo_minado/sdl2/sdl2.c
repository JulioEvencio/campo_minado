//  Bibliotecas
#include <stdio.h>
#include "sdl2.h"

/*  Funcoes */
/*  Inicializacao e finalizacao: SDL, IMG e TTF */
//  Funcao que iniciar: SDL, IMG e TTF
void sdl2_iniciar_SDL2(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao iniciar SDL: %s \n", SDL_GetError());
        exit(1);
    }
    if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) < 0)
    {
        SDL_Quit();
        printf("Erro ao iniciar IMG: %s \n", IMG_GetError());
        exit(1);
    }
    if(TTF_Init() < 0)
    {
        IMG_Quit();
        SDL_Quit();
        printf("Erro ao iniciar TTF: %s \n", TTF_GetError());
        exit(1);
    }
}

//  Funcao que finaliza: SDL, IMG e TTF
void sdl2_finalizar_SDL2(void)
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/*  Funcoes da janela e tela */
//  Funcao que cria uma janela
SDL_Window* sdl2_criar_janela(char nome[], int largura, int altura)
{
    SDL_Window *janela = NULL;
    janela = SDL_CreateWindow(nome, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largura, altura, SDL_WINDOW_SHOWN);
    if(janela == NULL)
    {
        printf("Erro ao criar janela: %s \n", SDL_GetError());;
    }
    return janela;
}

//  Funcao que cria uma tela
SDL_Renderer* sdl2_criar_tela(SDL_Window *janela)
{
    SDL_Renderer *tela = NULL;
    tela = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(tela == NULL)
    {
        printf("Erro ao criar tela: %s \n", SDL_GetError());
    }
    return tela;
}

//  Funcao que limpa a tela com uma cor especifica
void sdl2_limpar_tela(SDL_Renderer *tela, int r, int g, int b)
{
    SDL_SetRenderDrawColor(tela, r, g, b, 255);
    SDL_RenderClear(tela);
}

//  Funcao que atualiza uma tela
void sdl2_atualizar_tela(SDL_Renderer *tela)
{
    SDL_RenderPresent(tela);
}

//  Funcao que libera memoria de uma tela
void sdl2_fechar_tela(SDL_Renderer *tela)
{
    SDL_DestroyRenderer(tela);
    tela = NULL;
}

//  Funcao que libera memoria de uma janela
void sdl2_fechar_janela(SDL_Window *janela)
{
    SDL_DestroyWindow(janela);
    janela = NULL;
}

/*  Funcoes de desenhos geometricos */
//  Funcao que desenha um retangulo na tela
void sdl2_desenhar_retangulo(SDL_Renderer *tela, SDL_Rect retangulo, int x, int y, int largura, int altura, int r, int g, int b)
{
    SDL_SetRenderDrawColor(tela, r, g, b, 255);
    retangulo.x = x;
    retangulo.y = y;
    retangulo.w = largura;
    retangulo.h = altura;
    SDL_RenderFillRect(tela, &retangulo);
}

/*  Funcoes de arquivos .png e .jpg */
//  Funcao que carrega uma imagem .png/.jpg e transforma em uma textura usavel
SDL_Texture* sdl2_carregar_textura(SDL_Renderer *tela, char arquivo[])
{
    SDL_Surface *imagem = NULL;
    SDL_Texture *textura = NULL;
    imagem = IMG_Load(arquivo);
    if(imagem == NULL)
    {
        printf("Erro ao abrir arquivo: %s \n", IMG_GetError());
        return textura;
    }
    textura = SDL_CreateTextureFromSurface(tela, imagem);
    if(textura == NULL)
    {
        printf("Erro ao criar textura: %s \n", SDL_GetError());
    }
    SDL_FreeSurface(imagem);
    imagem = NULL;
    return textura;
}

//  Funcao que desenha uma textura na tela
void sdl2_desenhar_textura(SDL_Renderer *tela, SDL_Texture *textura, int x, int y, int largura, int altura)
{
    SDL_Rect desenho = {x, y, largura, altura};
    SDL_RenderCopy(tela, textura, NULL, &desenho);
}

//  Funcao que libera memoria de uma textura
void sdl2_fechar_textura(SDL_Texture *textura)
{
    SDL_DestroyTexture(textura);
    textura = NULL;
}

/*  Funcoes TTF */
//  Funcao que carrega uma fonte TTF
TTF_Font* sdl2_carregar_fonte(char arquivo[], int tamanho)
{
    TTF_Font *fonte = NULL;
    fonte = TTF_OpenFont(arquivo, tamanho);
    if(fonte == NULL)
    {
        printf("Erro ao abrir arquivo: %s \n", TTF_GetError());
    }
    return fonte;
}

//  Funcao que exibi um texto solid
int sdl2_exibir_texto_solid(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b)
{
    SDL_Surface *texto = NULL;
    SDL_Texture *texto_textura = NULL;
    SDL_Color fonte_cor = {r, g, b};
    texto = TTF_RenderText_Solid(fonte, mensagem, fonte_cor);
    if(texto == NULL)
    {
        printf("erro ao gerar mensagem: %s \n", TTF_GetError());
        return 0;
    }
    texto_textura = SDL_CreateTextureFromSurface(tela, texto);
    if(texto_textura == NULL)
    {
        SDL_FreeSurface(texto);
        texto = NULL;
        printf("Erro ao gerar textura para texto: %s \n", SDL_GetError());
        return 0;
    }
    SDL_Rect desenho = {x, y, largura, altura};
    SDL_RenderCopy(tela, texto_textura, NULL, &desenho);
    SDL_FreeSurface(texto);
    texto = NULL;
    sdl2_fechar_textura(texto_textura);
    return 1;
}

//  Funcao que exibi um texto shaded
int sdl2_exibir_texto_shaded(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b, int R, int G, int B)
{
    SDL_Surface *texto = NULL;
    SDL_Texture *texto_textura = NULL;
    SDL_Color fonte_cor = {r, g, b};
    SDL_Color fonte_fundo = {R, G, B};
    texto = TTF_RenderText_Shaded(fonte, mensagem, fonte_cor, fonte_fundo);
    if(texto == NULL)
    {
        printf("erro ao gerar mensagem: %s \n", TTF_GetError());
        return 0;
    }
    texto_textura = SDL_CreateTextureFromSurface(tela, texto);
    if(texto_textura == NULL)
    {
        SDL_FreeSurface(texto);
        texto = NULL;
        printf("Erro ao gerar textura para texto: %s \n", SDL_GetError());
        return 0;
    }
    SDL_Rect desenho = {x, y, largura, altura};
    SDL_RenderCopy(tela, texto_textura, NULL, &desenho);
    SDL_FreeSurface(texto);
    texto = NULL;
    sdl2_fechar_textura(texto_textura);
    return 1;
}

//  Funcao que exibi um texto blended
int sdl2_exibir_texto_blended(SDL_Renderer *tela, TTF_Font *fonte, char mensagem[], int x, int y, int largura, int altura, int r, int g, int b)
{
    SDL_Surface *texto = NULL;
    SDL_Texture *texto_textura = NULL;
    SDL_Color fonte_cor = {r, g, b};
    texto = TTF_RenderText_Blended(fonte, mensagem, fonte_cor);
    if(texto == NULL)
    {
        printf("erro ao gerar mensagem: %s \n", TTF_GetError());
        return 0;
    }
    texto_textura = SDL_CreateTextureFromSurface(tela, texto);
    if(texto_textura == NULL)
    {
        SDL_FreeSurface(texto);
        texto = NULL;
        printf("Erro ao gerar textura para texto: %s \n", SDL_GetError());
        return 0;
    }
    SDL_Rect desenho = {x, y, largura, altura};
    SDL_RenderCopy(tela, texto_textura, NULL, &desenho);
    SDL_FreeSurface(texto);
    texto = NULL;
    sdl2_fechar_textura(texto_textura);
    return 1;
}

//  Funcao que libera memoria das fontes
void sdl2_fechar_fonte(TTF_Font *fonte)
{
    TTF_CloseFont(fonte);
    fonte = NULL;
}