#ifndef _CARTE_H_
#define _CARTE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct carte* carte;


//Fonctions associées a la structure carte
carte creer_carte(char* nom);
void supprimer_carte(carte c);

//Renvoie une copie de la carte passée en parametre
carte copie_carte(carte c);

//Creer une carte aleatoirement en fonction des probabilité
carte choisir_aleatoirement_carte();

//Fonctions get
int get_cout(carte c);
int get_rarete(carte c);
char* get_nom(carte c);
//Fonction set
void set_cout(carte c, int a);
void set_rarete(carte c, int a);
void set_nom(carte c, char* s);

#endif
