/*
    Campo minado
*/

//  Bibliotecas
#include "cabecalho.h"
#include "sdl2/sdl2.c"
#include "funcoes.c"

//  Funcoes
void carregar_imagem(void);
void logica(void);
void graficos(void);
int preencher_matriz(void);
void pintar_matriz(void);
void pintar_imagens(int matriz, int x, int y, int comp, int alt);
void verificador_de_bombas(void);
void abrir_posicao(int x, int y);
void colocar_bandeira(int x, int y);
void clicar_mouse(void);
void perder_jogo(void);

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
SDL_Texture *bomba_explodida = NULL;
SDL_Texture *bandeira = NULL;
SDL_Texture *bloco = NULL;
SDL_Texture *borda = NULL;

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
    sdl2_iniciar_SDL2();

    //  Criando janela
    if((janela = sdl2_criar_janela(JANELA_NOME, JANELA_COMPRIMENTO, JANELA_ALTURA)) == NULL)
    {
        printf("Erro ao criar janela! \n");
        exit(1);
    }

    //  Criando tela
    if((tela = sdl2_criar_tela(janela)) == NULL)
    {
        printf("Erro ao criar tela \n");
        exit(1);
    }

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
            //  Verificando se  o usuario apertou uma tecla
            if(evento.type == SDL_KEYDOWN)
            {
                //  Tecla Esc
                if(evento.key.keysym.sym == SDLK_ESCAPE)
                {
                    preencher_matriz();
                    verificador_de_bombas();
                }
            }
            //  Verificando se o usuario clicou
            if(evento.type == SDL_MOUSEBUTTONDOWN)
            {
                //  Pegando a posicao do mouse
                coluna_mouse = evento.motion.x / (JANELA_COMPRIMENTO / MATRIZ_TAMANHO);
                linha_mouse = evento.motion.y / (JANELA_ALTURA / MATRIZ_TAMANHO);
                clicar_mouse();
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
    sdl2_fechar_tela(tela);
    sdl2_fechar_janela(janela);
    sdl2_finalizar_SDL2();

    return 0;
}

//  Funcao que cria texturas das imagens e as colocam em suas devidas variaveis
void carregar_imagem(void)
{
    //  Numero zero
    zero = sdl2_carregar_textura(tela, "imagem/zero.png");

    //  Numero um
    um = sdl2_carregar_textura(tela, "imagem/um.png");

    //  Numero dois
    dois = sdl2_carregar_textura(tela, "imagem/dois.png");

    //  Numero tres
    tres = sdl2_carregar_textura(tela, "imagem/tres.png");

    //  Numero quatro
    quatro = sdl2_carregar_textura(tela, "imagem/quatro.png");

    //  Numero cinco
    cinco = sdl2_carregar_textura(tela, "imagem/cinco.png");

    //  Numero seis
    seis = sdl2_carregar_textura(tela, "imagem/seis.png");

    //  Numero sete
    sete = sdl2_carregar_textura(tela, "imagem/sete.png");

    //  Numero oito
    oito = sdl2_carregar_textura(tela, "imagem/oito.png");

    //  Bomba
    bomba = sdl2_carregar_textura(tela, "imagem/mina.png");

    //  Bomba Explodida
    bomba_explodida = sdl2_carregar_textura(tela, "imagem/mina_vermelha.png");

    //  Bandeira
    bandeira = sdl2_carregar_textura(tela, "imagem/bandeira.png");

    //  Bloco
    bloco = sdl2_carregar_textura(tela, "imagem/bloco.png");

    //  Borda
    borda = sdl2_carregar_textura(tela, "imagem/borda.png");
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
    sdl2_limpar_tela(tela, SDL2_BRANCO);

    //  Pintando matriz na tela
    pintar_matriz();

    //  Atualizando tela
    sdl2_atualizar_tela(tela);
}

