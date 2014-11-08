
CC=gcc
CFLAGS=-I. -L. -O0 -g -fpermissive #-fdiagnostics-color="always"

all: lista grafo menu tabuleiro estado principal teste-tabuleiro teste-menu
estado:
	$(CC) $(CFLAGS) -c -x c++ ESTADO.c -o ESTADO.o	
grafo:
	$(CC) $(CFLAGS) -c -x c++ GRAFO.c -o GRAFO.o
lista:
	$(CC) $(CFLAGS) -c -x c++ LISTA.c -o LISTA.o
menu:
	$(CC) $(CFLAGS) -c -x c++ MENU.c -o MENU.o
principal:
	$(CC) $(CFLAGS) -c -x c++ PRINCIPAL.c -o PRINCIPAL.o
	$(CC) $(CFLAGS) -o labirinto.exe PRINCIPAL.o ESTADO.o TABULEIRO.o MENU.o GRAFO.o LISTA.o
tabuleiro:
	$(CC) $(CFLAGS) -c -x c++ TABULEIRO.c -o TABULEIRO.o
teste-menu:
	$(CC) $(CFLAGS) -c -x c++ TESTMEN.c -o TESTMEN.o
	$(CC) $(CFLAGS) -o teste_menu.exe -lArcaboucoTeste TESTMEN.o MENU.o GRAFO.o LISTA.o ESTADO.o TABULEIRO.o
teste-tabuleiro:
	$(CC) $(CFLAGS) -c -x c++ TESTTAB.C -o TESTTAB.o
	$(CC) $(CFLAGS) -o teste_tabuleiro.exe -lArcaboucoTeste TESTTAB.o TABULEIRO.o GRAFO.o LISTA.o 
clean:
	rm *.gch -f
	rm *.o -f
	rm *.exe -f

