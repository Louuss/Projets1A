#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "carte.h"
#include "ami.h"

typedef struct joueur* joueur;



//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
void supprimer_joueur(joueur j);

//Augmente le nombre d'ami associé au joueur
void augmenter_nb_ami_joueur(joueur j);

//Savoir si l'ami d'un joueur est mort
void ami_mort(joueur j, int numj);

//Choisi une carte aleatoirement
int choisir_carte(joueur j);

//Defausse toutes les cartes de la main du joueur
void defausser(joueur j);

//Le joueur j recupere une carte du memento et la place dans sa main a la position i
void piocher(joueur j, int i);

//Augmente l'idee du joueur du gain  
void augmenter_idee(joueur j);

//Savoir si le joueur est mort
bool est_mort(joueur j);

//Fonction get
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
carte get_carte_main(int i, joueur j);
int get_position_x(joueur j);
int get_position_y(joueur j);
struct position get_position(joueur j);
int get_nb_ami(joueur j);
ami get_ami(int i, joueur j);

//Fonction set
void set_numero(joueur j, int a);
void set_energie(joueur j, int a);
void set_idee(joueur j, int a);
void set_gain(joueur j, int a);
void set_nb_carte(joueur j, int a);
void set_carte_main(int i, joueur j, carte c);
void set_position_x(joueur j, int vx);
void set_position_y(joueur j, int vy);
void set_ami(int i, joueur j, ami a);
void set_nb_ami(joueur j, int i);

//Fonction d'affichage
void afficher_main(joueur j);


#endif
