/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 07 dez 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/

/*
lista.h
Arquivo com interface do modulo lista.c de lista ligada de celulas
struct corpo.
*/

#include "space.h"

extern Cel *fim;
extern Cel *jog1;
extern Cel *jog2;

void init_lista();
Cel *lista_insere();
void lista_remove( Cel* );
void lista_Destroy();
