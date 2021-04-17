#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

#define MATRIZ_LINHA 10
#define MATRIZ_COLUNA 10
#define TABULEIRO_BOMBA 9
#define TABULEIRO_SEM_BOMBA 12
#define TABULEIRO_BORDA 13
#define TABULEIRO_BANDEIRA 11

typedef struct Tabuleiro Tabuleiro;

int criar_tabuleiro(Tabuleiro **tabuleiro);
void liberar_tabuleiro(Tabuleiro **tabuleiro);
int preencher_tabuleiro(Tabuleiro **tabuleiro);
int obter_valor(Tabuleiro **tabuleiro, int linha, int coluna);
int abrir_posicao(Tabuleiro **tabuleiro, int linha, int coluna);

#endif