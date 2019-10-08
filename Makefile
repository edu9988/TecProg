CFLAGS = -Wall
 CC = gcc
 EXECUTABLE = exec
###########################################################################

run: $(EXECUTABLE)
	./$^ 0.001

$(EXECUTABLE): fase2.o space.o xwc.o
	$(CC) $(CFLAGS) $^ -o $@ -lm -lXpm -lX11
