/*
    Constantes e prototipos de funcoes
    genericas
*/
#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

#define JANELA_NOME "Campo Minado"
#define JANELA_LARGURA 640
#define JANELA_ALTURA 640
#define JANELA_DELAY 30
#define TEXTURA_QUANTIDADE 14

enum Menu {
    SAIR
};

enum Textura {
    NUMERO_ZERO,
    NUMERO_UM,
    NUMERO_DOIS,
    NUMERO_TRES,
    NUMERO_QUATRO,
    NUMERO_CINCO,
    NUMERO_SEIS,
    NUMERO_SETE,
    NUMERO_OITO,
    BOMBA,
    BOMBA_EXPLODIDA,
    BANDEIRA,
    BLOCO,
    BORDA
};

static char *textura_arquivo[TEXTURA_QUANTIDADE] = {
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
    "imagem/borda.png",
};

int carregar_texturas(SDL_Renderer *tela, SDL_Texture *textura[]);
void liberar_texturas(SDL_Texture *textura[]);

#endif