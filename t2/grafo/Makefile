CC=gcc
CFLAGS=-I. -I../linux_devel -I../obj -std=c99 -Wall -O0 -fdiagnostics-color=auto
+CFLAGS=-Wall

all: grafo
grafo: 
	$(CC) $(CFLAGS) -c GRAFO.c -o ../obj/GRAFO.o
teste-grafo: grafo
	$(CC) $(CFLAGS) -c TESTGRAFO.c -o ../obj/TESTGRAFO.o
	$(CC) $(CFLAGS) -o ../bin/teste_grafo.exe GRAFO.o TESTGRAFO.o libArcaboucoTeste.a
clean:
	rm *.o
	rm *.exe
