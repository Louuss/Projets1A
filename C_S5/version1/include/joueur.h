#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include "carte.h"

typedef struct joueur* joueur;

//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
void supprimer_joueur(joueur j);

//Renvoie le numero de la carte choisie aleatoirement dans la main du joueur
int choisir_carte(joueur j);

//Cette fonction defausse toutes les cartes en main du joueur
void defausser(joueur j);

//Pioche dans le deck la carte du dessus
void piocher(joueur j, int i);

//Augmente l'idée du gain du joueur
void augmenter_idee(joueur j);

//Affiche la main du joueur
void afficher_main(joueur j);


//Fonction get
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
carte get_carte_main(int i, joueur j);

//Fonction set
void set_numero(joueur j,int a);
void set_energie(joueur j,int a);
void set_idee(joueur j,int a);
void set_gain(joueur j,int a);
void set_nb_carte(joueur j,int a);
void set_carte_main(int i, joueur j, carte c);


#endif
