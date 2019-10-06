/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP,
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA.
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: MARCELO NASCIMENTO DOS SANTOS JUNIOR
  NUSP: 11222012

  Comentarios: Os testes para descobrir o comportamento do executavel
  fornecido foram feitos atraves do GIMP. Muitas figuras, apesar de
  estarem em branco, depois do processamento, tinham regioes de borda
  equivalentes ao perimetro da imagem. Cada pixel foi adicionado um a
  um para testar o comportamento da segmentacao, porém o teste mais
  eficaz foi o de utilizar figuras somente de uma cor. Quando o fundo
  da imagem era branco, as bordas eram destacadas nos


  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>  /* fprintf(), printf() */
#include <stdlib.h> /* malloc(), free(),  */
#include <math.h>   /* sqrt() */

#include "imagem.h" /* LIMIAR, Byte, Imagem, CelPixel, CelRegiao ...
                       mallocImagem(), freeImagem(), freeRegioes()
                       copieImagem(), pinteImagem(), segmenteImagem()
                       pinteRegiao(), pinteRegioes(), AVISO(), getPixel()
                     */

#include "cores.h"  /* BACK_GROUND, NUM_CORES, cores[0..NUM_CORES] */


/*-------------------------------------------------------------
  constantes
*/
#define EXIT_FAILURE_MALLOC -1

/*-------------------------------------------------------------
  macros
*/
#define NORMA(x,y) sqrt(x*x + y*y)

/*-------------------------------------------------------------
  Funcoes locais que devem ser escritas
*/

static void
setPixel(Imagem *img, int col, int lin, Byte cor[]);

static Bool
pixelBorda(Imagem *img, int limiar, int col, int lin);

static int
pixelsRegiao(Imagem *img, int limiar, int col, int lin, CelRegiao *regiao);

static void
adicionarPixelRegiao(int col, int lin, CelRegiao *regiao);

int corB = 0;

CelRegiao *teste = NULL;

/*-------------------------------------------------------------
  Funcoes locais que ja estao escritas
*/

static void *
mallocSafe(size_t nbytes);

static double
luminosidadePixel(Imagem *img, int col, int lin);

/*-------------------------------------------------------------
  mallocImagem

  Recebe inteiros WIDTH e HEIGHT e retorna um ponteiro para uma
  estrutura (tipo Imagem) que representa uma imagem com HEIGHT
  linhas e WIDTH colunas (HEIGHT x WIDTH pixels).

  Cada pixel da imagem e do tipo Pixel.

  Esta funcao utiliza a funcao mallocSafe.
*/

Imagem *
mallocImagem(int width, int height)
{
    int i,j;
    Imagem *img = mallocSafe(sizeof(Imagem));

    img->pixel = mallocSafe(height * sizeof(Pixel*));
    for(i=0; i<height; i++)
    {
        img->pixel[i] = mallocSafe(width * sizeof(Pixel));

        for(j=0; j<width; j++)
        {
            img->pixel[i][j].regiao = NULL;
        }
    }

    return img;
}


/*-------------------------------------------------------------
  freeImagem

  Recebe um ponteiro IMG para um estrutura que representa uma
  imagem  e libera a memoria utilizada pela estrutura.

  Esta funcao utiliza a funcao free.
*/

void
freeImagem(Imagem *img)
{
    AVISO(imagem: Vixe! Ainda nao fiz a funcao freeImagem.);
}


/*-------------------------------------------------------------
  freeRegioes

  Recebe um ponteiro INIREGIOES para uma lista de regioes de
  uma imagem e libera a memoria aloca pelas celulas dessa lista.

  Esta função também libera a memoria alocada pelas celulas
  da lista de pixels de cada regiao.
*/

void
freeRegioes(CelRegiao *iniRegioes)
{
    AVISO(imagem: Vixe! Ainda nao fiz a funcao freeRegioes);
}


/*-------------------------------------------------------------
  copieImagem

  Recebe ponteiros DESTINO e ORIGINAL para estruturas que
  representam imagems.

  A funcao copia a imagem ORIGEM sobre a imagem DESTINO.

  A imagem DESTINO já deve ter sido criada antes da chama da
  funcao.  Assim, a memória utilizada por DESTINO ja deve ter
  sido _totalmente_ alocada.

*/

void
copieImagem(Imagem *destino, Imagem *origem) // EDITADO
{
    int i,j;

    destino->height = origem->height;
    destino->width = origem->width;

    for(i=0; i<origem->height; i++)
        for(j=0; j<origem->width; j++)
        {
                destino->pixel[j][i].cor[RED] = origem->pixel[i][j].cor[RED];
                destino->pixel[j][i].cor[GREEN] = origem->pixel[i][j].cor[GREEN];
                destino->pixel[j][i].cor[BLUE] = origem->pixel[i][j].cor[BLUE];
        }
}

