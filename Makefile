 CFLAGS = -Wall
 CC = gcc
 EXECUTABLE = exec
 SAIDA = saida.txt
###########################################################################

plot: $(EXECUTABLE) $(SAIDA)
	./read.m

$(SAIDA): $(EXECUTABLE) entry.dat
	./$(EXECUTABLE) 0.001 > $(SAIDA)

$(EXECUTABLE): fase1.c 
	$(CC) $(CFLAGS) $? -o $@ -lm
