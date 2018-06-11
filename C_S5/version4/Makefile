
# Makefile

#le nom du fichier executable

OUTFILE = test-1 version4

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

test-1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/ami.o obj/grille.o obj/test-1.o
	$(CC) $^ -o $@ && ./test-1
	
version4: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/grille.o obj/ami.o obj/version4.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c plateau.h joueur.h carte.h memento.h grille.h definition.h
version4.o: version4.c plateau.h joueur.h carte.h memento.h grille.h ami.h definition.h
carte.o: carte.c carte.h joueur.h grille.h definition.h
joueur.o: ami.h joueur.h carte.h joueur.c definition.h
memento.o: memento.h carte.h memento.c definition.h
plateau.o: plateau.h joueur.h carte.h grille.h plateau.c definition.h
grille.o: grille.h grille.c definition.h
ami.o: joueur.h grille.h ami.h ami.c definition.h

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS) *.dSYM
