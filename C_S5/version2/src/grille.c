#include "../include/grille.h"
#include "../include/joueur.h"
#include "../include/plateau.h"
#include "../include/definition.h"
#include <stdio.h>
#include <stdlib.h>

static grille grille_dj;

struct position {
    int x;
    int y;
};

struct grille_de_jeu {
    bool** tab;
    int nb_joueur;
    struct position* tab_position_actuelle;
    struct position* tab_position_futur;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void creer_grille(int nb_joueur) {
    grille_dj = malloc(sizeof (struct grille_de_jeu));
    if (!grille_dj) {
        echec("grille_dj non créé: creer_grille()");
        return;
    }

    grille_dj->tab = calloc(TAILLE, sizeof (bool*));
    if (!grille_dj->tab) {
        echec("grille_dj->tab non créé: creer_grille()");
        return;
    }

    for (int i = 0; i < TAILLE; i++) {
        grille_dj->tab[i] = calloc(TAILLE, sizeof (bool));
        if (!grille_dj->tab[i]) {
            echec("grille_dj->tab[i] non créé: creer_grille()");
            return;
        }
        for (int j = 0; j < TAILLE; j++) {
            grille_dj->tab[i][j] = true;
        }

    }
    grille_dj->nb_joueur = nb_joueur;
    grille_dj->tab_position_actuelle = calloc(nb_joueur, sizeof (struct position));
    grille_dj->tab_position_futur = calloc(nb_joueur, sizeof (struct position));
}

bool est_libre(int x, int y) {
    return grille_dj->tab[x % TORIQUE][y % TORIQUE];
}

void remplir_grille(int x, int y, int numj) {
    grille_dj->tab[x % TORIQUE][y % TORIQUE] = false;
    grille_dj->tab_position_actuelle[numj].x = x % TORIQUE;
    grille_dj->tab_position_actuelle[numj].y = y % TORIQUE;
}

void supprimer_grille() {
    for (int i = 0; i < TAILLE; i++) {
        free(grille_dj->tab[i]);
    }
    free(grille_dj->tab);
    free(grille_dj->tab_position_actuelle);
    free(grille_dj->tab_position_futur);
    free(grille_dj);
}

int est_joueur(int x, int y) {

    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        if (grille_dj->tab_position_actuelle[i].x == x && grille_dj->tab_position_actuelle[i].y == y) {
            return i;
        }
    }

    return -1;
}

void afficher_grille() {

    for (int i = 0; i < TAILLE; i++) {
        printf(ANSI_COLOR_YELLOW"____"ANSI_COLOR_RESET);
    }

    int* couleur = malloc(TAILLE * sizeof (int));
    int indice = 0;
    int parcours_tab = 0;

    printf("\n");

    for (int i = 0; i < TAILLE; i++) {

        indice = 0;
        parcours_tab = 0;

        for (int k = 0; k < TAILLE; k++) {
            if (i != 0) {
                if (k == couleur[parcours_tab]) {
                    printf(ANSI_COLOR_YELLOW "|"CARAMEL"___" DEFAULT ANSI_COLOR_RESET);
                    parcours_tab++;
                } else {
                    printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
                }
                if (k == TAILLE - 1)
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }
        
        for(int i=0; i<TAILLE; i++){
            couleur[i] = -1;
        }
        
        if (i != 0)
            printf("\n");
        
        for (int j = 0; j < TAILLE; j++) {
            if (grille_dj->tab[i][j] == true) {
                printf(ANSI_COLOR_YELLOW"|   "ANSI_COLOR_RESET);
            } else {
                if (est_joueur(i, j) == -1) {
                    couleur[indice++] = j;
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET CARAMEL"   "DEFAULT);
                } else {

                    printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_BOLD"%d "ANSI_BOLD_OFF, est_joueur(i, j));

                }
            }

            if (j == TAILLE - 1) {
                printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }

        printf("\n");
    }
    parcours_tab = 0;

    for (int i = 0; i < TAILLE; i++) {
        if (i == couleur[parcours_tab]) {
            printf(ANSI_COLOR_YELLOW "|"CARAMEL"___" DEFAULT ANSI_COLOR_RESET);
            parcours_tab++;
        } else {
            printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
        }
        if (i == TAILLE - 1)
            printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
    }
    printf("\n");
    free(couleur); 
}