/*-------------------------------------------------------------
  getPixel

  Recebe um ponteiro IMG para uma estrutura que representa
  uma imagem e uma posicao [LIN][COL] de um pixel.

  A funcao retorna o pixel da posicao [LIN][COL].

  Esta funcao e usada no modulo graphic para exibir a imagem
  corrente em uma janela.
*/

Pixel
getPixel(Imagem *img, int col, int lin)
{
    Pixel pixelX;

    pixelX.cor[RED] = img->pixel[col][lin].cor[RED];
    pixelX.cor[GREEN] = img->pixel[col][lin].cor[GREEN];
    pixelX.cor[BLUE] = img->pixel[col][lin].cor[BLUE];

    return pixelX;
}

/*-------------------------------------------------------------
  setPixel

  Recebe um ponteiro IMG para uma estrutura que representa
  uma imagem, uma posicao [LIN][COL] de um pixel e uma COR.

  A funcao pinta o pixel da posicao [LIN][COL] da cor COR.

*/

static void
setPixel(Imagem *img, int col, int lin, Byte cor[])
{
    img->pixel[col][lin].cor[RED] = cor[RED];
    img->pixel[col][lin].cor[GREEN] = cor[GREEN];
    img->pixel[col][lin].cor[BLUE] = cor[BLUE];
}

/*-------------------------------------------------------------
  pinteImagem

  Recebe um ponteiro IMG para uma estrutura que representa
  uma imagem e uma COR.

  A funcao pinta todos os pixels da imagem IMG da cor COR.

  Esta funcao deve utilizar a funcao setPixel.
*/

void
pinteImagem(Imagem *img, Byte cor[])
{
    for(int i = 0; i<img->height; i++)
        for(int j = 0; j<img->width; j++)
            setPixel(img, j, i, cor);
}

/*-------------------------------------------------------------
   pinteRegioes

   Recebe um  ponteiro IMG para uma estrutura que representa
   uma imagem, um ponteiro INIREGIOES para uma lista de regioes
   da imagem e uma opcao BORDA que tera o valor TRUE or FALSE.

   Se BORDA == FALSE a funcao pinta os pixels de cada regiao da
       lista INIREGIOES de uma cor "diferente" (uma mesma cor
       para todos os pixels de uma regiao).

   Se BORDA == TRUE a funcao pinta os pixels de cada regiao de
       __borda__ da lista INIREGIOES de uma cor "diferente".
       (uma mesma cor para todos os pixels de uma regiao).

   Para fazer o seu servico a funcao percorre a lista INIREGIOES
   e para cada regiao (dependendo da opcao BORDA) percorre a sua
   lista de pixels pintando-os de uma cor.

   Para pintar as regioes de uma cor "diferente" a funcao utiliza
   'ciclicamente' as cores na tabela cores[0..NUM_CORES-1]
   (cores.h):

           cores[0] eh uma cor
           cores[1] eh outra cor
           cores[2] eh outra cor
           ...
           cores[NUM_CORES-1] eh outra cor.

   A funcao tambem atualiza o campo _cor_ das celulas da lista
   INIREGIOES que representam regioes que foram pintadas.
*/

void
pinteRegioes(Imagem *img, CelRegiao *iniRegioes, Bool borda)
{
    int i,j, aux = 0;

    CelRegiao *p = iniRegioes;
    CelPixel *q = p->iniPixels;
    
    printf("A: %\n", p->nPixels);
    printf("A: %\n", p->nPixels);
}

/*-------------------------------------------------------------
   repinteRegiao

   Recebe um  ponteiro IMG para uma estrutura que representa
   uma imagem, uma posicao [LIN][COL] de um pixel da imagem e
   uma cor COR.

   A funcao repinta todos os pixels da imagem IMG que estao na
   regiao do pixel [LIN][COL] com a cor COR.

   Para isto a funcao percorre a lista dos pixels que estao
   na mesma regiao de [LIN][COL] pintando-os de COR.

   A funcao tambem atualiza o campo _cor_ da celula que
   representa a regiao a que o pixel [LIN][COL] pertence.
*/

void
repinteRegiao(Imagem *img, int col, int lin, Byte cor[])
{
    CelRegiao *p = img->pixel[col][lin].regiao;
    CelPixel *q = p->iniPixels;

    for (int i = 0; i < p->nPixels; ++i) {
        setPixel(img, q->col, q->lin, cor);
        q = q->proxPixel;
    }
}

