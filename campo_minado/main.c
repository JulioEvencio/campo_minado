/*
    Campo minado
*/
//  Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

//  Variaveis
const int comprimento = 640;
const int altura = 640;
bool loop = true;

//  Funcoes
//  Funcao responsavel pela tela do jogo
void graficos(void);

//  Variaveis SDL
SDL_Window *janela = NULL;
SDL_Renderer *tela = NULL;
SDL_Surface *imagem = NULL;

SDL_Event evento;

int main()
{
    //  Iniciando SDL e SDL IMAGE
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    //  Criando janela e tela
    janela = SDL_CreateWindow("Campo minado", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, comprimento, altura, 0);
    tela = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //  Funcao que vai carregar imagens

    //  Loop do jogo
    while(loop)
    {
        //  Verificando se algum evento ocorreu
        while(SDL_PollEvent(&evento) != 0)
        {
            //  Verificando se o X da janela foi clicado
            if(evento.type == SDL_QUIT)
            {
                loop = false;
            }
        }

        //  Graficos
        graficos();
    }

    //  Encerrando SDL e SDL IMAGE
    IMG_Quit();
    SDL_Quit();

    return 0;
}

//  Funcao responsavel pela tela do jogo
void graficos(void)
{
    //  Definindo cor preta para o fundo
    SDL_SetRenderDrawColor(tela, 255, 255, 255, 255);
    SDL_RenderClear(tela);

    //  Atualizando a tela
    SDL_RenderPresent(tela);
}