//  Funcao que preenche a matriz do campo minado para que ela possa ser jogavel
int preencher_matriz(void)
{
    int linha, coluna, bombas = 0;
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            if((linha == 0 || linha == 9) || (coluna == 0 || coluna == 9))
            {
                Matriz[linha][coluna] = -1;
                Matriz_auxiliar[linha][coluna] = -1;
            }
            else
            {
                Matriz_auxiliar[linha][coluna] = -2;
                if((rand() % 10) < 3)
                {
                    Matriz[linha][coluna] = 9;
                    bombas++;
                }
                else
                {
                    Matriz[linha][coluna] = 0;
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
    int quadrado_comp = (JANELA_COMPRIMENTO / MATRIZ_TAMANHO), quadrado_alt = (JANELA_ALTURA / MATRIZ_TAMANHO);
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
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
    //  Bandeira
    if(matriz == -3)
    {
        sdl2_desenhar_textura(tela, bandeira, x, y, comp, alt);
    }
    //  Parte de dentro invisivel
    if(matriz == -2)
    {
        sdl2_desenhar_textura(tela, bloco, x, y, comp, alt);
    }
    //  Borda
    if(matriz == -1)
    {
        sdl2_desenhar_textura(tela, borda, x, y, comp, alt);
    }
    //  Bomba Explodida
    if(matriz == -4)
    {
        sdl2_desenhar_textura(tela, bomba_explodida, x, y, comp, alt);
    }
    //  Bombas
    if(matriz == 9)
    {
        sdl2_desenhar_textura(tela, bomba, x, y, comp, alt);
    }
    //  Numero 0
    if(matriz == 0)
    {
        sdl2_desenhar_textura(tela, zero, x, y, comp, alt);
    }
    //  Numero 1
    if(matriz == 1)
    {
        sdl2_desenhar_textura(tela, um, x, y, comp, alt);
    }
    //  Numero dois
    if(matriz == 2)
    {
        sdl2_desenhar_textura(tela, dois, x, y, comp, alt);
    }
    //  Numero tres
    if(matriz == 3)
    {
        sdl2_desenhar_textura(tela, tres, x, y, comp, alt);
    }
    //  Numero quatro
    if(matriz == 4)
    {
        sdl2_desenhar_textura(tela, quatro, x, y, comp, alt);
    }
    //  Numero cinco
    if(matriz == 5)
    {
        sdl2_desenhar_textura(tela, cinco, x, y, comp, alt);
    }
    //  Numero seis
    if(matriz == 6)
    {
        sdl2_desenhar_textura(tela, seis, x, y, comp, alt);
    }
    //  Numero sete
    if(matriz == 7)
    {
        sdl2_desenhar_textura(tela, sete, x, y, comp, alt);
    }
    //  Numero oito
    if(matriz == 8)
    {
        sdl2_desenhar_textura(tela, oito, x, y, comp, alt);
    }
}

//  Funcao que verifica quantas bombas ha nos lugares adjacentes aos locais vazios
void verificador_de_bombas(void)
{
    int linha, coluna, numero_de_bombas;
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
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
    //  Verificando se o local esta marcado com bandeira
    if(Matriz_auxiliar[x][y] != -3)
    {
        Matriz_auxiliar[x][y] = Matriz[x][y];
        //  Verificando se o usuario perdeu
        if(Matriz[x][y] == 9)
        {
            perder_jogo();
        }
    }
}

//  Funcao que coloca ou retira a bandeira
void colocar_bandeira(int x, int y)
{
    //  Verificando se o local e valido
    if(Matriz_auxiliar[x][y] == -2)
    {
        Matriz_auxiliar[x][y] = -3;
    }
    else
    {
        //  Removendo bandeira
        if(Matriz_auxiliar[x][y] == -3)
        {
            Matriz_auxiliar[x][y] = -2;
        }
    }
}

//  Funcao que ativa quando alguem clicar com o mouse
void clicar_mouse(void)
{
    //  Verificando se o botao esquerdo do mouse foi pressionado
    if(evento.button.button == SDL_BUTTON_LEFT)
    {
        abrir_posicao(linha_mouse, coluna_mouse);
    }
    //  Verificando se o botao direito do mouse foi pressionado
    if(evento.button.button == SDL_BUTTON_RIGHT)
    {
        colocar_bandeira(linha_mouse, coluna_mouse);
    }
}

void perder_jogo(void)
{
    int linha, coluna;
    //  Deixando as matrizes iguais para exibir o gabarito do jogo
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            Matriz[linha_mouse][coluna_mouse] = -4;
            Matriz_auxiliar[linha][coluna] = Matriz[linha][coluna];
        }
    }
}
