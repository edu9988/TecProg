#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *name;
    float mass;
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
}nave;

void read_entry_file(nave *s1, nave *s2);
void *mallocSafe(int nbytes);
void string_copy(char *a, char *b);

int main(){
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
    float aux_float;
    FILE *arq;
    arq = fopen("entry.dat", "r");
    if( !arq ){
	printf("Error opening entry file\n");
	exit(EXIT_FAILURE);
    }
    /*	Planet		*/
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f \n", aux_float);
    /*	Spacecraft 1	*/
    fscanf(arq, " %s", aux_name);
    s1->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s1->name );
    printf("%s ", aux_name);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f\n", aux_float);
    /*	Spacecraft 2	*/
    fscanf(arq, " %s", aux_name);
    s2->name = mallocSafe( (1+strlen(aux_name))*sizeof(char) );
    string_copy( aux_name , s2->name );
    printf("%s ", aux_name);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f ", aux_float);
    fscanf(arq, "%f", &aux_float);
    printf("%f\n", aux_float);
    /*	Projectiles	*/
    fscanf(arq, "%d", &aux_int);
    printf("%d ", aux_int);
    fscanf(arq, "%f", &aux_float);
    printf("%f\n", aux_float);
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


