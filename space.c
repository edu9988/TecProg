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

extern constants p0;
extern tela t0;

static void string_copy(char *, char *);
static void *mallocSafe(unsigned int);


/*******************************/
static void border_check();
extern Corpo *cabecaBodyList;
extern Corpo *player01;
extern Corpo *player02;

/********************************/

/*init_modulo_space():
lê do arquivo "entry.dat" os dados do programa fase1.c, conforme
        especificado em enunciado, e os armazena nas structs p0 e
body_list
*/
void init_modulo_space()
{
    Corpo *corpoAux = NULL;

    double Aspect_Ratio;
    int i;

    /*	Planet		*/
    p0.planet_radius = 5.0e+6;
    p0.planet_mass = 6.0e+30;
    /* Calculos de escala */
    t0.SCR_larg = 1365;
    t0.SCR_alt = 700;
    Aspect_Ratio = (double)t0.SCR_alt/(double)t0.SCR_larg;
    p0.L = 6*p0.planet_radius;
    p0.H = p0.L*Aspect_Ratio;
    /*	Spacecraft 1	*/
    p0.name1 = mallocSafe( (4)*sizeof(char) );
    string_copy( "Foo" , p0.name1 );
    /*	Spacecraft 2	*/
    p0.name2 = mallocSafe( (4)*sizeof(char) );
    string_copy( "Bar" , p0.name2 );

/*****************************************************************************/
    cabecaBodyList = mallocSafe(sizeof(Corpo));
    cabecaBodyList->tipo = 0;
    cabecaBodyList->prox = NULL;
    player01 = mallocSafe(sizeof(Corpo));
    player02 = mallocSafe(sizeof(Corpo));

    player01->mass = 2.0e+4;
    player01->size = 10.0;
    player01->alive = 1;
    player01->pos_x = -1.0e+7;
    player01->pos_y = 0.0;
    player01->vel_x = 0.0;
    player01->vel_y = 1.0e+7;
    player01->tipo = 1;
    player01->angulo = 0.0;
    player01->acelera = 0;
    player01->prox = NULL;
    player01->numProjeteis = 10;
    player01->tempo = 1000;


    player02->mass = 2.0e+4;
    player02->size = 10.0;
    player02->alive = 1;
    player02->pos_x = 1.0e+7;
    player02->pos_y = 1.0e+7;
    player02->vel_x = 2.0e+6;
    player02->vel_y = -4.0e+6;
    player02->tipo = 1;
    player02->angulo = 0.0;
    player02->acelera = 0;
    player02->prox = NULL;
    player02->numProjeteis = 10;
    player02->tempo = 1000;

    player01->prox = cabecaBodyList->prox;
    cabecaBodyList->prox = player01;

    player02->prox = cabecaBodyList->prox;
    cabecaBodyList->prox = player02;

    for(i=0; i<4; i++)
        addProjeteis((-8+5*i)*(1.0e+7), (-8+4*i)*(1.0e+6), (8-5*i)*(-1.0e+6), (8 + 4*i)*(-1.0e+5));

    corpoAux = cabecaBodyList->prox;

    while(corpoAux != NULL)
    {
        corpoAux->a_x = 0;
        corpoAux->a_y = 0;
        corpoAux->angulo = 0.0;

        corpoAux = corpoAux->prox;
    }

    corpoAux = NULL;

/*****************************************************************************/

    p0.projectiles_lifespan = 0.25;

    border_check();
}

/*
mallocSafe():
recebe um int nbytes;
devolve um ponteiro para um bloco de mémoria alocada
de tamanho nbytes;
se malloc retornar NULL, a função imprime mensagem
de erro e encerra o programa devolvendo valor -1
*/
static void *mallocSafe(unsigned int nbytes){
    void *pointer;
    pointer = malloc(nbytes);
    if( pointer == NULL ){
	fprintf(stderr, "Failed to malloc %u bytes\n", nbytes);
	exit(-1);
    }
    return pointer;
}

