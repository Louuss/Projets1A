#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"



//Pointeur sur le entité de la liste
typedef struct memento* memento;

//Pointeur sur la tete de liste
typedef struct memento_list* memento_list;

//Fonction de creation et de suppression du memento
memento_list creer_memento();
void supprimer_tout_memento(memento_list m);
void supprimer_memento(memento m);

//Principe de la FIFO on recupere de debut de liste et on ajoute a la fin 
memento_list ajouter_memento_fin(memento_list m, carte c);
memento_list supprimer_memento_debut(memento_list m);

//rempli le deck de 50 cartes (MEMENTO)
memento_list remplir_memento(memento_list m);

//melange le memento
memento_list melanger_memento(memento_list memento);

//Fonction get
carte get_carte(memento m);
memento get_suivant(memento m);
memento get_premier(memento_list lm);
int get_longueur(memento_list lm);

//Fonction d'affichage
void afficher_memento(memento_list m);

#endif
