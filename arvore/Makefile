all:
	mkdir src
	cat ARVORE.C | sed 's/ARVORE.H/ARVORE.h/' > src/ARVORE.c
	cp ARVORE.H src/ARVORE.h
	cd src; \
		gcc -fdiagnostics-color=auto -c ARVORE.c ARVORE.h
	pwd
	cd src; \
		mv *.obj ../obj/;
	cd ../obj; \
		gcc -o arvore *;
	rm -R src;
#	-rm -R src