/*
string_copy():
recebe dois ponteiros para char, a e b;
copia em b, os valores armazenados em a, e por fim
escreve \0 no final de b
*/
static void string_copy(char *a, char *b){
    int i;
    for( i=0 ; i<strlen(a) ; i++ )
	b[i] = a[i];
    b[i] = '\0';
}

/*
termina_modulo_space():
Libera a memoria alocada pelo modulo atraves de malloc.
*/
void termina_modulo_space(){
    free( p0.name1 );
    p0.name1 = NULL;
    free( p0.name2 );
    p0.name2 = NULL;
    limparLista(cabecaBodyList);
}



/************************************************************/

void addObjLista(Corpo *obj)
{
    if(cabecaBodyList != NULL)
    {
        obj->prox = cabecaBodyList->prox;
        cabecaBodyList->prox = obj;
    }
}

void addProjeteis(double pos_x, double pos_y, double vel_x, double vel_y)
{
    Corpo *projetil = mallocSafe(sizeof(Corpo));

    projetil->tipo = 2;
    projetil->mass = 2.0e+3;
    projetil->a_x = 0;
    projetil->a_y = 0;
    projetil->alive = 1;
    projetil->size = 3.0;
    projetil->vel_x = vel_x;
    projetil->vel_y = vel_y;
    projetil->pos_x = pos_x;
    projetil->pos_y = pos_y;
    projetil->tempo = 2000;

    if(cabecaBodyList != NULL)
    {
        projetil->prox = cabecaBodyList->prox;
        cabecaBodyList->prox = projetil;
    }
    else
        fprintf(stderr, "Erro ao adicionar o projetil!");
}

void mostrarLista()
{
    Corpo *p = cabecaBodyList->prox;
    int i = 0;

    while(p != NULL)
    {
        printf("%d\n", i++);
        p = p->prox;
    }
}

static void border_check()
{
    Corpo *obj = cabecaBodyList->prox;

    while(obj != NULL)
    {
        if( obj->pos_x > p0.L ) /*passou da borda da direita?*/
        {
            obj->pos_x = p0.L;
            if( obj->vel_x > 0 ) /*está virado pra fora?*/
                obj->vel_x *= -1;
        }

        if( obj->pos_x < -p0.L ) /*passou da borda da esquerda?*/
        {
            obj->pos_x = -p0.L;
            if( obj->vel_x < 0 ) /*está virado pra fora?*/
                obj->vel_x *= -1;
        }
        if( obj->pos_y > p0.H ) /*passou da borda de cima?*/
        {
            obj->pos_y = p0.H;
            if( obj->vel_y > 0 )/*está virado pra fora?*/
                obj->vel_y *= -1;
        }
        if( obj->pos_y < -p0.H ) /*passou da borda de baixo?*/
        {
            obj->pos_y = -p0.H;
            if( obj->vel_y < 0 )/*está virado pra fora?*/
                obj->vel_y *= -1;
        }

        obj = obj->prox;
    }

    obj = NULL;

}

void borderControl()
{
    Corpo *obj = cabecaBodyList->prox;

    while (obj != NULL)
    {
        if(obj->pos_x > p0.L )  /*passou da borda da direita?*/
            obj->pos_x = -p0.L;
        if(obj->pos_x < -p0.L ) /*passou da borda da esquerda?*/
            obj->pos_x = p0.L;
        if(obj->pos_y > p0.H )  /*passou da borda de cima?*/
            obj->pos_y = -p0.H;
        if(obj->pos_y < -p0.H ) /*passou da borda de baixo?*/
            obj->pos_y = p0.H;

        obj = obj->prox;
    }
}

