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

/*  Variaveis */
//  Jogo
bool loop = true;
//  Mouse
int linha_mouse;
int coluna_mouse;
//  Matriz do campo minado
int Matriz[MATRIZ_TAMANHO][MATRIZ_TAMANHO];
int Matriz_auxiliar[MATRIZ_TAMANHO][MATRIZ_TAMANHO];

/*  Estruturas */

/*  Funcoes */

#endif // CABECALHO_H_INCLUDED