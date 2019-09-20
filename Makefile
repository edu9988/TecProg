# LIBDIR = /usr/local/lib
 CFLAGS = -Wall
 CC = gcc
 EXECUTABLE = exec
 SAIDA = saida.txt
###########################################################################

plot: $(EXECUTABLE) $(SAIDA)
	./$(EXECUTABLE) 0.1 > $(SAIDA)
	./read.m

run: $(EXECUTABLE)
	./$(EXECUTABLE) 0.1

comp: fase1.c 
	$(CC) $(CFLAGS) $^ -o $(EXECUTABLE) -lm
