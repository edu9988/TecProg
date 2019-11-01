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

/* XPM */
/* figura qualquer para tentar implementar transparencia*/
static char *samp_xpm[] = {
/* nose pixmap
 width height ncolors chars_per_pixel */
"32 32 5 1",
" 	c None",
".	c blue",
"X	c white",
"o	c gold",
"O	c yellow",
/* pixels */
"           ..XXX..              ",
"        ..XXXoXXXXX..           ",
"       .XooOOOooooXXX.          ",
"      XooOOOOOOOooooXXX         ",
"     XoOOOOOOOOOOOoooXXX        ",
"    .ooOOOOOOOOOOOooooXX.       ",
"   .XoOOOOOOOOOOOOOoooXXX.      ",
"  ..ooOOOOOOOOOOOOOooooXX..     ",
"  .XoOOOOOOOOOOOOOOOoooXXX.     ",
"  .XoOOOOOOOOOOOOOOOoooXXX.     ",
" ..XoOOOOOOOOOOOOOOOoooXXX..    ",
" .XoooOOOOOOOOOOOOOoooooXXX.    ",
" .XXooOOOOOOOOOOOOOooooXXXX.    ",
" .XXoooOOOOOOOOOOOoooooXXXX.    ",
" ..XoooOOOOOOOOOOOoooooXXX..    ",
" ..XoooooOOOOOOOoooooooXXX..    ",
" ..XXooooooOOOooooooooXXXX..    ",
"  ..XoooooooooooooooooXXX..     ",
"  ..XXoooooooooooooooXXXX..     ",
"  ...XXoooooooooooooXXXX...     ",
"   ..XXXXoooooooooXXXXXX..      ",
"    ..XXXXXXXoXXXXXXXXX..       ",
"     ...XXXXXXXXXXXXX...        ",
"      ....XXXXXXXXX....         ",
"         .....X.....            ",
"          .........             ",
"           .......              ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                "
};


extern constants p0;
extern corpo *body_list;

extern WINDOW *w;
extern tela t0;
static PIC P1, P2, Ms, Aux, fundo1, fundo2, planeta;
static Color player1, misseis;
static int indice;
MASK masc1, masc2, m_planet;
static int Be(double p);
void GeraFundo();
static char palavra[30];

/*
init_modulo_grafico():
Aloca as estruturas e inicializa as variaveis necessárias 
*/
void init_modulo_grafico(){
    indice = 0;
    w = InitGraph( t0.SCR_larg, t0.SCR_alt, "SpaceWar");
    Aux = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    masc1 = NewMask( w , t0.SCR_larg , t0.SCR_alt );
    masc2 = NewMask( w , t0.SCR_larg , t0.SCR_alt );
    m_planet = NewMask( w , t0.SCR_larg , t0.SCR_alt );
    fundo1 = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    fundo2 = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    planeta = ReadPic( w , "planeta1.xpm" , m_planet );
    GeraFundo();
    P1 = MountPic( w, samp_xpm, masc1 );
    P2 = ReadPic( w, "teste1.xpm" , masc2 );
    Ms = MountPic( w, samp_xpm, masc1 );
    t0.planeta_w =(int) ( (p0.planet_radius/p0.L) *(double)t0.SCR_larg ) ;
    t0.planeta_h = t0.planeta_w;
    t0.planeta_x = t0.SCR_larg/2 - t0.planeta_w/2;
    t0.planeta_y = t0.SCR_alt/2 - t0.planeta_w/2;
    player1 = WNamedColor("red");
    misseis = WNamedColor("gold");
    InitKBD(w);
}

/*
graficos_iteracao():
Desenha na tela todos os corpos em suas respectivas
posicoes.
*/
void graficos_iteracao(){
    int i, n;
    n = p0.projectiles_quantity;
    for( i=0 ; i<n+2 ; i++ ){
	body_list[i].SCR_pos_x = Tx( body_list[i].pos_x );
	body_list[i].SCR_pos_y = Ty( body_list[i].pos_y );
    }

    /*WFillArc( Aux , t0.planeta_x,t0.planeta_y  , 0,23040 , t0.planeta_w,t0.planeta_h , 0x5050FF );*/
    SetMask( Aux , m_planet );
    PutPic( Aux , planeta ,0,0 , t0.planeta_w,t0.planeta_h , t0.planeta_x,t0.planeta_y );
    SetMask( Aux , masc2 );
    PutPic( Aux , P2 ,0,0 , 50,40, body_list[1].SCR_pos_x,body_list[1].SCR_pos_y);
    SetMask( Aux , masc1 );
    PutPic( Aux , P1 ,0,0 , 40,40, body_list[0].SCR_pos_x,body_list[0].SCR_pos_y);
    for( i=0 ; i<n ; i++ )
    	PutPic( Aux , Ms ,0,0 , 40,40, body_list[i+2].SCR_pos_x-5,body_list[i+2].SCR_pos_y-5);
    UnSetMask( Aux );
    WCor( Aux , 0xFF0000 );
    sprintf(palavra, "%d", indice);
    WPrint( Aux , 20 , 180 , palavra );
    PutPic( w , Aux ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    /* Refaz fundo */
    if( indice%2 )
	PutPic( Aux , fundo1 ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    else
	PutPic( Aux , fundo2 ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    indice++;
}

/*
GeraFundo():
Preenche as PICs fundo1 e fundo2 com estrelas.
*/
void GeraFundo(){
    int x,y;
    for( y=0 ; y<t0.SCR_alt ; y++ )
	for( x = 0 ; x<t0.SCR_larg ; x++ )
	    if( Be( 1.0e-4 ) ){
		WFillArc( fundo1 , x,y , 0,23040 , 3,3 , 0x5050FF);
		WPlot( fundo1 , x+1,y+1 , 0x8080FF );
		WFillArc( fundo2 , x,y , 0,23040 , 3,3 ,  0x0000FF);
		WPlot( fundo2 , x+1,y+1 , 0xFF00FF );
	    }
}

/*Be():Dado um real p, 0 <= p <= 1, retorna 0 ou 1.*/
/*A probabilidade de retornar 1 é dada por p.*/
/*Funcao fornecida por: Yoshiharu Kohayakawa*/
static int Be(double p){
    return rand()/(1.0 + RAND_MAX) < p;
}

/*
termina_modulo_grafico():
Libera as estruturas alocadas
*/
void termina_modulo_grafico(){
    FreePic( P1 );
    FreePic( P2 );
    FreePic( Ms );
    WDestroy( w );
}

/*
Tx():
Recebe um double pos_x;
Calcula a posicao na tela, Tx, atraves de uma
transformacao de variaveis.
Tx pertence ao intervalo [0,SCR_larg];
*/
int Tx(double pos_x){
    int transf_x;
    double tx;
    tx = 1 + pos_x/p0.L;
    tx *= t0.SCR_larg/2;
    transf_x = (int) tx;
    return transf_x;
}

/*
Ty():
Recebe um double pos_y;
Calcula a posicao na tela, Ty, atraves de uma
transformacao de variaveis.
Ty pertence ao intervalo [0,SCR_alt];
*/
int Ty(double pos_y){
    int transf_y;
    double ty;
    ty = 1 - pos_y/p0.H;
    ty *= t0.SCR_alt/2;
    transf_y = (int) ty;
    return transf_y;
}
