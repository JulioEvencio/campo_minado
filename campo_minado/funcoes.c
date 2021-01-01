//  Bibliotecas
#include "cabecalho.h"

/*  Funcoes */
//  Funcao que cria texturas das imagens e as colocam em suas devidas variaveis
void carregar_imagem(SDL_Renderer *tela, SDL_Texture *imagens[], char *arquivos[])
{
    for(int incremento = 0; incremento < IMAGENS_NUMERO; incremento++)
    {
        imagens[incremento] = sdl2_carregar_textura(tela, arquivos[incremento]);
    }
}