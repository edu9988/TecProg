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

extern constants p0;
extern corpo *body_list;

/*
read_entry_file():
lê do arquivo "entry.dat" os dados do programa fase1.c, conforme
especificado em enunciado, e os armazena nas structs p0 e
body_list
*/
void read_entry_file(){
    int i;
    char aux_name[30];
    FILE *arq;
    corpo s1, s2;
    arq = fopen("entry.dat", "r");
    if( !arq ){
	printf("Error opening entry file\n");
	exit(EXIT_FAILURE);
    }
    /*	Planet		*/
    fscanf(arq, "%lf", &p0.planet_radius);
    fscanf(arq, "%lf", &p0.planet_mass);
    fscanf(arq, "%lf", &p0.total_time);
    p0.L = 1.5e7;
    p0.H = 1.5e7;
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    p0.name1 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0.name1 );
    fscanf(arq, "%lf", &(s1.mass));
    s1.size = 10.0;
    s1.alive = 1;
    fscanf(arq, "%lf", &(s1.pos_x));
    fscanf(arq, "%lf", &(s1.pos_y));
    fscanf(arq, "%lf", &(s1.vel_x));
    fscanf(arq, "%lf", &(s1.vel_y));
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    p0.name2 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0.name2 );
    fscanf(arq, "%lf", &(s2.mass));
    s2.size = 10.0;
    s2.alive = 1;
    fscanf(arq, "%lf", &(s2.pos_x));
    fscanf(arq, "%lf", &(s2.pos_y));
    fscanf(arq, "%lf", &(s2.vel_x));
    fscanf(arq, "%lf", &(s2.vel_y));
    /*	Projectiles	*/
    fscanf(arq, "%d", &(p0.projectiles_quantity));
    body_list = mallocSafe( ((p0.projectiles_quantity)+2)*sizeof(corpo) );
    corpo_copy(s1,body_list);
    corpo_copy(s2,body_list+1);
    fscanf(arq, "%lf", &(p0.projectiles_lifespan));
    for( i=0; i<p0.projectiles_quantity ; i++ ){
	fscanf(arq, "%lf", &(body_list[i+2].mass));
	body_list[i+2].size = 3.0;
	body_list[i+2].alive = 1;
	fscanf(arq, "%lf", &(body_list[i+2].pos_x));
	fscanf(arq, "%lf", &(body_list[i+2].pos_y));
	fscanf(arq, "%lf", &(body_list[i+2].vel_x));
	fscanf(arq, "%lf", &(body_list[i+2].vel_y));
    }
    fclose(arq);
    return;
}

