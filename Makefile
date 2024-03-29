CFLAGS = -Wall -ansi -pedantic -O2 -Wno-unused-result -D_POSIX_C_SOURCE=199309L
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
	rm -f *.o $(EXECUTABLE) kb fase4.tar

pack:
	cp *.c fase4;\
	cp *.h fase4;\
	cp Makefile fase4;\
	cp manual fase4;\
	cp planeta1.xpm fase4;\
	cp spaceshuttle_bw2.xpm fase4;\
	cp spaceshuttle_bw3.xpm fase4;\
	cp missiles02.xpm fase4;\
	cd fase4;\
	tar -cf fase4.tar *;\
	cd ..;\
	mv fase4/fase4.tar .
