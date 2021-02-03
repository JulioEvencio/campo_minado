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
void carregar_imagem(SDL_Renderer *tela, SDL_Texture *imagens[], char *arquivos[]);
void graficos(SDL_Renderer *tela, SDL_Texture **imagens, int **Matriz_auxiliar);
int preencher_matriz(int **Matriz, int **Matriz_auxiliar);
void pintar_matriz(SDL_Renderer *tela, SDL_Texture **imagens, int **Matriz_auxiliar);
void pintar_imagens(SDL_Renderer *tela, SDL_Texture **imagens, int matriz, int x, int y, int comp, int alt);
void verificador_de_bombas(int **Matriz);
void abrir_posicao(int **Matriz, int **Matriz_auxiliar, int x, int y);
void colocar_bandeira(int **Matriz_auxiliar, int x, int y);
void clicar_mouse(SDL_Event *evento, int **Matriz, int **Matriz_auxiliar, int linha_mouse, int coluna_mouse);
void perder_jogo(int **Matriz, int **Matriz_auxiliar, int linha_mouse, int coluna_mouse);

#endif // CABECALHO_H_INCLUDED