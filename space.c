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
space.c:
Implementacao do modulo space, que faz os principais calculos do
jogo SpaceWar, como calcular aceleracoes, verificar se houve
colisoes, entre outros.
Esse modulo tambem armazena os valores da principais variaveis
do jogo atraves da estrutura constants p0.
*/

constants p0;

static void init_border_check();
static void explode( Cel *vitima );

/*
init_modulo_space():
Cria a lista que armazena as informacoes das
naves e projeteis; inicializa as principais
variaveis do modulo.
*/
void init_modulo_space(){
    double Aspect_Ratio;
    init_lista();
    /*	Planet		*/
    p0.delta_t = 0.001;
    p0.planet_radius = 5.0e+6;
    p0.planet_mass = 6.0e+30;
    /* Calculos de escala */
    t0.SCR_larg = 1365;
    t0.SCR_alt = 700;
    Aspect_Ratio = (double)t0.SCR_alt/(double)t0.SCR_larg;
    p0.L = 6*p0.planet_radius;
    p0.H = p0.L*Aspect_Ratio;
    p0.jogando = 1;
    p0.menu = 1;
    /*	Spacecraft 1	*/
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
    /*	Spacecraft 2	*/
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
    /*	Projectiles	*/
    p0.n_proj = 0;
    init_border_check();
}

/*
reset_modulo_space():
Carrega novamente os valores iniciais das variaveis
e da lista, a fim de reiniciar a partida.
*/
void reset_modulo_space(){
    lista_Destroy();
    init_lista();
    /*	Spacecraft 1	*/
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
    /*	Spacecraft 2	*/
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
    /*	Projectiles	*/
    p0.n_proj = 0;
    init_border_check();
}

/*
corpo_copy():
recebe por valor um corpo a e por endereço o corpo b;
copia no corpo b os valores do corpo a
*/
void corpo_copy( Cel *origem , Cel *destino ){
    destino->mass = origem->mass;
    destino->size = origem->size;
    destino->alive = origem->alive;
    destino->pos_x = origem->pos_x;
    destino->pos_y = origem->pos_y;
    destino->vel_x = origem->vel_x;
    destino->vel_y = origem->vel_y;
}


/*
next_pos():
realiza os cálculos das próximas posições e velocidades dos n corpos;
primeiro é calculada a aceleração de todos os corpos devido à força
gravitacional dos demais e do planeta;
em seguida, é atualizada a posição e velocidade de cada corpo;
ao calcular as acelerações, se a distância entre dois corpos ou entre
um corpo e o planeta é menor que o respectivo tamanho (do corpo ou
do planeta), inicia-se o processo de "explosao" do corpo.
O processo de explosao inicia reduzindo a velocidade do corpo;
nas proximas iteracoes, aceleracoes nao sao mais calculadas.
*/
void next_pos(){
    double r;
    Cel *ptr, *aux;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){/*zera a_x e a_y*/
	ptr->a_x = 0.0;
	ptr->a_y = 0.0;
    }
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){/*calcula aceleracoes*/
	if( ptr->alive == 100 ){/*se alive!=100, pula essa iteracao*/
	    r = pow( ptr->pos_x , 2 ) + pow( ptr->pos_y , 2 );
	    r = sqrt( r );
	    if( r <= p0.planet_radius + ptr->size ){
		ptr->vel_x *= 0.2;
		ptr->vel_y *= 0.2;
		ptr->alive -= 1;
		continue;
	    }
	    r = pow( r , 3);
	    ptr->a_x -= (p0.planet_mass) * ptr->pos_x  / r;
	    ptr->a_y -= (p0.planet_mass) * ptr->pos_y  / r;
	    for( aux=ptr->ant ; aux ; aux=aux->ant ){
		r = pow(aux->pos_x-ptr->pos_x,2)+pow(aux->pos_y-ptr->pos_y , 2);
		r = sqrt( r );
		if( r <= ptr->size + aux->size ){
		    ptr->vel_x *= 0.5;
		    ptr->vel_y *= 0.5;
		    aux->vel_x *= 0.5;
		    aux->vel_y *= 0.5;
		    ptr->alive -= 1;
		    aux->alive -= 1;
		    break;
		}
		r = pow( r , 3 );
		ptr->a_x += (aux->mass) * ((aux->pos_x) - (ptr->pos_x)) / r;
		ptr->a_y += (aux->mass) * ((aux->pos_y) - (ptr->pos_y)) / r;
		aux->a_x += (ptr->mass) * ((ptr->pos_x) - (aux->pos_x)) / r;
		aux->a_y += (ptr->mass) * ((ptr->pos_y) - (aux->pos_y)) / r;
	    }
	    ptr->a_x *= G;
	    ptr->a_y *= G;
	}/* end if( ptr->alive == 100 ) */
	else
	    ptr->alive -= 1;
    }/* fim de calcula aceleracoes gravitacionais */

    ptr = jog1;
    if( ptr && ptr->alive == 100 && ptr->acelera ){
	ptr->a_x += 1.0e+9*cos( ptr->angulo );
	ptr->a_y += 1.0e+9*sin( ptr->angulo );
	ptr->acelera = 0;
    }
    ptr = jog2;
    if( ptr && ptr->alive == 100 && ptr->acelera ){
	ptr->a_x += 1.0e+9*cos( ptr->angulo );
	ptr->a_y += 1.0e+9*sin( ptr->angulo );
	ptr->acelera = 0;
    } /*fim de calcula aceleracoes*/

    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){	/*atualiza pos, vel*/
	if( ptr->alive ){/*se alive==0, explode*/
	    ptr->pos_x += (ptr->vel_x)*(p0.delta_t) + ptr->a_x*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_x*/
	    ptr->pos_y += (ptr->vel_y)*(p0.delta_t) + ptr->a_y*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_y*/
	    ptr->vel_x += ptr->a_x*(p0.delta_t);
	    ptr->vel_y += ptr->a_y*(p0.delta_t);
	}
	else
	    explode( ptr );
    }
}

