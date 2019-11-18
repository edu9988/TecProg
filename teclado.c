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
#include "/usr/include/X11/keysym.h"


extern WINDOW *w;
extern constants p0;


extern Corpo *player01, *player02;

void interacao_teclado()
{
    unsigned int valor;

    if( WCheckKBD(w))
    {
        valor = WGetKey(w);
        valor = WLastKeySym();

        if( valor == 0xFF51 ) /*seta esquerda*/
        {
            player02->angulo += 1.0e-1;
        }
        else
        if( valor == 0xFF53 ) /*seta direita*/
        {
            player02->angulo -= 1.0e-1;
        }
        else
        if( valor == 0xFF54 ) /* Liga os motores */
        {
            player02->acelera = 1;
        }
        else
        if( valor == 0x71 ) /*letra q*/
        {
            exit(0);
        }
        else
        if(valor == 0x61)
        {
            player01->angulo += 1.0e-1;
        }
        else
        if(valor == 0x64)
        {
            player01->angulo -= 1.0e-1;
        }
        else
        if( valor == 0x0073 )
        {
            player01->acelera = 1;
        }
        else
        if(valor == 0xff52)
        {
            atirarProjetil(player02);
            player02->numProjeteis--;
        }
        else
        if(valor == 0x77)
        {
            atirarProjetil(player01);
            player01->numProjeteis--;
        }
    }

    if (player01->angulo > 6.2832)
        player01->angulo -= 6.2832;
    if (player01->angulo < -6.2832)
        player01->angulo += 6.2832;

    if (player02->angulo > 6.2832)
        player02->angulo -= 6.2832;
    if (player02->angulo < -6.2832)
        player02->angulo += 6.2832;

}