void nextPos()
{
    double r;
    int i = 0;

    Corpo *obj = NULL;
    Corpo *aux = NULL;
    obj = cabecaBodyList->prox;


    while (obj != NULL) /*zera a_x e a_y*/
    {
        obj->a_x = 0.0;
        obj->a_y = 0.0;
        obj = obj->prox;
    }

    obj = cabecaBodyList->prox;

    while (obj != NULL ) /*calcula aceleracoes*/
    {
        i= 0;
        if(obj->alive) /*se alive==0, pula essa iteracao*/
        {

            r = pow(obj->pos_x, 2) + pow(obj->pos_y , 2);

            if( r <= pow( p0.planet_radius ,2 ) )
            {
                obj->vel_x = 0.0;
                obj->vel_y = 0.0;
                obj->alive = 0;
                continue;
            }

            r = pow( r , 1.5);
            obj->a_x -= (p0.planet_mass) * obj->pos_x  / r;
            obj->a_y -= (p0.planet_mass) * obj->pos_y  / r;

            aux = cabecaBodyList->prox;

            while (aux != NULL)
            {
                if(aux == obj)
                {
                }
                else
                {
                    r = pow(aux->pos_x - obj->pos_x,2)+pow(aux->pos_y - obj->pos_y , 2);

                    if( r <= pow(obj->size, 2) )
                    {
                        obj->a_x = 0.0;
                        obj->a_y = 0.0;
                        obj->vel_x = 0.0;
                        obj->vel_y = 0.0;
                        obj->alive = 0;
                        break;
                    }

                    r = pow( r , 1.5) ;

                    obj->a_x += (aux->mass) * ((aux->pos_x) - (obj->pos_x)) / r;
                    obj->a_y += (aux->mass) * ((aux->pos_y) - (obj->pos_y)) / r;

                }
                aux = aux->prox;
            }

            obj->a_x *= G;
            obj->a_y *= G;
        }
        obj = obj->prox;
    } /* fim de calcula aceleracoes gravitacionais*/


    if( player01->acelera)
    {
        player01->a_x += 1.0e+9*cos( player01->angulo );
        player01->a_y += 1.0e+9*sin( player01->angulo );
        player01->acelera = 0;
    }

    if( player02->acelera)
    {
        player02->a_x += 1.0e+9*cos( player02->angulo );
        player02->a_y += 1.0e+9*sin( player02->angulo );
        player02->acelera = 0;
    }

    obj = cabecaBodyList->prox;

    while(obj != NULL) /*atualiza pos, vel*/
    {
        if( obj->alive)
        {/*se alive==0, pula essa etapa*/
            obj->pos_x += (obj->vel_x)*(p0.delta_t) + obj->a_x*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_x*/
            obj->pos_y += (obj->vel_y)*(p0.delta_t) + obj->a_y*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_y*/
            obj->vel_x += obj->a_x*(p0.delta_t);
            obj->vel_y += obj->a_y*(p0.delta_t);
        }
        obj = obj->prox;
    }
}

void limparLista(Corpo *obj)
{
    if(obj->prox != NULL)
        limparLista(obj->prox);

    if(obj != NULL)
        free(obj);
}

void atirarProjetil(Corpo *objAtirador)
{
    if(objAtirador->numProjeteis > 0)
        addProjeteis(objAtirador->pos_x * 1.2, objAtirador->pos_y * 1.2, cos(objAtirador->angulo)*(objAtirador->vel_x + 25*(1.0e+6)),
                 cos(objAtirador->angulo)*objAtirador->vel_y + 25*(1.0e+5));
}

void interacaoProjeteis()
{
    Corpo *projetil = cabecaBodyList->prox;
    Corpo *aux = NULL;

    while (projetil != NULL)
    {
        if(projetil->tipo == 2)
        {
            projetil->tempo--;

            if(projetil->tempo <= 0)
            {
                aux = projetil;
            }

        }
        projetil = projetil->prox;

        if(aux != NULL)
            deletaObjeto(aux);

        aux = NULL;
    }


    if(player01->numProjeteis <= 0)
        player01->tempo--;
    if(player02->numProjeteis <= 0)
        player02->tempo--;
    if(player01->tempo <= 0)
    {
        player01->tempo = 1000;
        player01->numProjeteis = 10;
    }
    if(player02->tempo <= 0)
    {
        player02->tempo = 1000;
        player02->numProjeteis = 10;
    }
}

void deletaObjeto(Corpo *obj)
{
    Corpo *p = NULL;

    p = cabecaBodyList;

    while(p->prox != obj)
    {
        p = p->prox;
    }

    p->prox = obj->prox;
    free(obj);
}