/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 nov 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"
#include "grafico.h"
#include "lista.h"

/*
lista.c
Arquivo com implementacao de lista ligada para struct corpo.
*/

Cel *fim;
Cel *jog1;
Cel *jog2;
Cel *jog1Aux;
Cel *jog2Aux;

static Cel *mallocCel();

void init_lista(){
    fim = mallocCel();
    fim->ant = NULL;
    fim->prox = NULL;
}

Cel *lista_insere(){
    Cel *ptr;
    ptr = mallocCel();
    ptr->ant = fim->ant;
    ptr->prox = fim;
    if( fim->ant )
	fim->ant->prox = ptr;
    fim->ant = ptr;
    return ptr;
}

void lista_remove( Cel *a ){
    a->prox->ant= a->ant;
    if( a->ant)
	    a->ant->prox = a->prox;

    if(a != NULL)
        free( a );
}

void lista_Destroy(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant )
	lista_remove( ptr );
    free( fim );
    fim = NULL;
}

static Cel *mallocCel(){
    Cel *ptr;
    ptr = malloc( sizeof(Cel) );
    if( !ptr ){
	fprintf( stderr , "malloc failed\n" );
	exit(1);
    }
    return ptr;
}
