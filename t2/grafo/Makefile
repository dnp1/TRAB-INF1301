CC=gcc
CFLAGS=-I. -I../lib -I../headers -std=c99 -Wall -O0 -fdiagnostics-color=auto -fpermissive
+CFLAGS=-Wall

all: teste-grafo
lista:
	cd ../lista/ && $(MAKE) lista
grafo: 
	$(CC) $(CFLAGS) -c -x c++ GRAFO.c -o ../obj/GRAFO.o
teste-grafo: lista grafo
	$(CC) $(CFLAGS) -c -x c++ TESTGRA.c -o ../obj/TESTGRA.o
	cd ../obj && $(CC) -o ../bin/teste_grafo.exe -lArcaboucoTeste LISTA.o GRAFO.o TESTGRA.o
clean:
	rm *.o
	rm *.exe
