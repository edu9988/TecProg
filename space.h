/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Quarta fase - 02 dez 2019			      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/

/*
space.h
header file com a interface usada pelo programa fase4.c
*/

#ifndef _SPACE_

    #define _SPACE_

    #define Rt 6.4e6
    #define Mt 6.02e24
    #define G 6.67e-11

    /*
    corpo:
    armazena os dados de cada objeto que terá suas posições atualizadas
    a cada iteração do programa fase3.c
    */
    typedef struct corpo Cel;
    struct corpo{
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
        Cel *ant;
	Cel *prox;
    };

    /*
    constants:
    armazena os dados do programa fase3.c que não sofrem alterações
    durante os cálculos das trajetórias
    */
    typedef struct{
        double delta_t;
        double planet_radius;
        double planet_mass;
        int n_proj;
        double L;/*largura do universo*/
        double H;/*altura do universo*/
	int jogando;
	int menu;
    }constants;

    extern constants p0;

    void init_modulo_space();
    void next_pos();
    void debug_print_constants();
    void debug_print_bodies();
    void debug_print_positions();
    void border_control();
    void termina_modulo_space();
    void disparo( Cel *origem );

#endif
