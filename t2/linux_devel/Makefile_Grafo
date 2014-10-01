CC=gcc
CFLAGS=-I.  -std=c99 -Wall -O0 -fdiagnostics-color=auto
+CFLAGS=-Wall

all: grafo
lista:
	cd ../lista/ && $(MAKE) lista
grafo: 
	$(CC) $(CFLAGS) -c GRAFO.c -o ../obj/GRAFO.o
teste-grafo: lista grafo
	$(CC) $(CFLAGS) -c TESTGRA.c -o ../obj/TESTGRA.o
	cd ../obj && $(CC) -o ../bin/teste_grafo.exe -L../lib -lArcaboucoTeste libArcaboucoTeste.a LISTA.o GRAFO.o TESTGRA.o 
clean:
	rm *.o
	rm *.exe
