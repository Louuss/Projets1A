#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "grille.h"
#include "ami.h"
#include "carte.h"

typedef struct plateau_de_jeu* plateau_de_jeu;

//fonction associé au plateau
void creer_plateau(int nb_joueur);
void afficher_resultat();
void afficher_joueurs();
void classer_joueur(int numero);
void quitte_partie(int numj);
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);
void traiter_carte(bool ami, carte c, int num_joueur, int num_adversaire, int num_ami);
void supprimer_plateau();
void faire_jouer_ami(joueur j, joueur adversaire, int m, int ad);

#endif
