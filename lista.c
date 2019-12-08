/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Quarta fase - 07 dez 2019                        */
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

static Cel *mallocCel();

/*
init_lista():
Aloca a celula cabeca de lista.
*/
void init_lista(){
    fim = mallocCel();
    fim->ant = NULL;
    fim->prox = NULL;
}

/*
lista_insere():
Aloca e insere uma nova celula da lista.
Retorna um ponteiro para a nova celula.
*/
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

/*
lista_remove():
Recebe um ponteiro para celula, a.
Remove a celula apontada por a da lista.
*/
void lista_remove( Cel *a ){
    a->prox->ant= a->ant;
    if( a->ant )
	a->ant->prox = a->prox;
    free( a );
}

/*
lista_Destroy():
Remove todas as celulas da lista, incluindo
a cabeca.
*/
void lista_Destroy(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant )
	lista_remove( ptr );
    free( fim );
    fim = NULL;
    jog1 = NULL;
    jog2 = NULL;
}

/*
mallocCel():
Retorna um apontador para uma nova celula,
alocada por malloc.
Se houver falha no malloc, imprime mensagem
de erro e termina o programa.
*/
static Cel *mallocCel(){
    Cel *ptr;
    ptr = malloc( sizeof(Cel) );
    if( !ptr ){
	fprintf( stderr , "malloc failed\n" );
	exit(1);
    }
    return ptr;
}
