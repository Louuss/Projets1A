#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

//Pointeur sur la structure de plateau
typedef struct plateau_de_jeu* plateau_de_jeu;

//fonction associé au plateau
void creer_plateau(int nb_joueur);
void supprimer_plateau();

//Fonction d'affichage
void afficher_resultat(int tour);
void afficher_joueurs();

//Classe le numero du joueur dans un tableau de classement
void classer_joueur(int numero);
void classe_joueur_egalite(int num1, int num2); 

//Le joueur quitte la partie
void quitte_partie(int numj);

//traite la carte i du joueur et attaque l'adversaire
void traiter_carte(int i, joueur moi, joueur adversaire);

//Fonction get
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);


#endif
