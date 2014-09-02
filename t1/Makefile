CC=gcc
CFLAGS=-I. -ansi -Wall -g -O0 -fdiagnostics-color=auto
+CFLAGS=-Wall

all:
	echo "read the file"
lista:
	$(CC) $(CFLAGS) -c LISTA.C
arvore:
	$(CC) $(CFLAGS) -c ARVORE.C 
	
teste-lista: lista
	$(CC) $(CFLAGS) -c TESTLIS.C
	$(CC) $(CFLAGS) -o teste_lista LISTA.o TESTLIS.o libArcaboucoTeste.a

teste-arvore: lista arvore
	$(CC) $(CFLAGS) -c TESTARV.C
	$(CC) -o teste_arvore -L. -lArcaboucoTeste libArcaboucoTeste.a  LISTA.o ARVORE.o TESTARV.o 
clean:
	rm *.o


