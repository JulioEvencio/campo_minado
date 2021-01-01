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
void carregar_imagem(SDL_Texture *imagens[], char *arquivos[])

#endif // CABECALHO_H_INCLUDED