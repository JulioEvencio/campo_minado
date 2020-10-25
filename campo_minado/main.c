/*
    Campo minado
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//  Variaveis
const int comprimento = 640;
const int altura = 640;
bool loop = true;

//  Funcoes
void carregar_imagem(void);
void logica(void);
void graficos(void);

//  Variaveis SDl
SDL_Window *janela = NULL;
SDL_Renderer *tela = NULL;
SDL_Surface *imagem = NULL;
//  Variaveis das imagens
SDL_Texture *zero = NULL;
SDL_Texture *um = NULL;
SDL_Texture *dois = NULL;
SDL_Texture *tres = NULL;
SDL_Texture *quatro = NULL;
SDL_Texture *cinco = NULL;
SDL_Texture *seis = NULL;
SDL_Texture *sete = NULL;
SDL_Texture *oito = NULL;
SDL_Texture *bomba = NULL;

SDL_Event evento;

int main()
{
    //  Iniciando SDL e SDL IMAGE
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    //  Criando janela e tela
    janela = SDL_CreateWindow("Campo Minado", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, comprimento, altura, 0);
    tela = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //  Carregar imagens em suas variaveis
    carregar_imagem();

    //  Loop do jogo
    while(loop)
    {
        //  Verificando se algum evento ocorreu
        while(SDL_PollEvent(&evento) != 0)
        {
            //  Verificando qual evento ocorreu
            //  Click no X da janela
            if(evento.type == SDL_QUIT)
            {
                loop = false;
            }
        }

        //  Logica
        logica();

        //  Graficos
        graficos();
    }

    //  Finalizando SDL e SDL IMAGE
    SDL_DestroyRenderer(tela);
    SDL_DestroyWindow(janela);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

//  Funcao que cria texturas das imagens e as colocam em suas devidas variaveis
void carregar_imagem(void)
{
    //  Numero zero
    imagem = IMG_Load("imagem/zero.png");
    zero = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero um
    imagem = IMG_Load("imagem/um.png");
    um = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero dois
    imagem = IMG_Load("imagem/dois.png");
    dois = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero tres
    imagem = IMG_Load("imagem/tres.png");
    tres = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero quatro
    imagem = IMG_Load("imagem/quatro.png");
    quatro = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero cinco
    imagem = IMG_Load("imagem/cinco.png");
    cinco = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero seis
    imagem = IMG_Load("imagem/seis.png");
    seis = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero sete
    imagem = IMG_Load("imagem/sete.png");
    sete = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Numero oito
    imagem = IMG_Load("imagem/oito.png");
    oito = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Bomba
    imagem = IMG_Load("imagem/mina.png");
    bomba = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);
}

//  Funcao responsavel pela logica do programa
void logica(void)
{
    //  Code
}

//  Funcao responsavel pelos graficos do programa
void graficos(void)
{
    //  Definindo plano de fundo da janela
    SDL_SetRenderDrawColor(tela, 0, 0, 0, 0);
    SDL_RenderClear(tela);

    //  Pintando o zero na tela
    SDL_Rect zero_img = {50, 50, 100, 100};
    SDL_RenderCopy(tela, cinco, NULL, &zero_img);

    //  Atualizando tela
    SDL_RenderPresent(tela);
}
