#ifndef _PROJET_1_H_
#define _PROJET_1_H_

#include <stdio.h>
#include <stdlib.h>

//Pointeur sur une structure de plateau
typedef struct plateau_de_jeu* plateau_de_jeu;
//Pointeur sur une structure de joueur
typedef struct joueur* joueur;
//Pointeur sur une structure de carte
typedef struct carte* carte;

int rand_a_b(int a, int b);

//Fonctions associées a la structure carte
carte creer_carte(char* nom);
void supprimer_carte(carte c);
//creer une carte aleatoirement en fonction des probabilites
carte choisir_aleatoirement_carte();

//Les fonctions get
char* get_nom(carte c);
int get_cout(carte c);
int get_rarete(carte c);
//Les fonctions set
void set_cout(carte c, int a);
void set_rarete(carte c, int a);
void set_nom(carte c, char* s);


//Fonction associé a la structure joueur
joueur creer_joueur(int numero);
void supprimer_joueur(joueur j);
//Choisi aleatoirement une carte dans la main du joueur
int choisir_carte(joueur j);
//rajoute une nouvelle carte a la position de la carte precedement jouée 
void piocher(joueur j, int i);
//Augmente de l'idee du gain du joueur
void augmenter_idee(joueur j);

//Les fonctions get 
int get_numero(joueur j);
int get_energie(joueur j);
int get_idee(joueur j);
int get_gain(joueur j);
int get_nb_carte(joueur j);
carte get_carte(joueur j , int i);
//Les fonctions set
void set_carte_main(int i, joueur j, carte c);
void set_idee(joueur j, int a);


//fonction associé au plateau
void creer_plateau(int nb_joueur);
void supprimer_plateau() ;
//Le joueur qui n'a plus d'energie quitte la partie
void quitte_partie(int numj);
//Le joueur apres sa mort est classée dans un tableau qui servira au resultats
void classer_joueur(int numero);

//Les fontions get
int get_nb_joueur_vivant();
int get_nb_joueur();
joueur get_joueur(int i);
int get_classement(int i);

//La fonction traiter carte, traite la carte choisie, puis la supprime.
void traiter_carte(int c, joueur moi, joueur adversaire);


//Fonction d'affichage
void afficher_main(joueur j);
void afficher_joueurs();
void afficher_resultat();

#endif
