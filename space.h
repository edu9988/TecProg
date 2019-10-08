/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 set 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/

/*
space.h
header file com a interface usada pelo programa fase1.c
*/

#define Rt 6.4e6
#define Mt 6.02e24
#define G 6.67e-11

typedef struct{
    double mass;
    double size;
    int alive;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
}corpo;

/*
corpo
armazena os dados de cada objeto que terá suas posições atualizadas
a cada iteração do programa fase1.c
*/

typedef struct{
    double delta_t;
    double planet_radius;
    double planet_mass;
    double total_time;
    char *name1;
    char *name2;
    int projectiles_quantity;
    double projectiles_lifespan;
}constants;

/*
constants
armazena os dados do programa fase1.c que não sofrem alterações
durante os cálculos das trajetórias
*/

void read_entry_file(constants *, corpo **);
void *mallocSafe(unsigned int);
void string_copy(char *, char *);
void next_pos(constants *, corpo *, int);
void corpo_copy(corpo, corpo *);
void print_constants(constants);
void print_bodies(corpo *, int);
void print_positions(corpo *, int);