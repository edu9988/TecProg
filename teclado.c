/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Quarta fase - 07 dez 2019			      */
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

/*
teclado.c:
Modulo do jogo responsavel pela interacao do usuario com o
teclado.
*/

static unsigned int botao, vetor[26];
static int delay1, delay2;

/*
menu_kb():
Faz leituras do teclado atraves do modulo xwc.c,
e realiza as acoes convenientes.
Essa funcao e' especifica para o menu.
*/
void menu_kb(){
    int opcao;
    if( leitor( w , &botao , &opcao) ){ /*se digitaram algo */
        if( botao == 0x00FF0D && opcao ){ /*Enter*/
	    if( p0.jogando == 1 ){
		if( p0.menu == 1 ){
		    delay1 = 0;
		    delay2 = 0;
		    p0.menu = 0;
		    p0.jogando = 2;
		}
		else if( p0.menu == 2 ){
		    p0.menu = 0;
		    p0.jogando = 0;
		}
	    }
	    if( p0.jogando == 2 ){
		if( p0.menu == 1 ){
		    p0.menu = 0;
		}
		else if( p0.menu == 2 ){
		    reset_modulo_space();
		    p0.placar1 = 0;
		    p0.placar2 = 0;
		    delay1 = 0;
		    delay2 = 0;
		    p0.menu = 0;
		}
		else if( p0.menu == 3 ){
		    p0.menu = 0;
		    p0.jogando = 0;
		}
	    }
	}
        if( botao == 0x00FF52 && opcao ){ /*Pra cima*/
	    if( p0.menu > 1 )
		p0.menu--;
	    else{
		if( p0.jogando == 1 )
		    p0.menu = 2;
		else if( p0.jogando == 2)
		    p0.menu = 3;
	    }
	}
        if( botao == 0x00FF54 && opcao ){ /*Pra baixo*/
	    if( ( p0.jogando == 1 && p0.menu == 1 ) || ( p0.jogando == 2 && p0.menu <3 ) )
		p0.menu++;
	    else
		p0.menu = 1;
	}
    }
}

/*
interacao_teclado():
Faz a leitura de teclas chamando o modulo xwc.c, e executa
as acoes pertinentes referentes ao jogo.
Essa funcao e' especifica para a interacao durante as partidas.
*/
void interacao_teclado(){
    int i, opcao;
    for( i=0 ; leitor( w , &botao , &opcao ) && i<32 ; i++ ){ /*se digitaram algo */
        if( botao >= 0x61 && botao <= 0x7a ){ /*a-z*/
	    botao -= 97;
	    vetor[botao] = opcao;
	}
    }
    if( jog2 ){
	if( vetor[0] ){ /* letra a */
	    jog2->angulo += 1.3e-2;
	}
	if( vetor[18] ){ /* letra s */
	    if( delay2 )
		delay2--;
	    else{
		delay2 = 100;
		disparo( jog2 );
	    }
	}
	if( vetor[3] ){ /* letra d */
	    jog2->angulo -= 1.3e-2;
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
	    jog1->angulo += 1.3e-2;
	}
	if( vetor[10] ){ /* letra k */
	    if( delay1 )
		delay1--;
	    else{
		delay1 = 100;
	    disparo( jog1 );
	    }
	}
	if( vetor[11] ){ /* letra l */
	    jog1->angulo -= 1.3e-2;
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
        p0.menu = 1;
	vetor[16] = 0;
    }
}

void vitoria_kb(){
    if( WCheckKBD( w ) ){
	reset_modulo_space();
	p0.jogando = 2;
    }
}
	
