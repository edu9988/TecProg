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
#include "lista.h"

extern WINDOW *w;

unsigned int tecla, botao, vetor[26];

void interacao_teclado(){
    int i;
    for( i=0 ; i<26 ; i++ )
	vetor[i] = 0;
    for( i=0 ; WCheckKBD(w) && i<8 ; i++ ){ /*se digitaram algo */
        tecla = WGetKey(w);
        botao = WLastKeySym();
        if( botao >= 0x61 && botao <= 0x7a ){ /*a-z*/
	    botao -= 97;
	    if( !vetor[botao] )
		vetor[botao] = 1;
	}
    }
    if( vetor[0] ){ /* letra a */
	jog2->angulo += 1.0e-1;
    }
    /*if( vetor[18] ){  letra s */
    if( vetor[3] ){ /* letra d */
	jog2->angulo -= 1.0e-1;
    }
    if( vetor[22] ){ /* letra w */
	jog2->acelera = 1;
    }
    if( vetor[9] ){ /* letra j */
	jog1->angulo += 1.0e-1;
    }
    /*if( vetor[10] ){  letra k */
    if( vetor[11] ){ /* letra l */
	jog1->angulo -= 1.0e-1;
    }
    if( vetor[8] ){ /* letra i */
	jog1->acelera = 1;
    }
    if( vetor[16] ){ /* letra q */
	p0.jogando = 0;
    }
    if( jog1->angulo > 6.2832 )
	jog1->angulo -= 6.2832;
    if( jog1->angulo < -6.2832 )
	jog1->angulo += 6.2832;
    if( jog2->angulo > 6.2832 )
	jog2->angulo -= 6.2832;
    if( jog2->angulo < -6.2832 )
	jog2->angulo += 6.2832;
}
