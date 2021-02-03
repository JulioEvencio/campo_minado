/*
    Campo minado
*/

//  Bibliotecas
#include "cabecalho.h"
#include "sdl2/sdl2.c"
#include "funcoes.c"

int main()
{   
    /*  Variaveis */
    //  Jogo
    bool loop = true;
    //  Mouse
    int linha_mouse;
    int coluna_mouse;
    //  Matriz do campo minado
    int Matriz[MATRIZ_TAMANHO][MATRIZ_TAMANHO];
    int Matriz_auxiliar[MATRIZ_TAMANHO][MATRIZ_TAMANHO];

    /*  Variaveis SDl */
    //  Janela
    SDL_Window *janela = NULL;
    SDL_Renderer *tela = NULL;
    //  Variaveis das imagens
    SDL_Texture *imagens[IMAGENS_NUMERO];
    //  Evento
    SDL_Event evento;

    //  Vetore de string com o nome dos arquivos das imagens
    static char *imagens_arquivos[IMAGENS_NUMERO] =
    {
        "imagem/zero.png",
        "imagem/um.png",
        "imagem/dois.png",
        "imagem/tres.png",
        "imagem/quatro.png",
        "imagem/cinco.png",
        "imagem/seis.png",
        "imagem/sete.png",
        "imagem/oito.png",
        "imagem/mina.png",
        "imagem/mina_vermelha.png",
        "imagem/bandeira.png",
        "imagem/bloco.png",
        "imagem/borda.png"
    };

    //  Definindo semente para a funcao rand
    srand(time(NULL));
    //  preenchendo a matriz do campo minado
    preencher_matriz(Matriz, Matriz_auxiliar);
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
    carregar_imagem(tela, imagens, imagens_arquivos);

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

        /*  Logica */

        //  Graficos
        graficos();

        //  Delay
        SDL_Delay(DELAY);
    }

    //  Finalizando SDL e SDL IMAGE
    sdl2_fechar_tela(tela);
    sdl2_fechar_janela(janela);
    sdl2_finalizar_SDL2();

    return 0;
}