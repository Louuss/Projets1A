#include "../include/joueur.h"
#include "../include/memento.h"
#include "../include/definition.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>



struct joueur {
    int numero_joueur;
    int energie;
    int idee;
    int gain;
    int n_carte;
    carte *main;
    memento_list memento_joueur;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

// on créé un joueur et on initialise tout ses champs
joueur creer_joueur(int numero) {
    joueur j = calloc(1,sizeof (struct joueur));
    if (!j) {
        echec("joueur non créé: creer_joueur()");
        return NULL;
    }

    j->numero_joueur = numero;
    j->energie = 50;
    j->idee = 0;
    j->gain = 1;
    j->n_carte = 0;
    
    j->main = calloc(NB_CARTE_BEGIN, sizeof (carte));
    if (!j->main) {
        echec("main non créé: creer_joueur()");
    }
    
    j->memento_joueur = creer_memento();
    j->memento_joueur = remplir_memento(j->memento_joueur);

    

    // sert a remplir la main 
    for (int i = 0; i < NB_CARTE_BEGIN; i++) {
        piocher(j, i);
    }

    return j;

}

// sert à liberer l'espace quand on a plus besoin du joueur 
void supprimer_joueur(joueur j){
    if (j==NULL){
        return;
    }
    for(int i=0; i<NB_CARTE_BEGIN;i++){
        supprimer_carte(j->main[i]);
    }
    free(j->main);
    
    supprimer_tout_memento(j->memento_joueur);
    free(j->memento_joueur);
    free(j);
}

// cette fonction selectionne une carte dans la main du joueur 
// si le joueur n'a pas assez d'idées pour jouer la carte, on
// cherche parmi les cartes de la main une carte possible 
// si rien n'est possible alors on retourne -1 et le joueur ne jouera pas 
// lors de ce tour 
int choisir_carte(joueur j) {

    if (j == NULL) {
        echec("joueur NULL: choisir_carte()");
        return EXIT_FAILURE;
    }

    int alea = rand_a_b(0, j->n_carte);
    int alea2 = 0;

    for (alea2 = (alea2 + 1) % NB_CARTE_BEGIN; get_cout(j->main[alea2]) > get_idee(j);) {

        if ((get_cout(j->main[alea2]) > get_idee(j)) && (alea2 == alea)) {
            return FAIL;
        }

        if (get_cout(j->main[alea2]) < get_idee(j)) {
            break;
        }

        alea2 = (alea2 + 1) % NB_CARTE_BEGIN;

    }
    j->n_carte--;
    j->memento_joueur = ajouter_memento_fin(j->memento_joueur, j->main[alea2]);

    return alea2;
}

// cette fonction sert a afficher la main d'un joueur
void afficher_main(joueur j) {
    
    
        if (j == NULL) {
        echec("joueur NULL: afficher_main()");
        return;
    }

    
    //Affichage haut de carte
    int i = 0;
    while (i < NB_CARTE_BEGIN) {
        printf(" __________   ");
        i++;
    }
    printf("\n");
    
    //Affichage nom de carte
    i = 0;
    while (i < NB_CARTE_BEGIN) {
        if (strcmp(get_nom(j->main[i]), "panacea") == 0) {
            printf("|"ANSI_COLOR_RED ANSI_BOLD"  %s "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(j->main[i]));
        } else if (strcmp(get_nom(j->main[i]), "hell") == 0) {
            printf("|"ANSI_COLOR_RED ANSI_BOLD"   %s   "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(j->main[i]));
        } else {
            printf("|"ANSI_COLOR_RED ANSI_BOLD"  %s"ANSI_COLOR_RESET ANSI_BOLD_OFF"   |  ", get_nom(j->main[i]));
        }
        i++;
    }
    printf("\n");
    
    //Affichage espace
    i = 0;
    while (i < NB_CARTE_BEGIN) {
        printf("|          |  ");
        i++;
    }
    printf("\n");
    
    //Affichage cout de carte
    i = 0;
    while (i < NB_CARTE_BEGIN) {
        if (get_cout(j->main[i]) < 10) {
            printf("|"ANSI_COLOR_YELLOW"         %d"ANSI_COLOR_RESET"|  ", get_cout(j->main[i]));
        } else if (get_cout(j->main[i]) == 100) {
            printf("|"ANSI_COLOR_YELLOW"       %d"ANSI_COLOR_RESET"|  ", get_cout(j->main[i]));
        } else {
            printf("|"ANSI_COLOR_YELLOW"        %d"ANSI_COLOR_RESET"|  ", get_cout(j->main[i]));
        }
        i++;
    }
    printf("\n");
    
    //Affichage rarete de carte
    i = 0;
    while (i < NB_CARTE_BEGIN) {
        if (get_rarete(j->main[i]) == 1) {
            printf("|"ANSI_COLOR_YELLOW"     %d/131"ANSI_COLOR_RESET"|  ", get_rarete(j->main[i]));
        } else {
            printf("|"ANSI_COLOR_YELLOW"    %d/131"ANSI_COLOR_RESET"|  ", get_rarete(j->main[i]));
        }
        i++;
    }
    printf("\n");
    
    //Affichage bas de carte
    i = 0;
    while (i < NB_CARTE_BEGIN) {
        printf("|__________|  ");
        i++;
    }
    printf("\n\n\n");
}
//cette fonction defausse la main d'un joueur j et lui fait piocher une nouvelle
// main
void defausser(joueur j) {

    for (int i = 0; i < j->n_carte; i++) {
        j->memento_joueur = ajouter_memento_fin(j->memento_joueur, j->main[i]);
    }
    j->n_carte = 0;
    for (int i = 0; i < NB_CARTE_BEGIN; i++) {
        piocher(j, i);
    }

}

// cette fonction ajoute une carte dans la main d'un joueur j, à la position i
// elle la prend au debut du memento 
// elle augmente aussi le nombre de carte du joueur 
void piocher(joueur j, int i) {

    if (j == NULL) {
        echec("joueur NULL: piocher()");
        return;
    }

    j->main[i] = copie_carte(get_carte(get_premier(j->memento_joueur)));
    j->memento_joueur = supprimer_memento_debut(j->memento_joueur);
    j->n_carte++;
}

// augmente les idées du joueur j par son gain 
void augmenter_idee(joueur j) {

    if (j == NULL) {
        echec("joueur NULL: augmenter_idee()");
        return;
    }

    j->idee += j->gain;
}

int get_numero(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_numero()");
        return EXIT_FAILURE;
    }

