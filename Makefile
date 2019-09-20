# LIBDIR = /usr/local/lib
# CFLAGS = -Wall
# CC = gcc
###########################################################################

plot: run
	./exec 1 > saida.txt
	./read.m

run: comp
	./exec 1

comp: fase1.c 
	${CC} ${CFLAGS} $^ -o exec -lm
