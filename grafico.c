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

extern WINDOW *w;
static PIC P1, P2, Ms;
static Color player1, player2, misseis;

void init_modulo_grafico(){
    w = InitGraph( p0.SCR_larg, p0.SCR_alt, "Janelao");
    P1 = NewPic( w , 10 , 10 );
    P2 = NewPic( w , 10 , 10 );
    Ms = NewPic( w , 10 , 10 );
    player1 = WNamedColor("red");
    player2 = WNamedColor("blue");
    misseis = WNamedColor("gold");
    InitKBD(w);
    WFillRect(P1, 0,0 , 5,5 ,player1 );
    WFillRect(P2, 0,0 , 5,5 ,player2 );
    WFillRect(Ms, 0,0 , 5,5 ,misseis );

    WFillRect( w , 0,0 , 1366,768 , 0x000000 );
    return;
}

void graficos_iteracao(){
    int i, n;
    n = p0.projectiles_quantity;
    for( i=0 ; i<n+2 ; i++ ){
	body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
	body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );
    }
    WFillRect( w , 0,0 , 1366,768 , 0x000000 );
    PutPic( w , P1 ,0,0 , 5,5, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
    PutPic( w , P2 ,0,0 , 5,5, body_list[1].SCR_pos_x,body_list[1].SCR_pos_y);
    for( i=0 ; i<n ; i++ )
    	PutPic( w , Ms ,0,0 , 5,5, body_list[i+2].SCR_pos_x,body_list[i+2].SCR_pos_y);
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
