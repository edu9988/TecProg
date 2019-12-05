CFLAGS = -Wall -ansi -pedantic -O2 -Wno-unused-result
CLIBS = -lm -lXpm -lX11
 CC = gcc
 EXECUTABLE = spacewar
###########################################################################

run: $(EXECUTABLE)
	./$^

$(EXECUTABLE): fase4.o space.o xwc.o grafico.o teclado.o lista.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

kbtest:	kb
	./kb

kb: kb.o xwc.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)
clean:
	rm -f *.o $(EXECUTABLE) kb
