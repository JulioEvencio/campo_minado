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

//  Matriz do campo minado
int M[10][10];

//  Funcoes
void graficos(void);
void logica(void);
void desenhar_campo_minado(void);
int preencher_matriz(void);

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

        //  Logica
        logica();

        //  Graficos
        graficos();
    }

    //  Encerrando SDL e SDL IMAGE
    IMG_Quit();
    SDL_Quit();

    return 0;
}

//  Funcao responsavel pela logica do jogo
void logica(void)
{
    preencher_matriz();
}

//  Funcao responsavel pela tela do jogo
void graficos(void)
{
    //  Definindo cor preta para o fundo
    SDL_SetRenderDrawColor(tela, 255, 255, 255, 255);
    SDL_RenderClear(tela);

    //  Desenhando campo minado
    desenhar_campo_minado();

    //  Atualizando a tela
    SDL_RenderPresent(tela);
}

//  Funcao que desenha o campo minado
void desenhar_campo_minado(void)
{
    int linha, coluna, quadrado_x, quadrado_y, quadrado_comp = (comprimento / 10), quadrado_alt = (altura / 10);
    for(linha = 0; linha < 10; linha++)
    {
        for(coluna = 0; coluna < 10; coluna++)
        {
            //  Definindo cor do quadrado
            if((linha + coluna) % 2 == 0)
            {
                //  Definindo cor branca para uma parte dos quadrados
                SDL_SetRenderDrawColor(tela, 0, 0, 0, 0);
            }
            else
            {
                //  Definindo cor azul (com verde) para os quadrados restantes
                SDL_SetRenderDrawColor(tela, 255, 255, 255, 255);
            }
            //  Calculo de onde iniciara cada quadrado na tela
            quadrado_x = coluna * quadrado_comp;
            quadrado_y = linha * quadrado_alt;
            //  Criando de fato os quadrados
            SDL_Rect quadrado = {quadrado_x, quadrado_y, quadrado_comp, quadrado_alt};
            //  Pintando de fato o quadrado na tela
            SDL_RenderFillRect(tela, &quadrado);
        }
    }
}

//  Funcao que preenche a matriz do campo minado
int preencher_matriz(void)
{
    int linha, coluna, bombas = 0;
    for(linha = 0; linha < 10; linha++)
    {
        for(coluna = 0; coluna < 10; coluna++)
        {
            if((linha == 0 || linha == 9) || (coluna == 0 || coluna == 9))
            {
                M[linha][coluna] = -1;
            }
            else
            {
                if((rand() % 10) % 2 == 0)
                {
                    M[linha][coluna] = 9;
                    bombas++;
                }
                else
                {
                    M[linha][coluna] = 0;
                }

            }

        }
    }
    return bombas;
}
