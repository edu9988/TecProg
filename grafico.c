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
extern tela t0;
static PIC P1, P2, Ms;
static Color player1, player2, misseis;
MASK mascara;

void init_modulo_grafico(){
    w = InitGraph( t0.SCR_larg, t0.SCR_alt, "Janelao");
    P1 = NewPic( w , 20 , 20 );
    P2 = NewPic( w , 20 , 20 );
    Ms = NewPic( w , 20 , 20 );
    mascara = NewMask( w , 20 , 20 );
    WArc( mascara , 0,0 , 0,23040 , 12,12 , 1 );
    t0.planeta_w =(int) ( (p0.planet_radius/p0.L) *(double)t0.SCR_larg ) ;
    t0.planeta_h = t0.planeta_w;
    t0.planeta_x = t0.SCR_larg/2 - t0.planeta_w/2;
    t0.planeta_y = t0.SCR_alt/2 - t0.planeta_w/2;
    player1 = WNamedColor("red");
    player2 = WNamedColor("blue");
    misseis = WNamedColor("gold");
    InitKBD(w);
    WArc(P1, 0,0 , 0,23040 , 12,12 ,player1 );
    WArc(P2, 0,0 , 0,23040 , 12,12 ,player2 );
    WArc(Ms, 0,0 , 0,23040 , 12,12 ,misseis );
    SetMask( P1 , mascara );
    SetMask( P2 , mascara );
    SetMask( Ms , mascara );

    WFillRect( w , 0,0 , t0.SCR_larg,t0.SCR_alt , 0x000000 );
    return;
}

void graficos_iteracao(){
    int i, n;
    n = p0.projectiles_quantity;
    for( i=0 ; i<n+2 ; i++ ){
	body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
	body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );
    }
    WFillRect( w , 0,0 , t0.SCR_larg,t0.SCR_alt , 0x000000 );
    WArc( w , t0.planeta_x,t0.planeta_y  , 0,23040 , t0.planeta_w,t0.planeta_h , 0xFF0000 );
    PutPic( w , P1 ,0,0 , 13,13, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
    PutPic( w , P2 ,0,0 , 13,13, body_list[1].SCR_pos_x,body_list[1].SCR_pos_y);
    for( i=0 ; i<n ; i++ )
    	PutPic( w , Ms ,0,0 , 13,13, body_list[i+2].SCR_pos_x-5,body_list[i+2].SCR_pos_y-5);
    return;
}

void termina_modulo_grafico(){
    FreePic( P1 );
    FreePic( P2 );
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
