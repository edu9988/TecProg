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
PIC P1, P2, Ms;
Color player1, player2, misseis;

void init_modulo_grafico(){
    w = InitGraph( p0.SCR_larg, p0.SCR_alt, "Janelao");
    player1 = WNamedColor("red");
    player2 = WNamedColor("blue");
    misseis = WNamedColor("white");
    InitKBD(w);
    P1 = NewPic( w , 10 , 10 );
    P2 = NewPic( w , 10 , 10 );
    Ms = NewPic( w , 10 , 10 );
    WFillRect(P1, 0,0 , 5,5 ,player1 );
    WFillRect(P2, 0,0 , 5,5 ,player2 );

    WPlot( P1 , 0,0 , player1 );
    WPlot( P2 , 0,0 , player1 );
    WFillRect( w , 0,0 , 1366,768 , 0x000000 );
    return;
}

void graficos_iteracao(){
    WFillRect( w , 0,0 , 1366,768 , 0x000000 );
    PutPic( w , P1 ,0,0 , 5,5, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
    PutPic( w , P2 ,0,0 , 5,5, body_list[1].SCR_pos_x,body_list[1].SCR_pos_y);
    PutPic( w , Ms ,0,0 , 5,5, body_list[2].SCR_pos_x,body_list[2].SCR_pos_y);
    PutPic( w , Ms ,0,0 , 5,5, body_list[3].SCR_pos_x,body_list[3].SCR_pos_y);
    PutPic( w , Ms ,0,0 , 5,5, body_list[4].SCR_pos_x,body_list[4].SCR_pos_y);
    PutPic( w , Ms ,0,0 , 5,5, body_list[5].SCR_pos_x,body_list[5].SCR_pos_y);
    return;
}
