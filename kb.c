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
#include "/usr/include/X11/keysym.h"
#include "xwc.h"

typedef struct tecla Tecla;
struct tecla{
    int x;
    int y;
    int larg;
    int alt;
};

static Tecla key[26];
static int pressionadas[26];
static int jogando;
void geraTeclas();
void PintaTecla( WINDOW* , int , int );
void kb_scan2( WINDOW *jan );

int main(){
    /*declaracoes de variaveis*/
    WINDOW *w;
    int i;

    /*inicializacoes*/
    w = InitGraph( 800 , 350 , "Keyboard Test" );
    geraTeclas();
    InitKBD( w );
    jogando = 1;

    /*execucao*/
    WFillRect( w , 0,0 , 800,350 , WNamedColor( "gray1" ) );
    WCor( w , WNamedColor("gold") );
    WPrint( w , 200 , 300 , "Pressione uma tecla nao-alfabetica para terminar:" );
    while( jogando ){
	kb_scan2( w );
	for( i=0 ; i<26 ; i++)
	    PintaTecla( w , i , pressionadas[i] );
    }

    /*finalizacao*/
    return 0;
}

void kb_scan2( WINDOW *jan ){
    int i, r;
    unsigned int botao;
    for( i=0 ; leitor( jan , &botao , &r ) && i<8 ; i++ ){ /*se digitaram algo*/
	if( botao >= 0x61 && botao <= 0x7a ){ /*a-z*/
	    botao -= 97;
	    if( r )
		pressionadas[botao] = 1;
	    else
		pressionadas[botao] = 0;
	}
	else
	    jogando = 0;
    }
}

void PintaTecla( WINDOW *janela , int indice , int acesa ){
    int x0 , y0 , w , h;
    Color estado;
    x0 = key[indice].x;
    y0 = key[indice].y;
    w = key[indice].larg;
    h = key[indice].alt;
    if( acesa )
	estado = 0x0000FF;  /*acesa = azul*/
    else
	estado = 0xFF0000;  /*apagada = vermelho*/
    WFillRect( janela , x0,y0 , w,h , estado );
}

void geraTeclas(){
    int i;
    for( i=0 ; i<26 ; i++){
	key[i].larg = 45;
	key[i].alt = 45;
    }
    key[0].x = 112;  /*a*/
    key[0].y = 150;
    key[1].x = 337;  /*b*/
    key[1].y = 200;
    key[2].x = 237;  /*c*/
    key[2].y = 200;
    key[3].x = 212;  /*d*/
    key[3].y = 150;
    key[4].x = 200;  /*e*/
    key[4].y = 100;
    key[5].x = 262;  /*f*/
    key[5].y = 150;
    key[6].x = 312;  /*g*/
    key[6].y = 150;
    key[7].x = 362;  /*h*/
    key[7].y = 150;
    key[8].x = 450;  /*i*/
    key[8].y = 100;
    key[9].x = 412;  /*j*/
    key[9].y = 150;
    key[10].x = 462; /*k*/
    key[10].y = 150;
    key[11].x = 512; /*l*/
    key[11].y = 150;
    key[12].x = 437; /*m*/
    key[12].y = 200;
    key[13].x = 387; /*n*/
    key[13].y = 200;
    key[14].x = 500; /*o*/
    key[14].y = 100;
    key[15].x = 550; /*p*/
    key[15].y = 100;
    key[16].x = 100; /*q*/
    key[16].y = 100;
    key[17].x = 250; /*r*/
    key[17].y = 100;
    key[18].x = 162; /*s*/
    key[18].y = 150;
    key[19].x = 300; /*t*/
    key[19].y = 100;
    key[20].x = 400; /*u*/
    key[20].y = 100;
    key[21].x = 287; /*v*/
    key[21].y = 200;
    key[22].x = 150; /*w*/
    key[22].y = 100;
    key[23].x = 187; /*x*/
    key[23].y = 200;
    key[24].x = 350; /*y*/
    key[24].y = 100;
    key[25].x = 137; /*z*/
    key[25].y = 200;
    for( i=0 ; i<26 ; i++)
	key[i].x +=100;
    for( i=0 ; i<26 ; i++)
	pressionadas[i] = 0;
}
