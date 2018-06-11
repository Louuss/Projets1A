#ifndef _CARTE_H_
#define _CARTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct carte* carte;
typedef void (*pointeur_fonction)(int j, int ad, bool ami, int num_ami);


//Fonctions associées a la structure carte
carte creer_carte(char* nom);
int get_cout(carte c);
int get_rarete(carte c);
char* get_nom(carte c);
void set_cout(carte c, int a);
void set_rarete(carte c, int a);
void set_nom(carte c, char* s);
void supprimer_carte(carte c);
carte copie_carte(carte c);
carte choisir_aleatoirement_carte();
pointeur_fonction get_application_carte(carte c);

#endif
