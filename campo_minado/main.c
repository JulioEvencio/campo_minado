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
void carregar_imagem(void);
int preencher_matriz(void);
void colocar_imagens_na_matriz(int bomba, int x, int y, int comp, int alt);

//  Variaveis SDL
SDL_Window *janela = NULL;
SDL_Renderer *tela = NULL;
SDL_Surface *imagem = NULL;
SDL_Texture *zero = NULL;
SDL_Texture *um = NULL;
SDL_Texture *dois = NULL;
SDL_Texture *tres = NULL;
SDL_Texture *quatro = NULL;
SDL_Texture *cinco = NULL;
SDL_Texture *seis = NULL;
SDL_Texture *sete = NULL;
SDL_Texture *oito = NULL;
SDL_Texture *mina = NULL;

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

//  Funcao que pega as imagens dos arquivos e as colocam em variaveis usaveis para o programa
void carregar_imagem(void)
{
    //  Zero
    imagem = IMG_Load("imagem/zero.png");
    zero = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Um
    imagem = IMG_Load("imagem/um.png");
    um = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Dois
    imagem = IMG_Load("imagem/dois.png");
    dois = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Tres
    imagem = IMG_Load("imagem/tres.png");
    tres = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Quatro
    imagem = IMG_Load("imagem/quatro.png");
    quatro = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Cinco
    imagem = IMG_Load("imagem/cinco.png");
    cinco = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Seis
    imagem = IMG_Load("imagem/seis.png");
    seis = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Sete
    imagem = IMG_Load("imagem/sete.png");
    sete = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);

    //  Oito
    imagem = IMG_Load("imagem/oito.png");
    oito = SDL_CreateTextureFromSurface(tela, imagem);
    SDL_FreeSurface(imagem);
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

//  Pintando imagens no campo minado
void colocar_imagens_na_matriz(int bomba, int x, int y, int comp, int alt)
{
    if(bomba == 9)
    {
        //  Bomba
        SDL_Rect bomba_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, mina, NULL, &bomba_img);
    }
    if(bomba == 0)
    {
        //  Zero
        SDL_Rect zero_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, zero, NULL, &zero_img);
    }
    if(bomba == 1)
    {
        //  Um
        SDL_Rect um_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, um, NULL, &um_img);
    }
    if(bomba == 2)
    {
        //  Dois
        SDL_Rect dois_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, dois, NULL, &dois_img);
    }
    if(bomba == 3)
    {
        //  tres
        SDL_Rect tres_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, tres, NULL, &tres_img);
    }
    if(bomba == 4)
    {
        //  Quatro
        SDL_Rect quatro_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, quatro, NULL, &quatro_img);
    }
    if(bomba == 5)
    {
        //  Cinco
        SDL_Rect cinco_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, cinco, NULL, &cinco_img);
    }
    if(bomba == 6)
    {
        //  Seis
        SDL_Rect seis_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, seis, NULL, &seis_img);
    }
    if(bomba == 7)
    {
        //  Sete
        SDL_Rect sete_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, sete, NULL, &sete_img);
    }
    if(bomba == 8)
    {
        //  Oito
        SDL_Rect oito_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, oito, NULL, &oito_img);
    }
}
