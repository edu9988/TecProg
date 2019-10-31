/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 set 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"
#include "xwc.h"
#include "grafico.h"

extern constants p0;
extern corpo *body_list;

double posX=100, posY=100;

extern WINDOW *w;
static PIC Ms, pFigura2, pFigura1, pAux, pBackup, Ms2;
static Color player1, player2, misseis, teste;
static MASK msk;

void init_modulo_grafico(){
    w = InitGraph( p0.SCR_larg, p0.SCR_alt, "Fase 2");
    pFigura1 = NewPic(w, 88, 100);
    pFigura2 = NewPic(w, 88, 100);
    pAux = NewPic(w, p0.SCR_larg, p0.SCR_alt);
    pBackup = NewPic(w, p0.SCR_larg,p0.SCR_alt);
    msk = NewMask(w,p0.SCR_larg, p0.SCR_alt);

    Ms = NewPic( w , 10 , 10);
    Ms2 = NewPic(w, 10, 10);

    pFigura2 = ReadPic(w, "teste2.xpm", msk);
    pFigura1 = ReadPic(w, "teste1.xpm", msk);


    misseis = WNamedColor("gold");
    teste = WNamedColor("red");

    WFillRect(Ms, 0, 0 , 5,5 , misseis);
    WFillRect(Ms2, 0, 0, 5, 5, teste);

    InitKBD(w);

    WFillRect( w , 0,0 , p0.SCR_larg,p0.SCR_alt , 0x000055 );
    PutPic(pBackup, w, 0, 0, p0.SCR_larg, p0.SCR_alt, 0, 0);

    return;
}

void graficos_iteracao(){

    int i, n;
    double norma;

    n = p0.projectiles_quantity;

    for( i=0 ; i<n+2 ; i++ ){
        body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
        body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );
    }

    norma = sqrt( pow(body_list[0].SCR_pos_x -15 - posX, 2) + pow(body_list[0].SCR_pos_y -15 - posY, 2));

    posX += ((body_list[0].SCR_pos_x - posX)/norma)*0.16;
    posY += ((body_list[0].SCR_pos_y - posY)/norma)*0.16;


    PutPic(pAux, pBackup, 0, 0, p0.SCR_larg, p0.SCR_alt, 0, 0);

    for( i=0 ; i<n ; i++ )
        PutPic(pAux, Ms ,0,0 , 5,5, body_list[i+2].SCR_pos_x,body_list[i+2].SCR_pos_y);

    PutPic(pAux, Ms2, 0, 0, 5, 5, posX + 30*(((body_list[0].SCR_pos_x - posX)/norma)),
            posY + 30*(((body_list[0].SCR_pos_y - posY)/norma)));

    SetMask(pAux, msk);

    PutPic(pAux, pFigura1, 0, 0, 88, 100, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
    PutPic(pAux, pFigura2, 0, 0, 88, 100, posX, posY);

    UnSetMask(pAux);

    PutPic(w, pAux, 0, 0, p0.SCR_larg, p0.SCR_alt, 0, 0);

    return;
}

/*
Tx():
Recebe um double pos_x;
Calcula a posicao na tela, Tx, atraves de uma
transformacao de variaveis.
Tx pertence ao intervalo [0,SCR_larg];
*/
int Tx(double pos_x){
    int transf_x;
    double tx;
    tx = 1 + pos_x/p0.L;
    tx *= p0.SCR_larg/2;
    transf_x = (int) tx;
    return transf_x;
}

/*
Ty():
Recebe um double pos_y;
Calcula a posicao na tela, Ty, atraves de uma
transformacao de variaveis.
Ty pertence ao intervalo [0,SCR_alt];
*/
int Ty(double pos_y){
    int transf_y;
    double ty;
    ty = 1 - pos_y/p0.H;
    ty *= p0.SCR_alt/2;
    transf_y = (int) ty;
    return transf_y;
}