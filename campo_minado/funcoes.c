//  Bibliotecas
#include "sdl2/sdl2.h"
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

//  Funcao responsavel pelos graficos do programa
void graficos(SDL_Renderer *tela)
{
    //  Definindo plano de fundo da janela
    sdl2_limpar_tela(tela, SDL2_BRANCO);

    //  Pintando matriz na tela
    pintar_matriz();

    //  Atualizando tela
    sdl2_atualizar_tela(tela);
}

//  Funcao que preenche a matriz do campo minado para que ela possa ser jogavel
int preencher_matriz(void)
{
    int linha, coluna, bombas = 0;
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            if((linha == 0 || linha == 9) || (coluna == 0 || coluna == 9))
            {
                Matriz[linha][coluna] = -1;
                Matriz_auxiliar[linha][coluna] = -1;
            }
            else
            {
                Matriz_auxiliar[linha][coluna] = -2;
                if((rand() % 10) < 3)
                {
                    Matriz[linha][coluna] = 9;
                    bombas++;
                }
                else
                {
                    Matriz[linha][coluna] = 0;
                }
            }
        }
    }
    return bombas;
}

//  Funcao que pinta a matriz na tela usando imagens
void pintar_matriz(void)
{
    int linha, coluna, quadrado_x, quadrado_y;
    int quadrado_comp = (JANELA_COMPRIMENTO / MATRIZ_TAMANHO), quadrado_alt = (JANELA_ALTURA / MATRIZ_TAMANHO);
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            quadrado_x = coluna * quadrado_comp;
            quadrado_y = linha * quadrado_alt;
            pintar_imagens(Matriz_auxiliar[linha][coluna], quadrado_x, quadrado_y, quadrado_comp, quadrado_alt);
        }
    }
}

//  Funcao auxiliar para pintar o campo minado na tela
void pintar_imagens(int matriz, int x, int y, int comp, int alt)
{
    //  Bandeira
    if(matriz == -3)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_bandeira], x, y, comp, alt);
    }
    //  Parte de dentro invisivel
    if(matriz == -2)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_bloco], x, y, comp, alt);
    }
    //  Borda
    if(matriz == -1)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_borda], x, y, comp, alt);
    }
    //  Bomba Explodida
    if(matriz == -4)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_mina_explodida], x, y, comp, alt);
    }
    //  Bombas
    if(matriz == 9)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_mina], x, y, comp, alt);
    }
    //  Numero 0
    if(matriz == 0)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_zero], x, y, comp, alt);
    }
    //  Numero 1
    if(matriz == 1)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_um], x, y, comp, alt);
    }
    //  Numero dois
    if(matriz == 2)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_dois], x, y, comp, alt);
    }
    //  Numero tres
    if(matriz == 3)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_tres], x, y, comp, alt);
    }
    //  Numero quatro
    if(matriz == 4)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_quatro], x, y, comp, alt);
    }
    //  Numero cinco
    if(matriz == 5)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_cinco], x, y, comp, alt);
    }
    //  Numero seis
    if(matriz == 6)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_seis], x, y, comp, alt);
    }
    //  Numero sete
    if(matriz == 7)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_sete], x, y, comp, alt);
    }
    //  Numero oito
    if(matriz == 8)
    {
        sdl2_desenhar_textura(tela, imagens[imagems_oito], x, y, comp, alt);
    }
}

//  Funcao que verifica quantas bombas ha nos lugares adjacentes aos locais vazios
void verificador_de_bombas(void)
{
    int linha, coluna, numero_de_bombas;
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            numero_de_bombas = 0;
            //  Divisao 1
            if(Matriz[linha][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Divisao 2
            if(Matriz[linha-1][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha-1][coluna] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha-1][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Divisao 3
            if(Matriz[linha+1][coluna-1] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha+1][coluna] == 9)
            {
                numero_de_bombas++;
            }
            if(Matriz[linha+1][coluna+1] == 9)
            {
                numero_de_bombas++;
            }
            //  Adicionando numeros de bombas na posicao vazia
            if(Matriz[linha][coluna] == 0)
            {
                Matriz[linha][coluna] = numero_de_bombas;
            }
        }
    }
}

//  Funcao que mostra o que ha dentro da posicao clicada
void abrir_posicao(int x, int y)
{
    //  Verificando se o local esta marcado com bandeira
    if(Matriz_auxiliar[x][y] != -3)
    {
        Matriz_auxiliar[x][y] = Matriz[x][y];
        //  Verificando se o usuario perdeu
        if(Matriz[x][y] == 9)
        {
            perder_jogo();
        }
    }
}

//  Funcao que coloca ou retira a bandeira
void colocar_bandeira(int x, int y)
{
    //  Verificando se o local e valido
    if(Matriz_auxiliar[x][y] == -2)
    {
        Matriz_auxiliar[x][y] = -3;
    }
    else
    {
        //  Removendo bandeira
        if(Matriz_auxiliar[x][y] == -3)
        {
            Matriz_auxiliar[x][y] = -2;
        }
    }
}

//  Funcao que ativa quando alguem clicar com o mouse
void clicar_mouse(void)
{
    //  Verificando se o botao esquerdo do mouse foi pressionado
    if(evento.button.button == SDL_BUTTON_LEFT)
    {
        abrir_posicao(linha_mouse, coluna_mouse);
    }
    //  Verificando se o botao direito do mouse foi pressionado
    if(evento.button.button == SDL_BUTTON_RIGHT)
    {
        colocar_bandeira(linha_mouse, coluna_mouse);
    }
}

void perder_jogo(void)
{
    int linha, coluna;
    //  Deixando as matrizes iguais para exibir o gabarito do jogo
    for(linha = 0; linha < MATRIZ_TAMANHO; linha++)
    {
        for(coluna = 0; coluna < MATRIZ_TAMANHO; coluna++)
        {
            Matriz[linha_mouse][coluna_mouse] = -4;
            Matriz_auxiliar[linha][coluna] = Matriz[linha][coluna];
        }
    }
}