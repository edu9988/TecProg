/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 set 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space.h"

/*
read_entry_file():
recebe um ponteiro para constants p0, um ponteiro para vetor de
corpos bodies;
lê do arquivo "entry.dat" os dados do programa fase1.c, conforme
especificado em enunciado, e os armazena nas structs definidas
no arquivo interface
*/
void read_entry_file(constants *p0, corpo **bodies){
    char aux_name[30];
    FILE *arq;
    corpo s1, s2;
    arq = fopen("entry.dat", "r");
    if( !arq ){
	printf("Error opening entry file\n");
	exit(EXIT_FAILURE);
    }
    /*	Planet		*/
    fscanf(arq, "%lf", &(p0->planet_radius));
    fscanf(arq, "%lf", &(p0->planet_mass));
    fscanf(arq, "%lf", &(p0->total_time));
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    p0->name1 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0->name1 );
    fscanf(arq, "%lf", &(s1.mass));
    s1.size = 10.0;
    s1.alive = 1;
    fscanf(arq, "%lf", &(s1.pos_x));
    fscanf(arq, "%lf", &(s1.pos_y));
    fscanf(arq, "%lf", &(s1.vel_x));
    fscanf(arq, "%lf", &(s1.vel_y));
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    p0->name2 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0->name2 );
    fscanf(arq, "%lf", &(s2.mass));
    s2.size = 10.0;
    s2.alive = 1;
    fscanf(arq, "%lf", &(s2.pos_x));
    fscanf(arq, "%lf", &(s2.pos_y));
    fscanf(arq, "%lf", &(s2.vel_x));
    fscanf(arq, "%lf", &(s2.vel_y));
    /*	Projectiles	*/
    fscanf(arq, "%d", &(p0->projectiles_quantity));
    *bodies = mallocSafe( ((p0->projectiles_quantity)+2)*sizeof(corpo) );
    corpo_copy(s1,*bodies);
    corpo_copy(s2,(*bodies)+1);
    fscanf(arq, "%lf", &(p0->projectiles_lifespan));
    for( int i=0; i<p0->projectiles_quantity ; i++ ){
	fscanf(arq, "%lf", &((*bodies)[i+2].mass));
	(*bodies)[i+2].size = 3.0;
	(*bodies)[i+2].alive = 1;
	fscanf(arq, "%lf", &((*bodies)[i+2].pos_x));
	fscanf(arq, "%lf", &((*bodies)[i+2].pos_y));
	fscanf(arq, "%lf", &((*bodies)[i+2].vel_x));
	fscanf(arq, "%lf", &((*bodies)[i+2].vel_y));
    }
    fclose(arq);
    return;
}

/*
corpo_copy():
recebe por valor um corpo a e por endereço o corpo b;
armazena no corpo b os valores do corpo a
*/
void corpo_copy(corpo a, corpo *b){
    b->mass = a.mass;
    b->size = a.size;
    b->alive = a.alive;
    b->pos_x = a.pos_x;
    b->pos_y = a.pos_y;
    b->vel_x = a.vel_x;
    b->vel_y = a.vel_y;
    return;
}

