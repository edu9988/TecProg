/**************************************************************/
/* José Eduardo R. M. Peres y Peres       No. USP:8945332     */
/* Marcelo Nascimento dos Santos Junior	  No. USP:11222012    */
/* Gilvane da Silva Sousa		  No. USP:10258726    */
/*							      */
/* Projeto - Primeira fase - 22 set 2019                      */
/* Curso MAC0216  - Prof. Marco Dimas Gubitoso		      */
/**************************************************************/
CFLAGS = -Wall
 CC = gcc
 EXECUTABLE = exec
 SAIDA = saida.txt
###########################################################################

plot: $(EXECUTABLE) $(SAIDA)
	./read.m

$(SAIDA): $(EXECUTABLE) entry.dat
	./$(EXECUTABLE) 0.001 > $(SAIDA)

$(EXECUTABLE): fase1.c space.c
	$(CC) $(CFLAGS) $^ -o $@ -lm
