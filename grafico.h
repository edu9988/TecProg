/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Quarta fase - 02 dez 2019			      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/

/*
grafico.h
header file com a interface grafica usada pelo programa fase4.c
*/

#include "xwc.h"

typedef struct{
    int SCR_larg;
    int SCR_alt;
    int planeta_x;
    int planeta_y;
    int planeta_w;
    int planeta_h;
}tela;

extern tela t0;
extern WINDOW *w;

void init_modulo_grafico();
void graficos_iteracao();
void termina_modulo_grafico();
void enter_menu();
void menu_plot();
