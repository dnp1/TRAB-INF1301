CC=gcc
CFLAGS=-I. -I../linux_devel -I../obj -I../headers -L../lib -std=c99 -Wall -O0 -
+CFLAGS=-Wall

all: grafo
grafo: 
	$(CC) $(CFLAGS) -c GRAFO.c -o ../obj/GRAFO.o
teste-grafo: grafo
	$(CC) $(CFLAGS) -c TESTGRA.c -o ../obj/TESTGRA.o
	$(CC) $(CFLAGS) -o ../bin/teste_grafo.exe GRAFO.o TESTGRA.o libArcaboucoTeste.a
clean:
	rm *.o
	rm *.exe