/*
mallocSafe():
recebe um int nbytes;
devolve um ponteiro para um bloco de mémoria alocada
de tamanho nbytes;
se malloc retornar NULL, a função imprime mensagem
de erro e encerra o programa devolvendo valor -1
*/
void *mallocSafe(unsigned int nbytes){
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
void string_copy(char *a, char *b){
    int i;
    for( i=0 ; i<strlen(a) ; i++ )
	b[i] = a[i];
    b[i] = '\0';
    return;
}

/*
next_pos():
recebe um ponteiro para constants p0, um ponteiro para corpos bodies
e um inteiro n;
realiza os cálculos das próximas posições e velocidades dos n corpos;
primeiro é calculada a aceleração de todos os corpos devido à força
gravitacional dos demais e do planeta
em seguida, é atualizada a posição e velocidade de cada corpo;
ao calcular as acelerações, se a distância entre dois corpos ou entre
um corpo e o planeta é menor que o respectivo tamanho (do corpo ou
do planeta), as acelerações e velocidades desse corpo são zeradas,
e também o campo alive do corpo recebe valor 0, o que faz com que
suas posições e velocidades não sejam mais calculadas nem atualizadas
*/
void next_pos(constants *p0, corpo *bodies, int n){
    double *a_x = mallocSafe(n*sizeof(double));
    double *a_y = mallocSafe(n*sizeof(double));
    double r;
    for( int i=0 ; i<n ; i++ ){/*inicializa vetores a_x e a_y*/
	a_x[i] = 0.0;
	a_y[i] = 0.0;
    }
    for( int i=0 ; i<n ; i++ ){/*calcula aceleracoes*/
	if( bodies[i].alive ){/*se alive==0, pula essa etapa*/
	    r = pow(bodies[i].pos_x ,2) + pow(bodies[i].pos_y , 2);
	    if( r <= pow( p0->planet_radius ,2 ) ){
		a_x[i] = 0.0;
		a_y[i] = 0.0;
		bodies[i].vel_x = 0.0;
		bodies[i].vel_y = 0.0;
		bodies[i].alive = 0;
		continue;
	    }
	    r = pow( r , 1.5);
	    a_x[i] -= (p0->planet_mass) * bodies[i].pos_x  / r;
	    a_y[i] -= (p0->planet_mass) * bodies[i].pos_y  / r;
	    for( int j=0 ; j<i ; j++ ){
		r = pow(bodies[j].pos_x-bodies[i].pos_x,2)+pow(bodies[j].pos_y-bodies[i].pos_y , 2);
		if( r <= pow( bodies[i].size ,2 ) ){
		    a_x[i] = 0.0;
		    a_y[i] = 0.0;
		    bodies[i].vel_x = 0.0;
		    bodies[i].vel_y = 0.0;
		    bodies[i].alive = 0;
		    break;
		}
		r = pow( r , 1.5) ;
		a_x[i] += (bodies[j].mass) * ((bodies[j].pos_x) - (bodies[i].pos_x)) / r;
		a_y[i] += (bodies[j].mass) * ((bodies[j].pos_y) - (bodies[i].pos_y)) / r;
	    }
	    for( int j=i+1 ; j<n ; j++ ){
		r = pow(bodies[j].pos_x-bodies[i].pos_x,2)+pow(bodies[j].pos_y-bodies[i].pos_y , 2);
		if( r <= pow( bodies[i].size ,2 ) ){
		    a_x[i] = 0.0;
		    a_y[i] = 0.0;
		    bodies[i].vel_x = 0.0;
		    bodies[i].vel_y = 0.0;
		    bodies[i].alive = 0;
		    break;
		}
		r = pow( r , 1.5) ;
		a_x[i] += (bodies[j].mass) * ((bodies[j].pos_x) - (bodies[i].pos_x)) / r;
		a_y[i] += (bodies[j].mass) * ((bodies[j].pos_y) - (bodies[i].pos_y)) / r;
	    }
	    a_x[i] *= G;
	    a_y[i] *= G;
	}
    }
    for( int i=0 ; i<n ; i++ ){	/*atualiza pos, vel*/
	if( bodies[i].alive ){/*se alive==0, pula essa etapa*/
	    bodies[i].pos_x += (bodies[i].vel_x)*(p0->delta_t) + a_x[i]*(p0->delta_t)*(p0->delta_t)/2;
	    bodies[i].pos_y += (bodies[i].vel_y)*(p0->delta_t) + a_y[i]*(p0->delta_t)*(p0->delta_t)/2;
	    bodies[i].vel_x += a_x[i]*(p0->delta_t);
	    bodies[i].vel_y += a_y[i]*(p0->delta_t);
	}
    }
    free(a_x);
    free(a_y);
    a_x = NULL;
    a_y = NULL;
    return;
}

/*
print_constants():
função criada para depuração; imprime
os valores armazenados na constants p0
*/
void print_constants(constants p0){
    printf("%lf %lf %lf %s %s %d %lf\n", p0.planet_mass, p0.planet_radius, p0.total_time, p0.name1, p0.name2, p0.projectiles_quantity, p0.projectiles_lifespan);
    return;
}

/*
print_bodies():
função criada para depuração; imprime
valores armazenados no vetor de corpos bodies
*/
void print_bodies(corpo *bodies, int n){
    for( int i=0 ; i<n ; i++ )
	printf("%lf %lf %lf %lf %lf\n", (bodies[i]).mass, (bodies[i]).pos_x, (bodies[i]).pos_y, (bodies[i]).vel_x, (bodies[i]).vel_y);
    return;
}

/*
print_positions():
recebe um vetor de corpos bodies e um inteiro n;
imprime a coordenada x e y da posição de cada um
dos n primeiros corpos do vetor
*/
void print_positions(corpo *bodies, int n){
    for( int i=0 ; i<n ; i++ )
	printf("%.2le %.2le  ", (bodies[i]).pos_x, (bodies[i]).pos_y);
    printf("\n");
    return;
}