/*-------------------------------------------------------------
   repinteRegioes

   Recebe um  ponteiro IMG para uma estrutura que representa
   uma imagem, um ponteiro INIREGIOES para uma lista de regioes,
   uma posicao [LIN][COL] de um pixel e uma cor COR.

   A funcao repinta os pixels da imagem IMG de

       cada regiao que tem a mesma cor que a regiao
       do pixel [LIN][COL] com a cor COR.

   Para isto a funcao percorre a lista INIREGIOES e,
   para cada regiao que tem a mesma cor que a _regiao_ do pixel
   [LIN][COL], percorre a sua lista pixels repintando-os
   de COR.

   A funcao tambem atualiza o campo _cor_ das celulas da lista
   INIREGIOES que representam regioes que foram repintadas.
*/

void
repinteRegioes(Imagem *img, CelRegiao *iniRegioes, int col, int lin,
               Byte cor[])
{
    AVISO(imagem: Vixe! Ainda nao fiz a funcao pinteRegioes.);
}




/*-------------------------------------------------------------
   pixelBorda

   Recebe um  ponteiro IMG para uma estrutura que representa
   uma imagem, um posicao [LIN][COL] de um pixel da imagem
   e um valor LIMIAR.

   A funcao retorna TRUE se o pixel [LIN][COL] for de borda
   em relacao ao valor LIMIAR.

   Esta funcao utiliza a funcao luminosidadePixel().
*/

