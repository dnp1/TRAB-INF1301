CC=gcc
CFLAGS=-I. -I../linux_devel -I../obj -I../headers -L../lib -std=c99 -Wall -O0 -fdiagnostics-color=auto
+CFLAGS=-Wall

all: lista
lista: 
	$(CC) $(CFLAGS) -c LISTA.c -o ../obj/LISTA.o
teste-lista: lista
	$(CC) $(CFLAGS) -c TESTLIS.c -o ../obj/TESTLIS.o
	$(CC) $(CFLAGS) -o ../bin/teste_lista.exe LISTA.o TESTLIS.o -lArcaboucoTeste

clean:
	rm *.o
	rm *.exe
