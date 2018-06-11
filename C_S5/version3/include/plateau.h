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
void supprimer_plateau();

//Fonction d'affichage
void afficher_resultat();
void afficher_joueurs();

//Fonction qui classe le joueur apres sa mort
void classer_joueur(int numero);

//Fonction qui fait quitter la partie au joueur numero numj
void quitte_partie(int numj);

//Fonction get
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);

//Fonction qui traite la carte d'un joueur
void traiter_carte(int i, joueur moi, joueur adversaire);

//Fonction qui traite la carte d'un ami
void traiter_carte_ami(ami a, joueur adversaire, carte c);

//Fonction qui fait jouer les amis d'un joueur j 
void faire_jouer_ami(joueur j, joueur adversaire);

#endif
