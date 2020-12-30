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

/*  Variaveis SDl */
//  Janela
SDL_Window *janela = NULL;
SDL_Renderer *tela = NULL;
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
//  Evento
SDL_Event evento;

/*  Estruturas */

/*  Funcoes */

#endif // CABECALHO_H_INCLUDED