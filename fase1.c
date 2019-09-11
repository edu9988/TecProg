#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Mt 6.02e24
#define Rt 6.4e6
#define G 6.67e-11

typedef struct{
    char *name;
    double mass;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
}nave;

typedef struct{
    double mass;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
}corpo;

typedef struct{
    double planet_mass;
    double planet_radius;
    double total_time;
    int projectiles_quantity;
    double projectiles_lifespan;
}global_params;

void read_entry_file(global_params *p0, nave *s1, nave *s2, corpo **corpos);
void *mallocSafe(int nbytes);
void string_copy(char *a, char *b);
void next_pos(global_params *p0, nave *s1, nave *s2, corpo **corpos);

int main(int argc, char *argv[]){
    double delta_t;
    if( argc == 1 ){
	printf("Specify step length\n>>>");
	scanf("%lf", &delta_t);
    }
    else if( argc == 2 )
	delta_t = atof( argv[1] );
    else{
	printf("Expected fewer arguments\n");
	return 0;
    }
    nave ship1;
    nave ship2;
    corpo *body_list;
    global_params parametros;
    read_entry_file( &parametros , &ship1 , &ship2 , &body_list );

    /*	free's section	*/
    free( ship1.name );
    ship1.name = NULL;
    free( ship2.name );
    ship2.name = NULL;
    free( body_list );
    body_list = NULL;
    return 0;
}

void read_entry_file(global_params *p0, nave *s1, nave *s2, corpo **corpos){
    char aux_name[30];
    FILE *arq;
    arq = fopen("entry.dat", "r");
    if( !arq ){
	printf("Error opening entry file\n");
	exit(EXIT_FAILURE);
    }
    /*	Planet		*/
    fscanf(arq, "%lf", &(p0->planet_mass));
    fscanf(arq, "%lf", &(p0->planet_radius));
    fscanf(arq, "%lf", &(p0->total_time));
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    s1->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s1->name );
    fscanf(arq, "%lf", &(s1->mass));
    fscanf(arq, "%lf", &(s1->pos_x));
    fscanf(arq, "%lf", &(s1->pos_y));
    fscanf(arq, "%lf", &(s1->vel_x));
    fscanf(arq, "%lf", &(s1->vel_y));
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    s2->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s2->name );
    fscanf(arq, "%lf", &(s2->mass));
    fscanf(arq, "%lf", &(s2->pos_x));
    fscanf(arq, "%lf", &(s2->pos_y));
    fscanf(arq, "%lf", &(s2->vel_x));
    fscanf(arq, "%lf", &(s2->vel_y));
    /*	Projectiles	*/
    fscanf(arq, "%d", &(p0->projectiles_quantity));
    *corpos = mallocSafe( p0->projectiles_quantity*sizeof(corpo) );
    printf("%d ", p0->projectiles_quantity);
    fscanf(arq, "%lf", &(p0->projectiles_lifespan));
    printf("%lf\n", p0->projectiles_lifespan);
    for( int i=0; i<p0->projectiles_quantity ; i++ ){
	fscanf(arq, "%lf", &((*corpos)[i].mass));
	fscanf(arq, "%lf", &((*corpos)[i].pos_x));
	fscanf(arq, "%lf", &((*corpos)[i].pos_y));
	fscanf(arq, "%lf", &((*corpos)[i].vel_x));
	fscanf(arq, "%lf", &((*corpos)[i].vel_y));
    }
    fclose(arq);
    return;
}

void *mallocSafe(int nbytes){
    void *pointer;
    pointer = malloc(nbytes);
    if( pointer == NULL ){
	printf("Malloc failed\n");
	exit(EXIT_FAILURE);
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

void next_pos(global_params *p0, nave *s1, nave *s2, corpo **corpos){
    return;  /*to be done*/
}
