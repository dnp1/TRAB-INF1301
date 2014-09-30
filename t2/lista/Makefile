CC=gcc
CFLAGS=-I. -I../linux_devel -I../obj -std=c99 -Wall -O0 -fdiagnostics-color=auto
+CFLAGS=-Wall

all:
lista: $(CC) $(CFLAGS) -c LISTA.c -o ../obj/LISTA.o

teste-lista: lista
	$(CC) $(CFLAGS) -c TESTLIS.c -o ../obj/TESTLIS.o
	$(CC) $(CFLAGS) -o ../bin/teste_lista.exe LISTA.o TESTLIS.o libArcaboucoTeste.a

clean:
	rm *.o
	rm *.exe
