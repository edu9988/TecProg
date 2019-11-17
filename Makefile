CFLAGS = -Wall -ansi -pedantic -O2 -Wno-unused-result
CLIBS = -lm -lXpm -lX11
 CC = gcc
 EXECUTABLE = exec
###########################################################################

run: $(EXECUTABLE)
	./$^ 0.001

$(EXECUTABLE): main.o space.o xwc.o grafico.o teclado.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

clean:
	rm -f *.o $(EXECUTABLE)
