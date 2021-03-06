#ifndef _GRILLE_H_
#define _GRILLE_H_


#include <stdio.h>
#include <stdbool.h>


typedef struct grille_de_jeu* grille;

void creer_grille(int nb_joueur);
void supprimer_grille();
bool est_libre(int x, int y);
void afficher_grille();


void creer_bloc(int x,int y);
void remplir_grille(int x, int y, int numj, bool ami);
void deplacement_total(int numj);
void faire_deplacement_simultanement();
int est_joueur(int x, int y);
bool est_encercle(int x, int y);
void afficher_position();
void augmenter_nb_ami();
int nb_ami_g();
void autoriser(int i);
void non_autoriser(int i);
void remplir_grille_droma(int x, int y);



#endif
