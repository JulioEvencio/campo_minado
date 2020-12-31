//  Bibliotecas
#include "cabecalho.h"

/*  Funcoes */
//  Funcao que cria texturas das imagens e as colocam em suas devidas variaveis
void carregar_imagem(void)
{
    //  Numero zero
    zero = sdl2_carregar_textura(tela, "imagem/zero.png");

    //  Numero um
    um = sdl2_carregar_textura(tela, "imagem/um.png");

    //  Numero dois
    dois = sdl2_carregar_textura(tela, "imagem/dois.png");

    //  Numero tres
    tres = sdl2_carregar_textura(tela, "imagem/tres.png");

    //  Numero quatro
    quatro = sdl2_carregar_textura(tela, "imagem/quatro.png");

    //  Numero cinco
    cinco = sdl2_carregar_textura(tela, "imagem/cinco.png");

    //  Numero seis
    seis = sdl2_carregar_textura(tela, "imagem/seis.png");

    //  Numero sete
    sete = sdl2_carregar_textura(tela, "imagem/sete.png");

    //  Numero oito
    oito = sdl2_carregar_textura(tela, "imagem/oito.png");

    //  Bomba
    bomba = sdl2_carregar_textura(tela, "imagem/mina.png");

    //  Bomba Explodida
    bomba_explodida = sdl2_carregar_textura(tela, "imagem/mina_vermelha.png");

    //  Bandeira
    bandeira = sdl2_carregar_textura(tela, "imagem/bandeira.png");

    //  Bloco
    bloco = sdl2_carregar_textura(tela, "imagem/bloco.png");

    //  Borda
    borda = sdl2_carregar_textura(tela, "imagem/borda.png");
}