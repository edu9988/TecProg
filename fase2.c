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

/*
Programa fase2.c
<DESCRIÇÃO>
*/
int main(int argc, char *argv[]){

    /*Declaracoes de variaveis*/
    constants params;
    corpo *body_list;
    WINDOW *w;
    PIC P1;
    Color player1;
    int i, N_iteracoes;

    /* tratar argumentos */
    if( argc == 1 ){/*sem argumentos, o programa recebe delta_t por scanf*/
	printf("Specify step length\n>>>");
	scanf("%lf", &(params.delta_t));
    }
    else if( argc == 2 )/*se o programa recebeu um argumento, o valor é convertido para float e armazenado em delta_t*/
	params.delta_t = atof( argv[1] );
    else{/* se recebe mais de um argumento, o programa termina*/
	printf("Expected fewer arguments\n");
	return 0;
    }

    /*Inicializacoes de variaveis*/
    params.SCR_larg = 1366;
    params.SCR_alt = 768;
    w = InitGraph( params.SCR_larg, params.SCR_alt, "Janelao");
    player1 = WNamedColor("gold");
    InitKBD(w);
    P1 = NewPic( w , 10 , 10 );
    WPlot(P1, 0 , 0 , player1 );

    read_entry_file( &params , &body_list );
    N_iteracoes = (int) params.total_time/params.delta_t;
    
    /*Execucao*/
    WPlot( P1 , 0,0 , player1 );
    WFillRect( w , 0,0 , 1366,768 , 0x000000 );
    for( i=0 ; i<N_iteracoes ; i++){
	PutPic( w , P1 ,0,0 , 5,5, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
	WFillRect( P1 , 0,0 , 5,5 , 255*i );
	next_pos(&params, body_list, (params.projectiles_quantity)+2);
	usleep(1000);
	if( WCheckKBD(w) ) /*se digitaram algo */
	    break;
    }
    WCor(w, 0x00FF00);
    while( !WCheckKBD(w) )
	WPrint( w , 20 , 200 , "Pressione uma tecla para terminar:" );
    /*fim Execucao*/

    CloseGraph();
    /*	free's section	*/
    free( params.name1 );
    params.name1 = NULL;
    free( params.name2 );
    params.name2 = NULL;
    free( body_list );
    body_list = NULL;

    return 0;
}
