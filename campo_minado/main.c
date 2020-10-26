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
int linha_mouse;
int coluna_mouse;
int linha_mov;
int coluna_mov;

//  Matriz do campo minado
int Matriz[10][10];
int Matriz_auxiliar[10][10];

//  Funcoes
void carregar_imagem(void);
void logica(void);
void graficos(void);
int preencher_matriz(void);
void pintar_matriz(void);
void pintar_imagens(int matriz, int x, int y, int comp, int alt);
void verificador_de_bombas(void);
void abrir_posicao(int x, int y);

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
    //  Definindo semente para a funcao rand
    srand(time(NULL));
    //  preenchendo a matriz do campo minado
    preencher_matriz();
    //  Funcao que vai marcar quantas bombas adjacentes ha em locais vazios
    verificador_de_bombas();

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
            //  Verificando se o mouse foi movido
            if(evento.type == SDL_MOUSEMOTION)
            {
                coluna_mov = evento.motion.x / (comprimento / 10);
                linha_mov = evento.motion.y / (altura / 10);
            }
            //  Verificando se o usuario clicou
            if(evento.type == SDL_MOUSEBUTTONDOWN)
            {
                coluna_mouse = evento.motion.x / (comprimento / 10);
                linha_mouse = evento.motion.y / (altura / 10);
            }
        }

        //  Logica
        logica();

        //  Graficos
        graficos();

        //  Delay
        SDL_Delay(60/1000);
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
    //  Funcao que abre as posicoes do campo minado
    abrir_posicao(linha_mouse, coluna_mouse);
}

//  Funcao responsavel pelos graficos do programa
void graficos(void)
{
    //  Definindo plano de fundo da janela
    SDL_SetRenderDrawColor(tela, 0, 0, 0, 255);
    SDL_RenderClear(tela);

    //  Pintando matriz na tela
    pintar_matriz();

    //  Atualizando tela
    SDL_RenderPresent(tela);
}

//  Funcao que preenche a matriz do campo minado para que ela possa ser jogavel
int preencher_matriz(void)
{
    int linha, coluna, bombas = 0;
    for(linha = 0; linha < 10; linha++)
    {
        for(coluna = 0; coluna < 10; coluna++)
        {
            if((linha == 0 || linha == 9) || (coluna == 0 || coluna == 9))
            {
                Matriz[linha][coluna] = -1;
                Matriz_auxiliar[linha][coluna] = -1;
            }
            else
            {
                if((rand() % 10) < 3)
                {
                    Matriz[linha][coluna] = 9;
                    bombas++;
                }
                else
                {
                    Matriz[linha][coluna] = 0;
                }
                //  Quatriculando parte interna da matriz com -2 e -3
                if((linha + coluna) % 2 == 0)
                {
                    Matriz_auxiliar[linha][coluna] = -2;
                }
                else
                {
                    Matriz_auxiliar[linha][coluna] = -3;
                }
            }
        }
    }
    return bombas;
}

//  Funcao que pinta a matriz na tela usando imagens
void pintar_matriz(void)
{
    int linha, coluna, quadrado_x, quadrado_y;
    int quadrado_comp = (comprimento / 10), quadrado_alt = (altura / 10);
    for(linha = 0; linha < 10; linha++)
    {
        for(coluna = 0; coluna < 10; coluna++)
        {
            quadrado_x = coluna * quadrado_comp;
            quadrado_y = linha * quadrado_alt;
            pintar_imagens(Matriz_auxiliar[linha][coluna], quadrado_x, quadrado_y, quadrado_comp, quadrado_alt);
        }
    }
}

//  Funcao auxiliar para pintar o campo minado na tela
void pintar_imagens(int matriz, int x, int y, int comp, int alt)
{
    //  Parte de dentro invisivel 1
    if(matriz == -3)
    {
        SDL_SetRenderDrawColor(tela, 223, 223, 223, 255);
        SDL_Rect quadrado = {x, y, comp, alt};
        SDL_RenderFillRect(tela, &quadrado);
    }
    //  Parte de dentro invisivel 2
    if(matriz == -2)
    {
        SDL_SetRenderDrawColor(tela, 200, 200, 200, 255);
        SDL_Rect quadrado = {x, y, comp, alt};
        SDL_RenderFillRect(tela, &quadrado);
    }
    //  Borda
    if(matriz == -1)
    {
        SDL_SetRenderDrawColor(tela, 112, 135, 179, 255);
        SDL_Rect quadrado = {x, y, comp, alt};
        SDL_RenderFillRect(tela, &quadrado);
    }
    //  Bombas
    if(matriz == 9)
    {
        SDL_Rect bomba_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, bomba, NULL, &bomba_img);
    }
    //  Numero 0
    if(matriz == 0)
    {
        SDL_Rect zero_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, zero, NULL, &zero_img);
    }
    //  Numero 1
    if(matriz == 1)
    {
        SDL_Rect um_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, um, NULL, &um_img);
    }
    //  Numero dois
    if(matriz == 2)
    {
        SDL_Rect dois_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, dois, NULL, &dois_img);
    }
    //  Numero tres
    if(matriz == 3)
    {
        SDL_Rect tres_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, tres, NULL, &tres_img);
    }
    //  Numero quatro
    if(matriz == 4)
    {
        SDL_Rect quatro_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, quatro, NULL, &quatro_img);
    }
    //  Numero cinco
    if(matriz == 5)
    {
        SDL_Rect cinco_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, cinco, NULL, &cinco_img);
    }
    //  Numero seis
    if(matriz == 6)
    {
        SDL_Rect seis_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, seis, NULL, &seis_img);
    }
    //  Numero sete
    if(matriz == 7)
    {
        SDL_Rect sete_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, sete, NULL, &sete_img);
    }
    //  Numero oito
    if(matriz == 8)
    {
        SDL_Rect oito_img = {x, y, comp, alt};
        SDL_RenderCopy(tela, oito, NULL, &oito_img);
    }
}

//  Funcao que verifica quantas bombas ha nos lugares adjacentes aos locais vazios
void verificador_de_bombas(void)
{
    int linha, coluna, numero_de_bombas;
    for(linha = 0; linha < 10; linha++)
    {
        for(coluna = 0; coluna < 10; coluna++)
        {
            numero_de_bombas = 0;
            //  Divisao 1
            if(Matriz[linha][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Divisao 2
            if(Matriz[linha-1][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha-1][coluna] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha-1][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Divisao 3
            if(Matriz[linha+1][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha+1][coluna] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha+1][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Adicionando numeros de bombas na posicao vazia
            if(Matriz[linha][coluna] == 0)
            {
                Matriz[linha][coluna] = numero_de_bombas;
            }
        }
    }
}

//  Funcao que mostra o que ha dentro da posicao clicada
void abrir_posicao(int x, int y)
{
    Matriz_auxiliar[x][y] = Matriz[x][y];
    if(Matriz[x][y] == 9)
    {
        //  printf("Voce clicou em uma bomba! \n");
    }
}
