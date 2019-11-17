/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Terceira fase - 22 nov 2019                      */
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
#include "/usr/include/X11/keysym.h"
#include "teclado.h"

constants p0;
WINDOW *w;

Corpo *cabecaBodyList, *player01 = NULL, *player02 = NULL;

/*
Programa fase3.c
<DESCRIÇÃO>
*/
int main(int argc, char *argv[])
{

    /* tratar argumentos */
    if( argc == 1 ){/*sem argumentos, o programa recebe delta_t por scanf*/
	printf("Specify step length\n>>>");
	scanf("%lf", &(p0.delta_t));
    }
    else if( argc == 2 )/*se o programa recebeu um argumento, o valor é convertido para float e armazenado em delta_t*/
	p0.delta_t = atof( argv[1] );
    else{/*se recebe mais de um argumento, recebe por scanf*/
	printf("Expected fewer arguments\n");
	printf("Specify step length\n>>>");
	scanf("%lf", &(p0.delta_t));
    }

    /*Execucao*/
    init_modulo_space();
    init_modulo_grafico();
    while(1)
    {
        interacaoProjeteis();

        graficos_iteracao();

	    interacao_teclado();

	    nextPos();

	    borderControl();

	    usleep(2000);
    }

    WCor(w, WNamedColor("gold") );

    while( !WCheckKBD(w) )
	    WPrint( w , 20 , 200 , "Pressione uma tecla para terminar:" );
    /*fim Execucao*/

    termina_modulo_grafico();
    termina_modulo_space();

    return 0;
}
