#include "../include/carte.h"
#include "../include/definition.h"
#include <string.h>
#include <time.h>


struct carte {
    char* nom;
    int cout;
    int rarete;
};


static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}


// on créé une carte a partir d'un nom de carte 
// et on initialise les champs de la carte en fonction du nom 
carte creer_carte(char* nom) {
    if (nom == NULL) {
        echec("nom NULL: creer_carte()");
        return NULL;
    }

    carte c = calloc(1,sizeof (struct carte));

    if (strcmp(nom, "think") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
    }

    if (strcmp(nom, "steal") == 0) {
        c->nom = nom;
        c->cout = 10;
        c->rarete = 100 / 10;
    }

    if (strcmp(nom, "panacea") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
    }

    if (strcmp(nom, "razor") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
    }


    if (strcmp(nom, "hell") == 0) {
        c->nom = nom;
        c->cout = 100;
        c->rarete = 1;
    }
    return c;
}

void supprimer_carte(carte c){
    free(c);
}

char* get_nom(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_nom()");
        return NULL;
    }

    return c->nom;
}

// les fonction get et set servent a changer ou obtenir les champs des
// objets passés en parametre 

int get_cout(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_cout()");
        return EXIT_FAILURE;
    }

    return c->cout;
}

int get_rarete(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_rarete()");
        return EXIT_FAILURE;
    }

    return c->rarete;
}

void set_cout(carte c, int a) {
    if (c == NULL || a == 0) {
        echec("carte NULL : set_cout()");
        return;
    }

    c->cout = a;
}

void set_rarete(carte c, int a) {
    if (c == NULL || a == 0) {
        echec("carte NULL : set_rarete()");
        return;
    }

    c->rarete = a;
}

void set_nom(carte c, char* s) {
    if (c == NULL || s == NULL) {
        echec("carte NULL : set_nom()");
        return;
    }

    c->nom = s;
}

int rand_a_b(int min, int max) {
  return (rand() % (max - min)) + min;
}

carte copie_carte(carte c){
    return creer_carte(c->nom);
 }

// choisir aleatoirement carte créé une carte en fonction des 
// probabilités données dans le sujet 
carte choisir_aleatoirement_carte() {
    
  int alea = rand_a_b(0, PROBA); // on crée un nombre aléatoire et on choisit quelle carte créer en fonction de sa valeur 

    if (alea < 20) {
        return creer_carte("think");
    } else if (alea < 30) {
        return creer_carte("steal");
    } else if (alea < 80) {
        return creer_carte("panacea");
    } else if (alea < 130) {
        return creer_carte("razor");
    }

    return creer_carte("hell");
    

}
