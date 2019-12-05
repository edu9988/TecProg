/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Quarta fase - 02 dez 2019			      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"
#include "grafico.h"
#include "/usr/include/X11/keysym.h"
#include "teclado.h"
#include "lista.h"

/*
Programa fase4.c
<DESCRIÇÃO>
*/
int main(int argc, char *argv[]){

    /* tratar argumentos */

    /*Execucao*/
    init_modulo_space();
    init_modulo_grafico();

    while( p0.jogando ){
	graficos_iteracao();
	next_pos();
	border_control();
	interacao_teclado();
	usleep(2000);
    }
    /*fim Execucao*/

    termina_modulo_grafico();
    termina_modulo_space();

    return 0;
}
