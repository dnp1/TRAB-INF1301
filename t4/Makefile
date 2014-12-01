CC=gcc
CFLAGS=-I. -L. -O0 -g -DDEBUG -fpermissive -Wno-write-strings #-fdiagnostics-color="always"

all: teste-grafo
grafo:
	$(CC) $(CFLAGS) -c -x c++ GRAFO.c -o GRAFO.o
lista:
	$(CC) $(CFLAGS) -c -x c++ LISTA.c -o LISTA.o
teste-grafo:
	$(CC) $(CFLAGS) -c -x c++ TESTGRA.c -o TESTGRA.o
	$(CC) $(CFLAGS) -o teste_grafo.exe -lArcaboucoTeste LISTA.o GRAFO.o TESTGRA.o
clean:
	rm *.gch -f
	rm *.o -f
	rm *.exe -f

