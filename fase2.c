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

constants p0;
corpo *body_list;
WINDOW *w;

/*
Programa fase2.c
<DESCRIÇÃO>
*/
int main(int argc, char *argv[]){

    /*Declaracoes de variaveis*/
    int i, N_iteracoes;

    /* tratar argumentos */
    if( argc == 1 ){/*sem argumentos, o programa recebe delta_t por scanf*/
	printf("Specify step length\n>>>");
	scanf("%lf", &(p0.delta_t));
    }
    else if( argc == 2 )/*se o programa recebeu um argumento, o valor é convertido para float e armazenado em delta_t*/
	p0.delta_t = atof( argv[1] );
    else{/* se recebe mais de um argumento, o programa termina*/
	printf("Expected fewer arguments\n");
	return 0;
    }

    /*Inicializacoes de variaveis*/
    p0.SCR_larg = 1366;
    p0.SCR_alt = 768;

    read_entry_file( &p0 , &body_list );
    N_iteracoes = (int) p0.total_time/p0.delta_t;
    
    /*Execucao*/
    init_modulo_grafico();
    for( i=0 ; i<N_iteracoes ; i++){
	border_control();
	next_pos(&p0, body_list, (p0.projectiles_quantity)+2);
	graficos_iteracao();
	usleep(500);
	if( WCheckKBD(w) ) /*se digitaram algo */
	    break;
    }
    WCor(w, WNamedColor("gold") );
    while( !WCheckKBD(w) )
	WPrint( w , 20 , 200 , "Pressione uma tecla para terminar:" );
    /*fim Execucao*/

    CloseGraph();
    /*	free's section	*/
    free( p0.name1 );
    p0.name1 = NULL;
    free( p0.name2 );
    p0.name2 = NULL;
    free( body_list );
    body_list = NULL;

    return 0;
}
