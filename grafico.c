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
#include "lista.h"

#define PI_meios 1.57079632679490
#define f180_PI 57.2957795130823
#define PI 3.14159265358979

static int Tx(double);
static int Ty(double);
static int sprX_nave( double );
static int sprX_mis( double );
/*static void set_angle( Cel* );*/

WINDOW *w;
tela t0;
static PIC P1, P2, Ms, Aux, fundo1, fundo2, planeta;
static Color player1, misseis;
static int indice;
MASK masc1, masc2, masc_mis, masc_planet, aux1, aux2, aux_mis;
static int Be(double p);
static void GeraFundo();
/*static char palavra[30];*/


int vitoriasJog1 = 0, vitoriasJog2 = 0;

/*
init_modulo_grafico():
Aloca as estruturas e inicializa as variaveis necessárias 
*/
void init_modulo_grafico(){
    indice = 0;
    w = InitGraph( t0.SCR_larg, t0.SCR_alt, "SpaceWar");
    WFillRect( w , 0,0 , t0.SCR_larg,t0.SCR_alt , 0x000010 );
    Aux = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    masc1 = NewMask( w , 50,50 );
    aux1 = NewMask( w , 1200,50 );
    masc2 = NewMask( w , 50,50 );
    aux2 = NewMask( w , 1200,50 );
    masc_mis = NewMask( w , 26 , 26 );
    aux_mis = NewMask( w , 624,50 );
    masc_planet = NewMask( w , t0.SCR_larg , t0.SCR_alt );
    fundo1 = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    fundo2 = NewPic( w , t0.SCR_larg,t0.SCR_alt );
    planeta = ReadPic( w , "planeta1.xpm" , masc_planet );
    GeraFundo();
    P1 = ReadPic( w, "spaceshuttle_bw2.xpm", aux1 );
    P2 = ReadPic( w, "spaceshuttle_bw3.xpm", aux2 );
    Ms = ReadPic( w, "missiles02.xpm" , aux_mis );
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
void graficos_iteracao()
{
    int i;
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){	/*conversao de valores*/
	ptr->SCR_pos_x = Tx( ptr->pos_x );
	ptr->SCR_pos_y = Ty( ptr->pos_y );
    }

    /*WFillArc( Aux , t0.planeta_x,t0.planeta_y  , 0,23040 , t0.planeta_w,t0.planeta_h , 0x5050FF );*/



    SetMask( Aux , masc_planet );
    PutPic( Aux , planeta ,0,0 , t0.planeta_w,t0.planeta_h , t0.planeta_x,t0.planeta_y );


    if( jog2 != NULL){
	if( jog2->alive == 100 ){
	    PutPic( masc2 , aux2 , sprX_nave( jog2->angulo ),0 , 50,50, 0,0 );
	    SetMask( Aux , masc2 );
	    PutPic( Aux , P2 , sprX_nave( jog2->angulo ),0 , 50,50, jog2->SCR_pos_x-25,jog2->SCR_pos_y-25);
	    UnSetMask( Aux );
	}
	else
	    WFillArc( Aux , jog2->SCR_pos_x-20,jog2->SCR_pos_y-20  , 0,23040 , 40,40 , 0xFF0000-jog2->alive*0x008080 );
    }


    if( jog1 != NULL){
	if( jog1->alive == 100 ){
	    PutPic( masc1 , aux1 , sprX_nave( jog1->angulo ) ,0 , 50,50, 0,0 );
	    SetMask( Aux , masc1 );
	    PutPic( Aux , P1 , sprX_nave( jog1->angulo ) ,0 , 50,50, jog1->SCR_pos_x-25,jog1->SCR_pos_y-25);
	    UnSetMask( Aux );
	}
	else
	    WFillArc( Aux , jog1->SCR_pos_x-20,jog1->SCR_pos_y-20  , 0,23040 , 40,40 , 0xFF0000-jog1->alive*0x008080 );
    }



    for( i=0 , ptr=fim->ant ; i<p0.n_proj ; i++ , ptr=ptr->ant ){
	if( ptr->alive == 100 ){
	    PutPic( masc_mis , aux_mis ,sprX_mis( ptr->angulo),0 , 26,26, 0,0 );
	    SetMask( Aux , masc_mis );
	    PutPic( Aux , Ms ,sprX_mis( ptr->angulo),0 , 26,26, ptr->SCR_pos_x-13,ptr->SCR_pos_y-13);
	}
	else{
	    UnSetMask( Aux );
	    WFillArc( Aux , ptr->SCR_pos_x-10,ptr->SCR_pos_y-10  , 0,23040 , 20,20 , 0xFF0000-ptr->alive*0x008080 );
	}
    }
    UnSetMask( Aux );


    /*WCor( Aux , 0xFF0000 ); (parece desnecessario a partir de agora)
    sprintf(palavra, "%d", indice);
    WPrint( Aux , 20 , 180 , palavra );*/

    PutPic( w , Aux ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    WFillRect( masc1 , 0,0 , 50,50 , WNamedColor( "None" ) );
    WFillRect( masc2 , 0,0 , 50,50 , WNamedColor( "None" ) );


    /* Refaz fundo */
    if( indice%2 )
	PutPic( Aux , fundo1 ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    else
	PutPic( Aux , fundo2 ,0,0 , t0.SCR_larg,t0.SCR_alt , 0,0 );
    indice++;
}

/*static void set_angle( Cel *ptr ){
    if( ptr->vel_x > 0 )
	ptr->angulo = atan( ptr->vel_y / ptr->vel_x );
    else if( ptr->vel_x == 0){
	if( ptr->vel_y >= 0 )
	    ptr->angulo = PI_meios;
	else
	    ptr->angulo = -PI_meios;
    }
    else
	ptr->angulo = PI+atan( ptr->vel_y / ptr->vel_x );
}*/

static int sprX_nave( double ang ){
    int b;
    if( ang < 0 ){
	ang *= -f180_PI;
	ang -= 7.5;
	b = (int) (ang / 15);
	return 50*b;
    }
    else{
	ang *= f180_PI;
	ang -= 7.5;
	b = (int) (ang / 15);
	return (23-b)*50;
    }
}

static int sprX_mis( double ang ){
    int b;
    if( ang < 0 ){
	ang *= -f180_PI;
	ang -= 7.5;
	b = (int) (ang / 15);
	return 26*b;
    }
    else{
	ang *= f180_PI;
	ang -= 7.5;
	b = (int) (ang / 15);
	return (23-b)*26;
    }
}

/*
GeraFundo():
Preenche as PICs fundo1 e fundo2 com estrelas.
*/
static void GeraFundo(){
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

/*
Be():
Dado um real p, 0 <= p <= 1, retorna 0 ou 1.
A probabilidade de retornar 1 é dada por p.
*/
/*Funcao fornecida por: Yoshiharu Kohayakawa*/
static int Be( double p ){
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
    FreePic( Aux );
    FreePic( fundo1 );
    FreePic( fundo2 );
    FreePic( planeta );
    FreePic( masc1 );
    FreePic( masc2 );
    FreePic( masc_mis );
    FreePic( masc_planet );
    FreePic( aux1 );
    FreePic( aux2 );
    FreePic( aux_mis );
    WDestroy( w );
    CloseGraph();
}

/*
Tx():
Recebe um double pos_x;
Calcula a posicao na tela, Tx, atraves de uma
transformacao de variaveis.
Tx pertence ao intervalo [0,SCR_larg];
*/
static int Tx(double pos_x){
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
static int Ty(double pos_y){
    int transf_y;
    double ty;
    ty = 1 - pos_y/p0.H;
    ty *= t0.SCR_alt/2;
    transf_y = (int) ty;
    return transf_y;
}

void enter_menu(){
    WFillRect( w , 0,0 , t0.SCR_larg,t0.SCR_alt , 0x000010 );
}

void menu_plot(){
    if( p0.jogando == 1 ){
	if( p0.menu == 1 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 400 , "Start" );
	if( p0.menu == 2 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 425 , "Option 1" );
	if( p0.menu == 3 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 450 , "Option 2" );
	if( p0.menu == 4 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 475 , "Quit" );
    }
    else if( p0.jogando == 2 ){
	if( p0.menu == 1 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 400 , "Continue" );
	if( p0.menu == 2 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 425 , "Restart" );
	if( p0.menu == 3 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 450 , "Option 2" );
	if( p0.menu == 4 )
	    WCor( w , WNamedColor( "gold" ) );
	else
	    WCor( w , 0xAFAFAF );
	WPrint( w , 500 , 475 , "Quit" );
    }
}

void statusJogo()
{
    unsigned int botao = 0;
    int opcao = 0;

    if(jog1 == NULL && jog2 == NULL)
    {
        WPrint( w , 500 , 475 , "Empate" );
    }

    if(jog1 != NULL && jog2 == NULL)
    {
        vitoriasJog1++;

        if(!leitor(w, &botao, &opcao))
        {
            PutPic(w, fundo2, 0, 0, p0.L, p0.H, p0.L, p0.H);
            WPrint(w , 500 , 475 , "VITORIA: JOGADOR 1" );

            while(!leitor(w, &botao, &opcao));
        }

        jog1->mass = 2.0e+4;
        jog1->size = 5.0e+5;
        jog1->alive = 100;
        jog1->pos_x = -1.0e+7;
        jog1->pos_y = 0.0;
        jog1->vel_x = 0.0;
        jog1->vel_y = 1.0e+7;
        jog1->angulo = 0.0;
        jog1->acelera = 0;

        jog2 = lista_insere();
        jog2->mass = 2.0e+4;
        jog2->size = 5.0e+5;
        jog2->alive = 100;
        jog2->pos_x = 1.0e+7;
        jog2->pos_y = 1.0e+7;
        jog2->vel_x = 2.0e+6;
        jog2->vel_y = -4.0e+6;
        jog2->angulo = 0.0;
        jog2->acelera = 0;
    }

    if(jog1 == NULL && jog2 != NULL)
    {
        vitoriasJog2++;

        if(!leitor(w, &botao, &opcao))
        {
            PutPic(w, fundo2, 0, 0, p0.L, p0.H, p0.L, p0.H);
            WPrint(w , 500 , 475 , "VITORIA: JOGADOR 2" );

            while(!leitor(w, &botao, &opcao));
        }
        jog1 = lista_insere();
        jog1->mass = 2.0e+4;
        jog1->size = 5.0e+5;
        jog1->alive = 100;
        jog1->pos_x = -1.0e+7;
        jog1->pos_y = 0.0;
        jog1->vel_x = 0.0;
        jog1->vel_y = 1.0e+7;
        jog1->angulo = 0.0;
        jog1->acelera = 0;

        jog2->mass = 2.0e+4;
        jog2->size = 5.0e+5;
        jog2->alive = 100;
        jog2->pos_x = 1.0e+7;
        jog2->pos_y = 1.0e+7;
        jog2->vel_x = 2.0e+6;
        jog2->vel_y = -4.0e+6;
        jog2->angulo = 0.0;
        jog2->acelera = 0;
    }

}