/*
debug_print_constants():
função para depuração; imprime
os valores armazenados na constants p0
*/
void debug_print_constants(){
    printf("%f %f %d\n", p0.planet_mass, p0.planet_radius, p0.n_proj);
}

/*
debug_print_bodies():
função para depuração; imprime
valores armazenados no vetor de corpos bodies
*/
void debug_print_bodies(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant )
	printf("%e %e %e %e %e\n", ptr->mass, ptr->pos_x, ptr->pos_y, ptr->vel_x, ptr->vel_y);
}

/*
debug_print_positions():
funcao para depuracao;
imprime a coordenada x e y da posição de cada um
dos corpos do vetor head
*/
void debug_print_positions(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant )
	printf("%.2e %.2e  ", ptr->pos_x, ptr->pos_y);
    printf("\n");
}

/*
border_control():
Verifica se há algum corpo fora da tela;
caso positivo, coloca o corpo de volta na borda oposta,
a fim de se obter um espaço "toroidal"
*/
void border_control(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){
	if( ptr->pos_x > p0.L )  /*passou da borda da direita?*/
	    ptr->pos_x = -p0.L;
	if( ptr->pos_x < -p0.L ) /*passou da borda da esquerda?*/
	    ptr->pos_x = p0.L;
	if( ptr->pos_y > p0.H )  /*passou da borda de cima?*/
	    ptr->pos_y = -p0.H;
	if( ptr->pos_y < -p0.H ) /*passou da borda de baixo?*/
	    ptr->pos_y = p0.H;
    }
}

/*
init_border_check():
Verifica se há algum corpo fora da tela;
caso positivo, coloca o corpo de volta, na borda do mesmo lado,
e verifica se o corpo está "virado" pra fora; se estiver
virado pra fora, é virado pra dentro;
*/
static void init_border_check(){
    Cel *ptr;
    for( ptr=fim->ant ; ptr ; ptr=ptr->ant ){
	if( ptr->pos_x > p0.L ){ /*passou da borda da direita?*/
	    ptr->pos_x = p0.L;
	    if( ptr->vel_x > 0 ) /*está virado pra fora?*/
		ptr->vel_x *= -1;
	}
	if( ptr->pos_x < -p0.L ){ /*passou da borda da esquerda?*/
	    ptr->pos_x = -p0.L;
	    if( ptr->vel_x < 0 )/*está virado pra fora?*/
		ptr->vel_x *= -1;
	}
	if( ptr->pos_y > p0.H ){ /*passou da borda de cima?*/
	    ptr->pos_y = p0.H;
	    if( ptr->vel_y > 0 )/*está virado pra fora?*/
		ptr->vel_y *= -1;
	}
	if( ptr->pos_y < -p0.H ){ /*passou da borda de baixo?*/
	    ptr->pos_y = -p0.H;
	    if( ptr->vel_y < 0 )/*está virado pra fora?*/
		ptr->vel_y *= -1;
	}
    }
}

/*
termina_modulo_space():
libera toda a memoria da lista ligada.
*/
void termina_modulo_space(){
    lista_Destroy();
}

/*
disparo():
Recebe um apontador para celula origem.
Insere uma nova celula na lista, que 
corresponde a um projetil disparado
do corpo origem.
*/
void disparo( Cel *origem ){
    Cel *new;
    new = lista_insere();
    new->mass = 2.0e+3;
    new->size = 3.0e+5;
    new->alive = 100;
    new->pos_x = origem->pos_x;
    new->pos_x += (origem->size)*2.0*cos(origem->angulo);
    new->pos_y = origem->pos_y;
    new->pos_y += (origem->size)*2.0*sin(origem->angulo);
    new->vel_x = origem->vel_x;
    new->vel_y = origem->vel_y;
    new->angulo = origem->angulo;
    new->vel_x += 3.0e+7*cos( new->angulo );
    new->vel_y += 3.0e+7*sin( new->angulo );
    new->acelera = 0;
    p0.n_proj++;
}

/*
explode():
Recebe um apontador para celula vitima.
Remove a celula da lista ligada.
*/
static void explode( Cel *vitima ){
    if( vitima == jog1 )
	jog1 = NULL;
    else if( vitima == jog2 )
	jog2 = NULL;
    else
	p0.n_proj--;
    lista_remove( vitima );
}
