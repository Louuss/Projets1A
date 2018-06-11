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
void afficher_tab_ami_plateau();
void augmenter_nb_ami_plateau();
void classer_joueur(int numero);
void quitte_partie(int numj);
int get_nb_joueur_vivant();
void set_nb_joueur_vivant();
int get_nb_joueur();
int get_nb_ami_plateau();
ami get_ami_tab(int num);
ami get_ami_indice(int i);
joueur get_joueur(int i);
joueur get_joueur_tab(int num);
void set_ami_plateau(int i, ami a);
void traiter_carte(bool ami, carte c, int num_joueur, int num_adversaire, int num_ami);
void supprimer_plateau();
void ami_mort_plateau(int numj);


#endif
