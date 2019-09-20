#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Mt 6.02e24
#define Rt 6.4e6
#define G 6.67e-11

typedef struct{
    double mass;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
}corpo;

typedef struct{
    double delta_t;
    double planet_mass;
    double planet_radius;
    double total_time;
    char *name1;
    char *name2;
    int projectiles_quantity;
    double projectiles_lifespan;
}constants;

void read_entry_file(constants *, corpo **);
void *mallocSafe(unsigned int);
void string_copy(char *, char *);
void next_pos(constants *, corpo *, int);
void corpo_copy(corpo, corpo *);
void print_constants(constants);
void print_bodies(corpo *, int);
void print_positions(corpo *, int);

int main(int argc, char *argv[]){
    constants parametros;
    if( argc == 1 ){
	printf("Specify step length\n>>>");
	scanf("%lf", &(parametros.delta_t));
    }
    else if( argc == 2 )
	parametros.delta_t = atof( argv[1] );
    else{
	printf("Expected fewer arguments\n");
	return 0;
    }
    corpo *body_list;
    read_entry_file( &parametros , &body_list );
    
    for( int i=0 ; i<10 ; i++){
	//print_positions(body_list, parametros.projectiles_quantity+2);
	next_pos(&parametros, body_list, (parametros.projectiles_quantity)+2);
    }

    /*	free's section	*/
    free( parametros.name1 );
    parametros.name1 = NULL;
    free( parametros.name2 );
    parametros.name2 = NULL;
    free( body_list );
    body_list = NULL;
    return 0;
}

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
    fscanf(arq, "%le", &(p0->planet_mass));
    fscanf(arq, "%le", &(p0->planet_radius));
    fscanf(arq, "%lf", &(p0->total_time));
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    p0->name1 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0->name1 );
    fscanf(arq, "%lf", &(s1.mass));
    fscanf(arq, "%lf", &(s1.pos_x));
    fscanf(arq, "%lf", &(s1.pos_y));
    fscanf(arq, "%lf", &(s1.vel_x));
    fscanf(arq, "%lf", &(s1.vel_y));
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    p0->name2 = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , p0->name2 );
    fscanf(arq, "%lf", &(s2.mass));
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
	fscanf(arq, "%lf", &((*bodies)[i+2].pos_x));
	fscanf(arq, "%lf", &((*bodies)[i+2].pos_y));
	fscanf(arq, "%lf", &((*bodies)[i+2].vel_x));
	fscanf(arq, "%lf", &((*bodies)[i+2].vel_y));
    }
    fclose(arq);
    return;
}

void corpo_copy(corpo a, corpo *b){
    b->mass = a.mass;
    b->pos_x = a.pos_x;
    b->pos_y = a.pos_y;
    b->vel_x = a.vel_x;
    b->vel_y = a.vel_y;
    return;
}

void *mallocSafe(unsigned int nbytes){
    void *pointer;
    pointer = malloc(nbytes);
    if( pointer == NULL ){
	fprintf(stderr, "Failed to malloc %u bytes\n", nbytes);
	exit(-1);
    }
    return pointer;
}

void string_copy(char *a, char *b){
    int i;
    for( i=0 ; i<strlen(a) ; i++ )
	b[i] = a[i];
    b[i] = '\0';
    return;
}

void next_pos(constants *p0, corpo *bodies, int n){
    double *a_x = mallocSafe(n*sizeof(double));
    double *a_y = mallocSafe(n*sizeof(double));
    double r;
    for( int i=0 ; i<n ; i++ ){/*inicializa vetores a_x e a_y*/
	a_x[i] = 0;
	a_y[i] = 0;
    }
    for( int i=0 ; i<n ; i++ ){/*calcula aceleracoes*/
	r = pow((bodies[i]).pos_x ,2) + pow((bodies[i]).pos_y , 2);
	r = pow( r , 1.5);
	a_x[i] -= (p0->planet_mass) * (bodies[i]).pos_x  / r;
	a_y[i] -= (p0->planet_mass) * (bodies[i]).pos_y  / r;
	for( int j=0 ; j<i ; j++ ){
	    r = pow((bodies[j]).pos_x-(bodies[i]).pos_x,2)+pow((bodies[j]).pos_y-(bodies[i]).pos_y , 2);
	    r = pow( r , 1.5) ;
	    a_x[i] += ((bodies[j]).mass) * (((bodies[j]).pos_x) - ((bodies[i]).pos_x)) / r;
	    a_y[i] += ((bodies[j]).mass) * (((bodies[j]).pos_y) - ((bodies[i]).pos_y)) / r;
	}
 	for( int j=i+1 ; j<n ; j++ ){
	    r = pow((bodies[j]).pos_x-(bodies[i]).pos_x,2)+pow((bodies[j]).pos_y-(bodies[i]).pos_y , 2);
	    r = pow( r , 1.5) ;
	    a_x[i] += ((bodies[j]).mass) * (((bodies[j]).pos_x) - ((bodies[i]).pos_x)) / r;
	    a_y[i] += ((bodies[j]).mass) * (((bodies[j]).pos_y) - ((bodies[i]).pos_y)) / r;
	}
	//a_x[i] *= G;
	//a_y[i] *= G;
	//printf("%lf\n", a_x[i]);
    }
    for( int i=0 ; i<n ; i++ ){	/*atualiza pos, vel*/
	printf("%lf %lf %lf %lf %lf %lf %lf\n", bodies[i].mass, bodies[i].pos_x, bodies[i].pos_y, bodies[i].vel_x, bodies[i].vel_y, a_x[i], a_y[i]);
	(bodies[i]).pos_x += (bodies[i].vel_x)*(p0->delta_t) + (a_x[i])*(p0->delta_t)*(p0->delta_t)/2;
	(bodies[i]).pos_y += (bodies[i].vel_y)*(p0->delta_t) + (a_y[i])*(p0->delta_t)*(p0->delta_t)/2;
	(bodies[i]).vel_x += (a_x[i])*(p0->delta_t);
	(bodies[i]).vel_y += (a_y[i])*(p0->delta_t);
    }
    printf("\n");
    free(a_x);
    free(a_y);
    a_x = NULL;
    a_y = NULL;
    return;
}

void print_constants(constants p0){
    printf("%lf %lf %lf %s %s %d %lf\n", p0.planet_mass, p0.planet_radius, p0.total_time, p0.name1, p0.name2, p0.projectiles_quantity, p0.projectiles_lifespan);
    return;
}

void print_bodies(corpo *bodies, int n){
    for( int i=0 ; i<n ; i++ )
	printf("%lf %lf %lf %lf %lf\n", (bodies[i]).mass, (bodies[i]).pos_x, (bodies[i]).pos_y, (bodies[i]).vel_x, (bodies[i]).vel_y);
    return;
}

void print_positions(corpo *bodies, int n){
    for( int i=0 ; i<n ; i++ )
	printf("%.2lf\t\t%.2lf\t\t\t", (bodies[i]).pos_x, (bodies[i]).pos_y);
    printf("\n");
    return;
}
