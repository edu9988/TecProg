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

unsigned int /*tecla,*/ botao, vetor[26];

void menu_kb(){
    int opcao;

    if( leitor( w , &botao, &opcao) ){ /*se digitaram algo */
        if( botao == 0x00FF0D ){ /*Enter*/
	    if( p0.jogando == 1 ){
		if( p0.menu == 1 )
		    p0.menu = 0;
		else if( p0.menu == 2 )
		    p0.menu = 0;
		else if( p0.menu == 3 )
		    p0.menu = 0;
		else if( p0.menu == 4 ){
		    p0.menu = 0;
		    p0.jogando = 0;
		}
	    }
	    if( p0.jogando == 2){
		if( p0.menu == 1 ){
		    p0.menu = 0;
		    p0.jogando = 1;
		}
		else if( p0.menu == 2 )
		    p0.menu = 0;
		else if( p0.menu == 3 )
		    p0.menu = 0;
		else if( p0.menu == 4 ){
		    p0.menu = 0;
		    p0.jogando = 0;
		}
	    }
	}
        if( botao == 0x00FF52 ){ /*Pra cima*/
	    if( p0.menu > 1 )
		p0.menu--;
	    else
		p0.menu = 4;
	}
        if( botao == 0x00FF54 ){ /*Pra baixo*/
	    if( p0.menu < 4 )
		p0.menu++;
	    else
		p0.menu = 1;
	}
    }
}

void interacao_teclado(){
    int i, opcao;

    vetor[18] = 0;
    vetor[22] = 0;

    vetor[10] = 0;
    vetor[8] = 0;
    
    for( i=0 ; leitor( w , &botao, &opcao) && i<8 ; i++ ){ /*se digitaram algo */
        /*tecla = WGetKey(w);
        botao = WLastKeySym();*/
        if( botao >= 0x61 && botao <= 0x7a ){ /*a-z*/
	    botao -= 97;

	    vetor[botao] = opcao;

	}
    }
    if( jog2 ){
	if( vetor[0] ){ /* letra a */
	    jog2->angulo += (1.0e-1)/6;
	}
	if( vetor[18] ){ /* letra s */
	    disparo( jog2 );
	}
	if( vetor[3] ){ /* letra d */
	    jog2->angulo -= (1.0e-1)/6;
	}
	if( vetor[22] ){ /* letra w */
	    jog2->acelera = 1;
	}
	if( jog2->angulo > 6.2832 )
	    jog2->angulo -= 6.2832;
	if( jog2->angulo < -6.2832 )
	    jog2->angulo += 6.2832;
    }
    if( jog1 ){
	if( vetor[9] ){ /* letra j */
	    jog1->angulo += (1.0e-1)/6;
	}
	if( vetor[10] ){ /* letra k */
	    disparo( jog1 );
	}
	if( vetor[11] ){ /* letra l */
	    jog1->angulo -= (1.0e-1)/6;
	}
	if( vetor[8] ){ /* letra i */
	    jog1->acelera = 1;
	}
	if( jog1->angulo > 6.2832 )
	    jog1->angulo -= 6.2832;
	if( jog1->angulo < -6.2832 )
	    jog1->angulo += 6.2832;
    }
    if( vetor[16] ){ /* letra q */
	p0.jogando = 2;
        p0.menu = 1;
    }
}
