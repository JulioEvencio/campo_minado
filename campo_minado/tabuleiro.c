#include <stdlib.h>
#include "tabuleiro.h"

#define MATRIZ_LINHA 10
#define MATRIZ_COLUNA 10

struct Tabuleiro {
    int matriz[MATRIZ_LINHA][MATRIZ_COLUNA];
    int matriz_auxiliar[MATRIZ_LINHA][MATRIZ_COLUNA];
};

void verificador_de_bombas(Tabuleiro **tabuleiro);

int criar_tabuleiro(Tabuleiro **tabuleiro) {
    *tabuleiro = malloc(sizeof **tabuleiro);

    if (*tabuleiro == NULL) return -1;

    return 0;
}

void liberar_tabuleiro(Tabuleiro **tabuleiro) {
    free(*tabuleiro);
}

int preencher_tabuleiro(Tabuleiro **tabuleiro) {
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
                } else {
                    (*tabuleiro)->matriz[linha][coluna] = TABULEIRO_SEM_BOMBA;
                }

            }

        }

    }

    verificador_de_bombas(tabuleiro);

    return 0;
}

void verificador_de_bombas(Tabuleiro **tabuleiro) {
    int numero_de_bombas;
    for (int linha = 0; linha < MATRIZ_LINHA; linha++) {

        for (int coluna = 0; coluna < MATRIZ_COLUNA; coluna++) {
            numero_de_bombas = 0;

            //  Divisao 1
            if ((*tabuleiro)->matriz[linha][coluna - 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            if ((*tabuleiro)->matriz[linha][coluna + 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            //  Divisao 2
            if ((*tabuleiro)->matriz[linha - 1][coluna - 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            if ((*tabuleiro)->matriz[linha - 1][coluna] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            if ((*tabuleiro)->matriz[linha - 1][coluna + 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            //  Divisao 3
            if ((*tabuleiro)->matriz[linha + 1][coluna - 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            if ((*tabuleiro)->matriz[linha + 1][coluna] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            if ((*tabuleiro)->matriz[linha + 1][coluna + 1] == TABULEIRO_BOMBA) {
                numero_de_bombas++;
            }

            //  Adicionando numeros de bombas na posicao vazia
            if ((*tabuleiro)->matriz[linha][coluna] == TABULEIRO_SEM_BOMBA) {
                (*tabuleiro)->matriz[linha][coluna] = numero_de_bombas;
            }

        }

    }
}