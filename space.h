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
header file com a interface usada pelo programa fase3.c
*/

#define Rt 6.4e6
#define Mt 6.02e24
#define G 6.67e-11

/*
corpo:
armazena os dados de cada objeto que terá suas posições atualizadas
a cada iteração do programa fase3.c
*/

typedef struct corpox Corpo;
struct corpox
{
    double mass;
    double size;
    int alive;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
    double a_x;
    double a_y;
    int SCR_pos_x;
    int SCR_pos_y;
    double angulo;
    int acelera;
    int tipo;
    Corpo *prox;
};

typedef struct{
    double mass;
    double size;
    int alive;
    double pos_x;
    double pos_y;
    double vel_x;
    double vel_y;
    double a_x;
    double a_y;
    int SCR_pos_x;
    int SCR_pos_y;
    double angulo;
    int acelera;
}corpo;

/*
constants:
armazena os dados do programa fase3.c que não sofrem alterações
durante os cálculos das trajetórias
*/
typedef struct{
    double delta_t;
    double planet_radius;
    double planet_mass;
    char *name1;
    char *name2;
    int projectiles_quantity;
    double projectiles_lifespan;
    double L;/*largura do universo*/
    double H;/*altura do universo*/
}constants;

void init_modulo_space();
void next_pos();
void debug_print_constants();
void debug_print_bodies();
void debug_print_positions();
void border_control();
void termina_modulo_space();

/********************************************/
void addObjLista(Corpo *obj);
void addProjeteis(double pos_x, double pos_y, double vel_x, double vel_y);
void mostrarLista();
void borderControl();
void nextPos();

/**********************************************/
