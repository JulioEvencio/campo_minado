#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

//  Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "sdl2/sdl2.h"

/*  Constantes */
//  Janela
#define JANELA_NOME "Campo Minado"
#define JANELA_COMPRIMENTO 640
#define JANELA_ALTURA 640
//  Matriz
#define MATRIZ_TAMANHO 10
//  Textura
#define IMAGENS_NUMERO 14
//  Geral
#define DELAY 10

/*  Variaveis */
//  Jogo
bool loop = true;
//  Mouse
int linha_mouse;
int coluna_mouse;
//  Matriz do campo minado
int Matriz[MATRIZ_TAMANHO][MATRIZ_TAMANHO];
int Matriz_auxiliar[MATRIZ_TAMANHO][MATRIZ_TAMANHO];
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

/*  Variaveis SDl */
//  Janela
SDL_Window *janela = NULL;
SDL_Renderer *tela = NULL;
//  Variaveis das imagens
SDL_Texture *imagens[IMAGENS_NUMERO];
//  Evento
SDL_Event evento;

/*  Estruturas */
enum enum_imagens
{
    imagems_zero,
    imagems_um,
    imagems_dois,
    imagems_tres,
    imagems_quatro,
    imagems_cinco,
    imagems_seis,
    imagems_sete,
    imagems_oito,
    imagems_mina,
    imagems_mina_explodida,
    imagems_bandeira,
    imagems_bloco,
    imagems_borda
};

/*  Funcoes */
void carregar_imagem(void);

#endif // CABECALHO_H_INCLUDED