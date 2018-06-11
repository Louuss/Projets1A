
# Makefile

#le nom du fichier executable

OUTFILE = test-1 version6

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

test-1: obj/carte.o obj/joueur.o obj/memento.o obj/plateau.o obj/ami.o obj/grille.o obj/test-1.o obj/liste_priorite.o obj/dromadulaire.o
	$(CC) $^ -o $@ && ./test-1
	
version6: obj/carte.o obj/joueur.o obj/memento.o obj/ami.o obj/plateau.o obj/grille.o obj/version6.o obj/liste_priorite.o obj/dromadulaire.o
	$(CC) $^ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

test-1.o: test-1.c plateau.h joueur.h carte.h memento.h grille.h  dromaludaire.h liste_priorite.h
version6.o: version6.c plateau.h joueur.h carte.h memento.h grille.h ami.h liste_priorite.h
carte.o: carte.c carte.h joueur.h grille.h plateau.h
joueur.o: ami.h joueur.h carte.h joueur.c plateau.h
memento.o: memento.h carte.h memento.c
plateau.o: plateau.h joueur.h carte.h grille.h ami.h plateau.c liste_priorite.h dromaludaire.h
grille.o: grille.h ami.h joueur.h grille.c
ami.o: joueur.h grille.h ami.h ami.c
liste_priorite.o: liste_priorite.h liste_priorite.c ami.h joueur.h
dromadulaire.o: dromadulaire.h dromadulaire.c grille.h	

.PHONY: clean

clean:
	rm -rf $(OUTFILE) $(OBJECTS) *.dSYM