/*
corpo_copy():
recebe por valor um corpo a e por endereço o corpo b;
copia no corpo b os valores do corpo a
*/
void corpo_copy(corpo a, corpo *b){
    b->mass = a.mass;
    b->size = a.size;
    b->alive = a.alive;
    b->pos_x = a.pos_x;
    b->pos_y = a.pos_y;
    b->vel_x = a.vel_x;
    b->vel_y = a.vel_y;
/*    b->SCR_pos_x = a.SCR_pos_x;
    b->SCR_pos_y = a.SCR_pos_y;*/
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
void next_pos(){
    double *a_x, *a_y, r;
    int i, j, n;
    n = p0.projectiles_quantity +2;
    a_x = mallocSafe(n*sizeof(double));
    a_y = mallocSafe(n*sizeof(double));
    for( i=0 ; i<n ; i++ ){/*inicializa vetores a_x e a_y*/
	a_x[i] = 0.0;
	a_y[i] = 0.0;
    }
    for( i=0 ; i<n ; i++ ){/*calcula aceleracoes*/
	if( body_list[i].alive ){/*se alive==0, pula essa etapa*/
	    r = pow(body_list[i].pos_x ,2) + pow(body_list[i].pos_y , 2);
	    if( r <= pow( p0.planet_radius ,2 ) ){
		a_x[i] = 0.0;
		a_y[i] = 0.0;
		body_list[i].vel_x = 0.0;
		body_list[i].vel_y = 0.0;
		body_list[i].alive = 0;
		continue;
	    }
	    r = pow( r , 1.5);
	    a_x[i] -= (p0.planet_mass) * body_list[i].pos_x  / r;
	    a_y[i] -= (p0.planet_mass) * body_list[i].pos_y  / r;
	    for( j=0 ; j<i ; j++ ){
		r = pow(body_list[j].pos_x-body_list[i].pos_x,2)+pow(body_list[j].pos_y-body_list[i].pos_y , 2);
		if( r <= pow( body_list[i].size ,2 ) ){
		    a_x[i] = 0.0;
		    a_y[i] = 0.0;
		    body_list[i].vel_x = 0.0;
		    body_list[i].vel_y = 0.0;
		    body_list[i].alive = 0;
		    break;
		}
		r = pow( r , 1.5) ;
		a_x[i] += (body_list[j].mass) * ((body_list[j].pos_x) - (body_list[i].pos_x)) / r;
		a_y[i] += (body_list[j].mass) * ((body_list[j].pos_y) - (body_list[i].pos_y)) / r;
	    }
	    for( j=i+1 ; j<n ; j++ ){
		r = pow(body_list[j].pos_x-body_list[i].pos_x,2)+pow(body_list[j].pos_y-body_list[i].pos_y , 2);
		if( r <= pow( body_list[i].size ,2 ) ){
		    a_x[i] = 0.0;
		    a_y[i] = 0.0;
		    body_list[i].vel_x = 0.0;
		    body_list[i].vel_y = 0.0;
		    body_list[i].alive = 0;
		    break;
		}
		r = pow( r , 1.5) ;
		a_x[i] += (body_list[j].mass) * ((body_list[j].pos_x) - (body_list[i].pos_x)) / r;
		a_y[i] += (body_list[j].mass) * ((body_list[j].pos_y) - (body_list[i].pos_y)) / r;
	    }
	    a_x[i] *= G;
	    a_y[i] *= G;
	}
    }/* fim de calcula aproximacoes */
    for( i=0 ; i<n ; i++ ){	/*atualiza pos, vel*/
	if( body_list[i].alive ){/*se alive==0, pula essa etapa*/
	    body_list[i].pos_x += (body_list[i].vel_x)*(p0.delta_t) + a_x[i]*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_x*/
	    body_list[i].pos_y += (body_list[i].vel_y)*(p0.delta_t) + a_y[i]*(p0.delta_t)*(p0.delta_t)/2;/*atualiza pos_y*/
	    body_list[i].vel_x += a_x[i]*(p0.delta_t);
	    body_list[i].vel_y += a_y[i]*(p0.delta_t);
	}
    }
    free(a_x);
    free(a_y);
    a_x = NULL;
    a_y = NULL;
    return;
}

/*
debug_print_constants():
função para depuração; imprime
os valores armazenados na constants p0
*/
void debug_print_constants(){
    printf("%f %f %f %s %s %d %f\n", p0.planet_mass, p0.planet_radius, p0.total_time, p0.name1, p0.name2, p0.projectiles_quantity, p0.projectiles_lifespan);
    return;
}

/*
debug_print_bodies():
função para depuração; imprime
valores armazenados no vetor de corpos bodies
*/
void debug_print_bodies(){
    int i, n;
    for( i=0 , n=p0.projectiles_quantity+2 ; i<n ; i++ )
	printf("%f %f %f %f %f\n", body_list[i].mass, body_list[i].pos_x, body_list[i].pos_y, body_list[i].vel_x, body_list[i].vel_y);
    return;
}

/*
debug_print_positions():
funcao para depuracao;
imprime a coordenada x e y da posição de cada um
dos corpos do vetor body_list
*/
void debug_print_positions(corpo *bodies, int n){
    int i;
    for( i=0 ; i<n ; i++ )
	printf("%.2e %.2e  ", bodies[i].pos_x, bodies[i].pos_y);
    printf("\n");
    return;
}

/*
border_control():
Verifica se há algum corpo fora da tela;
caso positivo, coloca o corpo de volta na borda oposta,
a fim de se obter um espaço "toroidal"
*/
void border_control(){
    int i, n;
    n = p0.projectiles_quantity + 2;
    for( i=0 ; i<n ; i++){
	if( body_list[i].pos_x > p0.L ){ /*passou da borda da direita?*/
	    body_list[i].pos_x = -p0.L;
	    if( body_list[i].vel_x < 0 ) /*está virado pra fora?*/
		body_list[i].vel_x *= -1;
	}
	if( body_list[i].pos_x < -p0.L ){ /*passou da borda da esquerda?*/
	    body_list[i].pos_x = p0.L;
	    if( body_list[i].vel_x > 0 )/*está virado pra fora?*/
		body_list[i].vel_x *= -1;
	}
	if( body_list[i].pos_y > p0.H ){ /*passou da borda de cima?*/
	    body_list[i].pos_y = -p0.H;
	    if( body_list[i].vel_y < 0 )/*está virado pra fora?*/
		body_list[i].vel_y *= -1;
	}
	if( body_list[i].pos_y < -p0.H ){ /*passou da borda de baixo?*/
	    body_list[i].pos_y = p0.H;
	    if( body_list[i].vel_y > 0 )/*está virado pra fora?*/
		body_list[i].vel_y *= -1;
	}
    }
    return;
}
