
# Makefile

#le nom du fichier executable

OUTFILE = test-1 version5

#les fichiers objets
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=obj/%.o)

MAKEFILES := Makefile

#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

$(OBJECTS): $(MAKEFILES)

all: $(OUTFILE)

test-1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/ami.o obj/grille.o obj/test-1.o obj/liste_priorite.o
	$(CC) $^ -o $@ && ./test-1
	
version5: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/grille.o obj/ami.o obj/version5.o obj/liste_priorite.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c plateau.h joueur.h carte.h memento.h grille.h liste_priorite.h
version5.o: version5.c plateau.h joueur.h carte.h memento.h grille.h ami.h liste_priorite.h
carte.o: carte.c carte.h joueur.h grille.h plateau.h
joueur.o: ami.h joueur.h carte.h joueur.c plateau.h
memento.o: memento.h carte.h memento.c
plateau.o: plateau.h joueur.h carte.h grille.h plateau.c liste_priorite.h
grille.o: grille.h grille.c
ami.o: joueur.h grille.h ami.h ami.c
liste_priorite.o: liste_priorite.h liste_priorite.c ami.h joueur.h

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS) *.dSYM
