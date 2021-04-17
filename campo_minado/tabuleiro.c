#include <stdlib.h>
#include "tabuleiro.h"

#define MATRIZ_LINHA 10
#define MATRIZ_COLUNA 10

struct Tabuleiro {
    int matriz[MATRIZ_LINHA][MATRIZ_COLUNA];
};

int criar_tabuleiro(Tabuleiro **tabuleiro) {
    *tabuleiro = malloc(sizeof **tabuleiro);

    if (*tabuleiro == NULL) return -1;

    return 0;
}

int liberar_tabuleiro(Tabuleiro **tabuleiro) {
    if (*tabuleiro == NULL) return -1;

    free(*tabuleiro);

    return 0;
}