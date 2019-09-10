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

void read_entry_file(nave *s1, nave *s2);
void *mallocSafe(int nbytes);
void string_copy(char *a, char *b);

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
    read_entry_file( &ship1 , &ship2 );
    free( ship1.name );
    ship1.name = NULL;
    free( ship2.name );
    ship2.name = NULL;
    return 0;
}

void read_entry_file(nave *s1, nave *s2){
    char aux_name[30];
    int aux_int;
    double aux_double;
    FILE *arq;
    arq = fopen("entry.dat", "r");
    if( !arq ){
	printf("Error opening entry file\n");
	exit(EXIT_FAILURE);
    }
    /*	Planet		*/
    fscanf(arq, "%lf", &aux_double);
    printf("%lf ", aux_double);
    fscanf(arq, "%lf", &aux_double);
    printf("%lf ", aux_double);
    fscanf(arq, "%lf", &aux_double);
    printf("%lf \n", aux_double);
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    s1->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s1->name );
    printf("%s ", aux_name);
    fscanf(arq, "%lf", &(s1->mass));
    printf("%lf ", s1->mass);
    fscanf(arq, "%lf", &(s1->pos_x));
    printf("%lf ", s1->pos_x);
    fscanf(arq, "%lf", &(s1->pos_y));
    printf("%lf ", s1->pos_y);
    fscanf(arq, "%lf", &(s1->vel_x));
    printf("%lf ", s1->vel_x);
    fscanf(arq, "%lf", &(s1->vel_y));
    printf("%lf\n", s1->vel_y);
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    s2->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s2->name );
    printf("%s ", aux_name);
    fscanf(arq, "%lf", &(s2->mass));
    printf("%lf ", s2->mass);
    fscanf(arq, "%lf", &(s2->pos_x));
    printf("%lf ", s2->pos_x);
    fscanf(arq, "%lf", &(s2->pos_y));
    printf("%lf ", s2->pos_y);
    fscanf(arq, "%lf", &(s2->vel_x));
    printf("%lf ", s2->vel_x);
    fscanf(arq, "%lf", &(s2->vel_y));
    printf("%lf\n", s2->vel_y);
    /*	Projectiles	*/
    fscanf(arq, "%d", &aux_int);
    printf("%d ", aux_int);
    fscanf(arq, "%lf", &aux_double);
    printf("%lf\n", aux_double);
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