    return j->numero_joueur;
}

int get_idee(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_idee()");
        return EXIT_FAILURE;
    }

    return j->idee;
}

int get_gain(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_gain()");
        return EXIT_FAILURE;
    }

    return j->gain;
}

int get_nb_carte(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_nb_carte()");
        return EXIT_FAILURE;
    }

    return j->n_carte;
}

carte get_carte_main(int i, joueur j) {
    return j->main[i];
}

int get_energie(joueur j) {

    if (j == NULL) {
        echec("Joueur NULL: get_energie()");
        return EXIT_FAILURE;
    }

    return j->energie;
}

void set_numero(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: get_numero()");
        return;
    }

    j->numero_joueur = a;
}

void set_energie(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: set_energie()");
        return;
    }

    j->energie = a;
}

void set_idee(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: set_idee()");
        return;
    }

    j->idee = a;
}

void set_gain(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: set_gain()");
        return;
    }

    j->gain = a;
}

void set_nb_carte(joueur j, int a) {

    if (j == NULL) {
        echec("Joueur NULL: set_nb_carte()");
        return;
    }

    j->n_carte = a;
}

// met la carte c a la position i dans la main du joueur j 
void set_carte_main(int i, joueur j, carte c) {
    
    if(j == NULL || c == NULL)
        return;
    
    set_nom(j->main[i],get_nom(c));
    set_cout(j->main[i],get_cout(c));
    set_rarete(j->main[i],get_rarete(c));
    
    
}

