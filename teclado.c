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
#include "/usr/include/X11/keysym.h"

extern WINDOW *w;
extern constants p0;
extern corpo *body_list;

unsigned int tecla, botao;

void interacao_teclado(){
    if( WCheckKBD(w) ){ /*se digitaram algo */
        tecla = WGetKey(w);
        botao = WLastKeySym();
        if( botao == 0xFF51 )
	    body_list[0].angulo += 1.0;
        else if( botao == 0xFF53 )
	    body_list[0].angulo -= 1.0;
        else if( botao == 0xFF52 )
	    body_list[0].acelera = 1;
        else if( botao == 0x71 )
	    exit(0);
    }
}
