/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		          No. USP:10258726    */
/*							                                  */
/* Projeto - Terceira fase - 10 nov 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		          */
/**************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"
#include "xwc.h"
#include "grafico.h"

#define PI 3.14159265359

extern constants p0;
extern corpo *body_list;

double posX=100, posY=100;
double velX = 0, velY = 0;

extern WINDOW *w;
static PIC Ms, Ms2, pFigura2, pFigura1, pFigura3, pBackup;
static Color misseis, teste;
static MASK msk1, msk2, msk3;

extern int k;

int rotacaoX = 0, rotacaoY = 0;
double angulo = 0;
double constVel = 2;

int aux1;

static int i,j;
char aux[30], aux2[30];

KeySym key;

void init_modulo_grafico(){

    w = InitGraph( p0.SCR_larg, p0.SCR_alt, "Fase 2");
    pFigura1 = NewPic(w, 64, 64);
    pFigura2 = NewPic(w, 70, 70);
    pFigura3= NewPic(w, 70, 70);


    pBackup = NewPic(w, p0.SCR_larg,p0.SCR_alt);

    msk1 = NewMask(w, 64, 64);
    msk2 = NewMask(w, 70, 70);
    msk3 = NewMask(w, 70, 70);

    Ms = NewPic( w , 10 , 10);
    Ms2 = NewPic(w, 10, 10);



    pFigura1 = ReadPic(w, "nave.xpm", msk1);
    /*pFigura2 = ReadPic(w, "seta.xpm", msk2);*/


    /*XWriteBitmapFile(GetDisplay(), "seta.dat", GetDraw(pFigura2), 50, 50, 0, 0);*/

    misseis = WNamedColor("gold");
    teste = WNamedColor("white");

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

    if(WCheckKBD(w)){
        key = WGetKey(w);
/*********************************************************************/

        if(key == 114)
            angulo += PI/8;
        if(key == 113)
            angulo += -PI/8;

        if(angulo < 0)
            angulo = 2*PI + angulo;

        if(angulo >= 2*PI || angulo <= -2*PI)
            angulo = 0;

        PutPic(pFigura2, pFigura3, 0,0,64,64,0,0);

        sprintf(aux2, "%.f", fabs(10*angulo*180/PI));

        pFigura2 = ReadPic(w, strcat(aux2, ".xpm"), msk2);

/****************************************************************************/
    }

    for( i=0 ; i<n+2 ; i++ ){
        body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
        body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );

        if(i>1){
            body_list[i].SCR_pos_x += 20;
            body_list[i].SCR_pos_y += 20;
        }
    }

    norma = sqrt( pow(body_list[0].SCR_pos_x -15 - posX, 2) + pow(body_list[0].SCR_pos_y -15 - posY, 2));

    velX = ((body_list[0].SCR_pos_x - posX)/norma)*0.16;
    posX += velX;
    velY = ((body_list[0].SCR_pos_y - posY)/norma)*0.16;
    posY += velY;

    PutPic(w, pBackup, 0, 0, p0.SCR_larg, p0.SCR_alt, 0, 0);

    for( i=0 ; i<n ; i++ )
        PutPic(w, Ms ,0,0 , 5,5, body_list[i+2].SCR_pos_x,body_list[i+2].SCR_pos_y);
/**************************************************************************************/

    PutPic(w, Ms, 0, 0, 5, 5, posX, posY);


/**************************************************************************************/

    /*WLine(w, posX, posY, body_list[0].SCR_pos_x+20, body_list[0].SCR_pos_y, teste);*/

    SetMask(w, msk1);
    PutPic(w, pFigura1, 0, 0, 64, 64, body_list[0].SCR_pos_x, body_list[0].SCR_pos_y);

    SetMask(w, msk2);
    PutPic(w, pFigura2, 0, 0, 70, 70, posX-30, posY-30);
    UnSetMask(w);

    sprintf(aux, "%d", k);
    WPrint(w, 20, 200, aux);

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