void creer_bloc(int x, int y) {
    if (est_libre(x + 1, y)) {
        grille_dj->tab[(x + 1) % TORIQUE][y] = false;

    } else if (est_libre(x - 1 + TORIQUE, y)) {
        grille_dj->tab[(x - 1 + TORIQUE) % TORIQUE][y] = false;

    } else if (est_libre(x, y + 1)) {
        grille_dj->tab[x][(y + 1) % TORIQUE] = false;

    } else if (est_libre(x, y - 1 + TORIQUE)) {
        grille_dj->tab[x][(y - 1 + TORIQUE) % TORIQUE] = false;
    }
}

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

static void deplacement_une_case(int numj) {

    int x = grille_dj->tab_position_futur[numj].x;
    int y = grille_dj->tab_position_futur[numj].y;

    int i = rand_a_b(1, 4);

    switch (i) {
        case 1:
            if (est_libre(x + 1, y)) {
                grille_dj->tab_position_futur[numj].x = (x + 1) % TORIQUE;
                grille_dj->tab_position_futur[numj].y = y;
                return;

            }

        case 2:
            if (est_libre((x - 1) + TORIQUE, y)) {
                grille_dj->tab_position_futur[numj].x = (x - 1 + TORIQUE) % TORIQUE;
                grille_dj->tab_position_futur[numj].y = y;
                return;

            }

        case 3:
            if (est_libre(x, y + 1)) {
                grille_dj->tab_position_futur[numj].x = x;
                grille_dj->tab_position_futur[numj].y = (y + 1) % TORIQUE;
                return;
            }

        case 4:
            if (est_libre(x, (y - 1) + TORIQUE)) {
                grille_dj->tab_position_futur[numj].x = x;
                grille_dj->tab_position_futur[numj].y = (y - 1 + TORIQUE) % TORIQUE;
                return;
            }

    }
}

void deplacement_total(int numj) {
    int i = rand_a_b(0, NB_MOUV);

    for (; i < NB_MOUV; i++) {
        deplacement_une_case(numj);
    }
}

void faire_deplacement_simultanement() {

    int tab_joueur_pas_deplacement[grille_dj->nb_joueur * 2];
    int indice = 0;


    //verifier les colisions
    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        for (int j = i + 1; j < grille_dj->nb_joueur; j++) {
            if (grille_dj->tab_position_futur[i].x == grille_dj->tab_position_futur[j].x &&
                    grille_dj->tab_position_futur[i].y == grille_dj->tab_position_futur[j].y) {
                tab_joueur_pas_deplacement[indice++] = i;
                tab_joueur_pas_deplacement[indice++] = j;
            }
        }
    }

    //dire au joueur avec colision de ne pas bouger
    for (int i = 0; i < indice; i++) {
        grille_dj->tab_position_futur[tab_joueur_pas_deplacement[i]].x = grille_dj->tab_position_actuelle[tab_joueur_pas_deplacement[i]].x;
        grille_dj->tab_position_futur[tab_joueur_pas_deplacement[i]].y = grille_dj->tab_position_actuelle[tab_joueur_pas_deplacement[i]].y;
    }

    //joueur tout les deplacements des personnes
    for (int i = 0; i < grille_dj->nb_joueur; i++) {
        grille_dj->tab[ grille_dj->tab_position_actuelle[i].x][ grille_dj->tab_position_actuelle[i].y] = true;
        remplir_grille(grille_dj->tab_position_futur[i].x, grille_dj->tab_position_futur[i].y, i);
        if (i < get_nb_joueur_vivant() && !est_mort(get_joueur(i))) {
            set_position_x(get_joueur(i), grille_dj->tab_position_futur[i].x);
            set_position_y(get_joueur(i), grille_dj->tab_position_futur[i].y);
        }

    }

}

bool est_encercle(int x, int y) {
    if (!est_libre(x + 1, y) && !est_libre(x - 1 + TORIQUE, y) && !est_libre(x, y + 1) && !est_libre(x, y - 1 + TORIQUE)) {
        return true;
    }
    return false;
}

void afficher_position() {
    for (int i = 0; i < grille_dj->nb_joueur; i++)
        printf("Le joueur %d X=%d Y=%d\n", i, grille_dj->tab_position_actuelle[i].x, grille_dj->tab_position_actuelle[i].y);
}
