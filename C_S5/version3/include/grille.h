#ifndef _GRILLE_H_
#define _GRILLE_H_


#include <stdio.h>
#include <stdbool.h>


typedef struct grille_de_jeu* grille;

//fonction associe a la grille
void creer_grille(int nb_joueur);
void supprimer_grille();

//Foncion qui verifie si la case de coordonnee (x;y) est libre
//renvoie true si est libre
//renvoie false sinon
bool est_libre(int x, int y);

//Fonction d'affichage de la grille
void afficher_grille();
void afficher_position();

//Cree un caramel mou au coordonee (x;y)
void creer_bloc(int x,int y);

//remplie la grille au coordonne (x;y)
//Associe les coordonnees au numero du joueur
//Differencie le fait que ce soit un ami ou un joueur
void remplir_grille(int x, int y, int numj, bool ami);

//Fait les 5 deplacements du joueur numero numj
void deplacement_total(int numj);

//Traite les deplacments des joueurs simultanement 
void faire_deplacement_simultanement();

//Fonction qui permet de savoir si on a un joueur au coordonnee (x;y)
// si oui on renvoi son numero
//sinon on renvoi -1
int est_joueur(int x, int y);

//Fonction qui permet de savoir si on a un joueur au coordonnee (x;y) est encercle
bool est_encercle(int x, int y);

//Augmente le nombre d'ami de 1
void augmenter_nb_ami();

//Renvoie le nombre d'ami qu'il y a sur la grille
int nb_ami_g();

//Fonction qui autorise ou non les deplacements d'un ami
void autoriser(int i);
void non_autoriser(int i);



#endif
