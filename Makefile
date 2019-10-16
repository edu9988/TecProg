CFLAGS = -Wall -ansi -pedantic -O2 -Wno-unused-result
CLIBS = -lm -lXpm -lX11
 CC = gcc
 EXECUTABLE = exec
###########################################################################

run: $(EXECUTABLE)
	./$^ 0.001

$(EXECUTABLE): fase2.o space.o xwc.o
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)
