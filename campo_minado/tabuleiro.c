#include <stdlib.h>
#include "tabuleiro.h"

#define MATRIZ_LINHA 10
#define MATRIZ_COLUNA 10

struct Tabuleiro {
    int matriz[MATRIZ_LINHA][MATRIZ_COLUNA];
    int matriz_auxiliar[MATRIZ_LINHA][MATRIZ_COLUNA];
};

int criar_tabuleiro(Tabuleiro **tabuleiro) {
    *tabuleiro = malloc(sizeof **tabuleiro);

    if (*tabuleiro == NULL) return -1;

    return 0;
}

void liberar_tabuleiro(Tabuleiro **tabuleiro) {
    free(*tabuleiro);
}

int preencher_tabuleiro(Tabuleiro **tabuleiro) {
    int bombas = 0;

    if (*tabuleiro == NULL) return -1;

    for (int linha = 0; linha < MATRIZ_LINHA; linha++) {

        for (int coluna = 0; coluna < MATRIZ_COLUNA; coluna++) {

            if((linha == 0 || linha == 9) || (coluna == 0 || coluna == 9)) {

                (*tabuleiro)->matriz[linha][coluna] = TABULEIRO_BORDA;
                (*tabuleiro)->matriz_auxiliar[linha][coluna] = TABULEIRO_BORDA;

            } else {

                (*tabuleiro)->matriz_auxiliar[linha][coluna] = TABULEIRO_LOCAL_VAZIO;

                if((rand() % 10) < 3) {
                    (*tabuleiro)->matriz[linha][coluna] = TABULEIRO_BOMBA;
                    bombas++;
                } else {
                    (*tabuleiro)->matriz[linha][coluna] = TABULEIRO_SEM_BOMBA;
                }

            }

        }

    }

    return bombas;
}