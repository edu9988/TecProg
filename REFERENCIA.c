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

static char * nose[] = {
/* nose pixmap
 * width height ncolors chars_per_pixel */
        "32 32 4 2 ",
        "   c None",
        ".  c #000 	 s s_#000 ",
        "X  c #FFFFB0B0B0B0 	 s s_#FFFFB0B0B0B0 ",
        "o  c #32329999CCCC 	 s s_#32329999CCCC ",
/* pixels */
        "                                                                ",
        "                                                                ",
        "                    . . . . .                                   ",
        "                  . X X X X X .                                 ",
        "                . X X X X X X X .                               ",
        "                . X X X X X X X X .                             ",
        "                . X X X X X X . . . . . .                       ",
        "                . X X X X X .         .   .                     ",
        "                . X X X X . . o o o o o . .                     ",
        "                . X X X X .       o o o X .                     ",
        "                . X X X X .       o o o X X .                   ",
        "                . X X X X X .       o X X X X .                 ",
        "                . X X X X X X . . . X X X X X X .               ",
        "                . X X X X X X X X X X X X X X X X .             ",
        "                . X X . . X X X X X X X X X X X X X .           ",
        "                . X . X X X X X X X X X X X X X X X .           ",
        "                  . X X X X X X X X X X X X X X X X X .         ",
        "                  . X X X X X X X X X X X X X X X X X .         ",
        "                . X X X X X X X X X X X X X X X X X X .         ",
        "                . X X X X X X X X X X X X X X X X X X .         ",
        "                . X X X X X X X X X X X X X X X X X X .         ",
        "                . X X X X X X X X X X X X X X X X X .           ",
        "                . X X X X X X X X X X X X X X X X X .           ",
        "                  . X X X . . . X X X X X X X X X .             ",
        "                    . . . . X . . . X X X X X . .               ",
        "                        . X X . X X . . . . .                   ",
        "                        . X X . X X .                           ",
        "                        . X X . X X .                           ",
        "                        . X X X . . . . .   . .                 ",
        "                      . X X X . X X X X X . . X . .             ",
        "                    . X X X X X X X X X X X X . X X .           ",
        "                    . . . . . . . . . . . . . . . . .           "
} ;

extern constants p0;
extern corpo *body_list;

extern WINDOW *w;
extern tela t0;
static PIC P1, Ms, pAux;
static Color player1, player2, misseis;
MASK mascara;

void init_modulo_grafico(){
    w = InitGraph(t0.SCR_larg, t0.SCR_alt, "Janelao");
    pAux = NewPic(w, t0.SCR_larg, t0.SCR_alt);
    mascara = NewMask(w, t0.SCR_larg, t0.SCR_alt);

    P1 = MountPic(w, nose, mascara);

    return;
}

void graficos_iteracao(){
    int i, n;
    n = p0.projectiles_quantity;
    for( i=0 ; i<n+2 ; i++ ){
	body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
	body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );
    }

    SetMask(pAux, mascara);

    for(i=0; i<6; i++){
        PutPic(pAux , P1 ,0,0 , 32, 32, body_list[i].SCR_pos_x,body_list[i].SCR_pos_y);
    }


    UnSetMask(pAux);

    PutPic(w, pAux, 0, 0, t0.SCR_larg, t0.SCR_alt, 0, 0);

    WFillRect(pAux , 0,0,  t0.SCR_larg, t0.SCR_larg , 0x000099 );

    return;
}

void termina_modulo_grafico(){
    FreePic( P1 );
    FreePic( Ms );
    WDestroy( w );
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
    tx *= t0.SCR_larg/2;
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
    ty *= t0.SCR_alt/2;
    transf_y = (int) ty;
    return transf_y;
}
