#ifndef _LISTE_PRIORITE_H_
#define _LISTE_PRIORITE_H_

#include "joueur.h"
#include "ami.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct priorite* priorite;
typedef struct tete_list_prio* tete_list_prio;
typedef struct list_joueur* list_joueur;

void creer_liste_prio();
void ajouter_prio_fin(int p);
void ajouter_prio_debut(int p);
int recuperer_joueur_debut(priorite p);
void ajouter_joueur_fin(joueur j, priorite p);

void ajouter_ami_fin(ami a, priorite p);

priorite inserer_prio(priorite curseur, int priorite);

void replacer_joueur(bool a, joueur j, ami ami);

void supprimer_joueur_list(list_joueur lj);

priorite recuperer_liste_debut();
int get_joueur_list(priorite p);
bool get_ami_bool(priorite p);
void afficher_tete_liste();
void supprimer_tete_liste();
void supprimer_priorite(priorite p);
#endif