static Bool
pixelBorda(Imagem *img, int limiar, int col, int lin)
{
    double gX, gY, resultado;
    double gx1 = -1, gx2= -1, gx3= -1, gx4= -1, gx5= -1, gx6= -1;
    double gy1= -1, gy2= -1, gy3= -1, gy4= -1, gy5= -1, gy6= -1;

    if(lin <= 0)
    {
        gx1 = 0.0;
        gx4 = 0.0;
        gy4 = 0.0;
        gy5 = 0.0;
        gy6 = 0.0;
    }

    if(lin >= img->height-1)
    {
        gx3 = 0.0;
        gx6 = 0.0;
        gy1 = 0.0;
        gy2 = 0.0;
        gy3 = 0.0;
    }

    if(col <= 0)
    {
        gx4 = 0.0;
        gx5 = 0.0;
        gx6 = 0.0;
        gy1 = 0.0;
        gy4 = 0.0;
    }

    if(col >= img->width-1)
    {
        gx1 = 0.0;
        gx2 = 0.0;
        gx3 = 0.0;
        gy3 = 0.0;
        gy6 = 0.0;
    }


    if(gx1 == -1)
        gx1 = luminosidadePixel(img, lin-1, col+1);
    if(gx2 == -1)
        gx2 = 2*luminosidadePixel(img, lin, col+1);
    if(gx3 == -1)
        gx3 = luminosidadePixel(img, lin+1,col+1);
    if(gx4 == -1)
        gx4 = luminosidadePixel(img, lin-1,col-1);
    if(gx5 == -1)
        gx5 = 2*luminosidadePixel(img, lin, col-1);
    if(gx6 == -1)
        gx6 = luminosidadePixel(img, lin+1, col-1);
    if(gy1 == -1)
        gy1 = luminosidadePixel(img, lin+1, col-1);
    if(gy2 == -1)
        gy2 = 2*luminosidadePixel(img, lin+1, col);
    if(gy3 == -1)
        gy3 = luminosidadePixel(img, lin+1, col+1);
    if(gy4 == -1)
        gy4 = luminosidadePixel(img, lin-1, col-1);
    if(gy5 == -1)
        gy5 = 2*luminosidadePixel(img, lin-1, col);
    if(gy6 == -1)
        gy6 = luminosidadePixel(img, lin-1, col+1);

    gX = gx1 + gx2 + gx3 - gx4 - gx5 - gx6;

    gY = gy1 + gy2 + gy3 - gy4 - gy5 - gy6;

    resultado = sqrt(gX*gX + gY*gY);

    if(resultado > limiar) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/*-------------------------------------------------------------
  segmenteImagem

  Recebe um ponteiro IMG para uma estrutura que representa
  uma imagem e um inteiro LIMIAR.

  A funcao retorna um ponteiro para o inicio de uma lista
  de regioes da imagem (em relacao ao valor LIMIAR).

  Cada pixel da imagem deve pertencem a uma, e so uma,
  regiao. Essas regioes constituem o que se chama de uma
  _segmentacao_ da imagem.

  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
*/


CelRegiao *
segmenteImagem(Imagem *img, int limiar)
{
    int i,j;

    CelRegiao *regiao = NULL;
    CelPixel *cabeca = NULL;

    for(i = 0; i<img->height; i++)
    {
        for (j = 0; j<img->width; ++j)
        {
            if (img->pixel[j][i].regiao == NULL)
            {
                regiao = mallocSafe(sizeof(CelRegiao));
                regiao->borda = pixelBorda(img, limiar, j, i);
                regiao->nPixels = cabeca;
                regiao->nPixels = pixelsRegiao(img, limiar, j, i, regiao);

                i = img->height;
                j = img->width;
            }

        }
    }

    if(regiao != NULL)
    {
        regiao->proxRegiao = segmenteImagem(img, limiar);
        return regiao;
    }

    return NULL;

}

/*-------------------------------------------------------------
  pixelsRegiao

  Recebe

      - um  ponteiro IMG para uma estrutura que representa
        uma imagem
      - uma inteiro LIMIAR
      - uma posicao [LIN][COL] de um pixel,
      - um  ponteiro REGIAO para uma celula que representa
        uma regiao da imagem cuja lista de pixels Regiao->iniPixels
        esta sendo construida (recursivamente pela funcao).

  Visitando pixels a partir de posicao [LIN][COL], a funcao
  insere na lista REGIAO->iniPixels novas celulas correspondentes
  a pixels que ainda nao pertencem a regiao alguma (no jargao
  popular, ainda nao foram visitados pela funcao) e que estao na
  regiao representada por REGIAO.

*/

static int
pixelsRegiao(Imagem *img, int limiar, int col, int lin, CelRegiao *regiao)
{
    int i,j;
    i=lin;
    j=col;
    int contador = 0;

    if(lin >= 0 && lin <= img->height-1 && col >=0 && col <= img->width-1 && img->pixel[j][i].regiao == NULL){
        if(pixelBorda(img, limiar, j, i) == regiao->borda){
            img->pixel[j][i].regiao = regiao;
            adicionarPixelRegiao(j, i, regiao);
            contador++;

            contador += pixelsRegiao(img, limiar, j, i+1, regiao);
            contador += pixelsRegiao(img, limiar, j, i-1, regiao);
            contador += pixelsRegiao(img, limiar, j+1, i, regiao);
            contador += pixelsRegiao(img, limiar, j-1, i, regiao);

            if(regiao->borda == TRUE)
            {
                contador += pixelsRegiao(img, limiar, j+1, i+1, regiao);
                contador += pixelsRegiao(img, limiar, j-1, i+1, regiao);
                contador += pixelsRegiao(img, limiar, j+1, i-1, regiao);
                contador += pixelsRegiao(img, limiar, j+1, i-1, regiao);
            }
        }
    }
    return contador;
}

/*
   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
   IMPLEMENTACAO DAS FUNCOES DADAS

   //////////////////////////////////////////////////////////////////////
*/
/*-------------------------------------------------------------*/

/*-------------------------------------------------------------
   mallocSafe

   O parâmetro de mallocSafe é do tipo size_t.
   Em muitos computadores, size_t é equivalente a unsigned int.
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida
   fora destas notas de aula.
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
*/
static void *
mallocSafe(size_t nbytes)
{
    void *ptr;

    ptr = malloc (nbytes);
    if (ptr == NULL)
    {
        fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
        exit (EXIT_FAILURE_MALLOC);
    }

    return ptr;
}


/*-------------------------------------------------------------
   luminosidadePixel

   Recebe um  ponteiro IMG para uma estrutura que representa
   uma imagem, e a posicao [H][W] de um pixe da imagem
   e retorna a sua luminosidade de acordo com a formula

   luminosidade: (0.21 * r) + (0.72 * g) + (0.07 * b)

   http://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
   http://en.wikipedia.org/wiki/Relative_luminance

   Y = 0.2126 R + 0.7152 G + 0.0722 B

   Nota: a outras formulas para luminosidade por ai...
*/
static double
luminosidadePixel(Imagem *img, int col, int lin)
{
    return  ( 0.21 * img->pixel[lin][col].cor[RED]+0.72 * img->pixel[lin][col].cor[GREEN]+ 0.07 * img->pixel[lin][col].cor[BLUE] );
}

static void
adicionarPixelRegiao(int col, int lin, CelRegiao *regiao)
{
    CelPixel *p = regiao->iniPixels;
    CelPixel *q = mallocSafe(sizeof(CelPixel));
    q->lin = lin;
    q->col = col;

    q->proxPixel = p;
    regiao->iniPixels = q;
}
