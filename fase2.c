/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 set 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"
#include "xwc.h"
#include <unistd.h>

/*
Programa fase2.c
<DESCRIÇÃO>
*/
int main(int argc, char *argv[]){

    constants parametros;
    corpo *body_list;
    WINDOW *w;
    Color c;
    char palavra[30];

     if( argc == 1 ){/*sem argumentos, o programa recebe delta_t por scanf*/
	printf("Specify step length\n>>>");
	scanf("%lf", &(parametros.delta_t));
    }
    else if( argc == 2 )/*se o programa recebeu um argumento, o valor é convertido para float e armazenado em delta_t*/
	parametros.delta_t = atof( argv[1] );
    else{/* se recebe mais de um argumento, o programa termina*/
	printf("Expected fewer arguments\n");
	return 0;
    }

    w = InitGraph( 800, 600, "Janelao");
    c = WNamedColor("gold");
    WFillRect(w,20,20, 80, 230, c);
    InitKBD(w);

    read_entry_file( &parametros , &body_list );
    int N = (int) parametros.total_time/parametros.delta_t;
    
    for( int i=0 ; i<N ; i++){
	/*print_positions(body_list, parametros.projectiles_quantity+2);*/
	next_pos(&parametros, body_list, (parametros.projectiles_quantity)+2);
    }

    for(;;){
	int nada = fscanf(stdin, "%s", palavra);
	if( palavra[0] == 'q' && palavra[1] == '\0' )
	    break;
    }

    CloseGraph();
    /*	free's section	*/
    free( parametros.name1 );
    parametros.name1 = NULL;
    free( parametros.name2 );
    parametros.name2 = NULL;
    free( body_list );
    body_list = NULL;

    return 0;
}
