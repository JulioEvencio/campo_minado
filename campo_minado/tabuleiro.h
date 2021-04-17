#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

#define TABULEIRO_BOMBA 9
#define TABULEIRO_SEM_BOMBA 0
#define TABULEIRO_LOCAL_VAZIO 11
#define TABULEIRO_BORDA 10

typedef struct Tabuleiro Tabuleiro;

int criar_tabuleiro(Tabuleiro **tabuleiro);
void liberar_tabuleiro(Tabuleiro **tabuleiro);
int preencher_tabuleiro(Tabuleiro **tabuleiro);

#endif