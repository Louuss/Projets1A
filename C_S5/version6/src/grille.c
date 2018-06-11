#include "../include/grille.h"
#include "../include/joueur.h"
#include "../include/plateau.h"
#include "../include/definition.h"
#include "../include/ami.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static grille grille_dj;

struct grille_de_jeu {
    bool** tab;
    int nb_joueur;
    int nb_ami;
    struct position* tab_position_ami;
    int* numero_ennemi;
    bool* autorisation;
    struct position* tab_position_actuelle;
    struct position* tab_position_futur;
    struct position droma_pos;
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
    grille_dj->nb_ami = 0;
    grille_dj->tab_position_ami = calloc(NB_AMI, sizeof (struct position));
    grille_dj->numero_ennemi = calloc(NB_AMI, sizeof (int));
    grille_dj->autorisation = calloc(NB_AMI, sizeof (bool));

    grille_dj->tab_position_actuelle = calloc(nb_joueur, sizeof (struct position));
    grille_dj->tab_position_futur = calloc(nb_joueur, sizeof (struct position));
}

void remplir_grille_droma(int x, int y) {
    grille_dj->tab[x % TORIQUE][y % TORIQUE] = false;
    grille_dj->tab[(x + 1) % TORIQUE][y % TORIQUE] = false;
    grille_dj->tab[x % TORIQUE][(y + 1) % TORIQUE] = false;
    grille_dj->tab[(x - 1 + TORIQUE) % TORIQUE][y % TORIQUE] = false;
    grille_dj->tab[x % TORIQUE][(y - 1 + TORIQUE) % TORIQUE] = false;

    grille_dj->droma_pos.x = x;
    grille_dj->droma_pos.y = y;
}

bool est_droma(int x, int y) {
    int droma_x = grille_dj->droma_pos.x;
    int droma_y = grille_dj->droma_pos.y;

    if (droma_x == x && droma_y == y) {
        return true;

    } else if ((droma_x + 1 % TORIQUE) == x && droma_y == y) {
        return true;

    } else if ((droma_y + 1 % TORIQUE) == y && droma_x == x) {
        return true;

    } else if (((droma_x - 1 + TORIQUE) % TORIQUE) == x && droma_y == y) {
        return true;

    } else if (((droma_y - 1 + TORIQUE) % TORIQUE) == y && droma_x == x) {
        return true;

    }

    return false;
}

void augmenter_nb_ami() {
    grille_dj->nb_ami++;
}

int nb_ami_g() {
    return grille_dj->nb_ami;
}

bool est_libre(int x, int y) {
    return grille_dj->tab[x % TORIQUE][y % TORIQUE];
}

void remplir_grille(int x, int y, int numj, bool ami) {
    grille_dj->tab[x][y] = false;

    if (ami == true) {
        grille_dj->tab_position_ami[grille_dj->nb_ami].x = x;
        grille_dj->tab_position_ami[grille_dj->nb_ami].y = y;
        grille_dj->numero_ennemi[grille_dj->nb_ami] = numj;
        grille_dj->autorisation[grille_dj->nb_ami] = false;
    } else {
        grille_dj->tab_position_actuelle[numj].x = x;
        grille_dj->tab_position_actuelle[numj].y = y;
    }

}

void supprimer_grille() {
    for (int i = 0; i < TAILLE; i++) {
        free(grille_dj->tab[i]);
    }
    free(grille_dj->tab);
    free(grille_dj->tab_position_actuelle);
    free(grille_dj->tab_position_futur);
    free(grille_dj->tab_position_ami);
    free(grille_dj->numero_ennemi);
    free(grille_dj->autorisation);
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

int est_ami(int x, int y) {

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        if (grille_dj->tab_position_ami[i].x == x && grille_dj->tab_position_ami[i].y == y) {
            return i;
        }
    }

    return -1;
}

void afficher_grille() {

    for (int i = 0; i < TAILLE; i++) {
        printf(ANSI_COLOR_YELLOW"____"ANSI_COLOR_RESET);
    }

    int* couleur1 = malloc(TAILLE * sizeof (int));
    int indice1 = 0;
    int parcours_tab1 = 0;

    int* couleur2 = malloc(TAILLE * sizeof (int));
    int indice2 = 0;
    int parcours_tab2 = 0;

    printf("\n");
    for (int i = 0; i < TAILLE; i++) {

        indice1 = 0;
        parcours_tab1 = 0;

        indice2 = 0;
        parcours_tab2 = 0;


        for (int k = 0; k < TAILLE; k++) {
            if (i != 0) {
                if (k == couleur1[parcours_tab1]) {
                    printf(ANSI_COLOR_YELLOW "|"CARAMEL"___" DEFAULT ANSI_COLOR_RESET);
                    parcours_tab1++;

                } else if (k == couleur2[parcours_tab2]) {
                    printf(ANSI_COLOR_YELLOW "|"DROMA"___" DEFAULT ANSI_COLOR_RESET);
                    parcours_tab2++;
                } else {
                    printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
                }

                if (k == TAILLE - 1)
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }

        for (int i = 0; i < TAILLE; i++) {
            couleur1[i] = -1;
            couleur2[i] = -1;
        }

        if (i != 0)
            printf("\n");
        for (int j = 0; j < TAILLE; j++) {
            if (grille_dj->tab[i][j] == true) {
                printf(ANSI_COLOR_YELLOW"|   "ANSI_COLOR_RESET);
            } else {
                if (est_droma(i, j)) {
                    couleur2[indice2++] = j;
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET DROMA"   "DEFAULT);

                } else if (est_joueur(i, j) == -1 && est_ami(i, j) == -1) {
                    couleur1[indice1++] = j;
                    printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET CARAMEL"   "DEFAULT);
                } else {
                    if (est_joueur(i, j) == -1) {
                        if (est_ami(i, j) < 10) {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_COLOR_RED"%d "ANSI_COLOR_RESET, est_ami(i, j));
                        } else {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_COLOR_RED"%d"ANSI_COLOR_RESET, est_ami(i, j));
                        }
                    } else {
                        if (est_joueur(i, j) < 10) {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_BOLD"%d "ANSI_BOLD_OFF, est_joueur(i, j));
                        } else {
                            printf(ANSI_COLOR_YELLOW"| "ANSI_COLOR_RESET ANSI_BOLD"%d"ANSI_BOLD_OFF, est_joueur(i, j));
                        }
                    }

                }
            }

            if (j == TAILLE - 1) {
                printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
            }
        }

        printf("\n");
    }

    parcours_tab1 = 0;
    parcours_tab2 = 0;

    for (int i = 0; i < TAILLE; i++) {
        if (i == couleur1[parcours_tab1]) {
            printf(ANSI_COLOR_YELLOW "|"CARAMEL"___" DEFAULT ANSI_COLOR_RESET);
            parcours_tab1++;

        } else if (i == couleur2[parcours_tab2]) {
            printf(ANSI_COLOR_YELLOW "|"DROMA"___" DEFAULT ANSI_COLOR_RESET);
            parcours_tab2++;

        } else {
            printf(ANSI_COLOR_YELLOW"|___"ANSI_COLOR_RESET);
        }
        if (i == TAILLE - 1)
            printf(ANSI_COLOR_YELLOW"|"ANSI_COLOR_RESET);
    }
    printf("\n");

    free(couleur1);
    free(couleur2);

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
    int i = rand_a_b(0, 4);

    int prio = get_cout_action(get_joueur_tab(numj));
    for (; i < 5; i++) {
        set_priorite(get_joueur_tab(numj), get_priorite(get_joueur_tab(numj)) + prio);
        deplacement_une_case(numj);
    }
}

void deplacement_une_case_ami(struct position *p, struct position ad) {


    grille_dj->tab[p->x][p->y] = true;




    int passer_normal_x = abs(p->x - ad.x);
    int passer_normal_y = abs(p->y - ad.y);
    int passer_par_thorique_x = TORIQUE - passer_normal_x;
    int passer_par_thorique_y = TORIQUE - passer_normal_y;

    bool thorique_x = false;
    bool thorique_y = false;

    if (passer_par_thorique_x < passer_normal_x)
        thorique_x = true;

    if (passer_par_thorique_y < passer_normal_y)
        thorique_y = true;


    for (int k = 0; k < 4; k++) {
        if (est_libre(p->x + 1, p->y) && (ad.x > p->x) && !thorique_x) {
            p->x = (p->x + 1) % TORIQUE;
            return;

        } else if (est_libre((p->x - 1) + TORIQUE, p->y) && thorique_x) {
            p->x = (p->x - 1 + TORIQUE) % TORIQUE;
            return;

        } else if (est_libre((p->x - 1) + TORIQUE, p->y) && (ad.x < p->x) && !thorique_x) {
            p->x = (p->x - 1 + TORIQUE) % TORIQUE;
            return;

        } else if (est_libre(p->x + 1, p->y) && thorique_x) {
            p->x = (p->x + 1) % TORIQUE;
            return;



        } else if (est_libre(p->x, p->y + 1) && (ad.y > p->y) && !thorique_y) {
            p->y = (p->y + 1) % TORIQUE;
            return;

        } else if (est_libre(p->x, (p->y - 1) + TORIQUE) && thorique_y) {
            p->y = (p->y - 1 + TORIQUE) % TORIQUE;
            return;

        } else if (est_libre(p->x, (p->y - 1) + TORIQUE) && (ad.y < p->y) && !thorique_y) {
            p->y = (p->y - 1 + TORIQUE) % TORIQUE;
            return;

        } else if (est_libre(p->x, p->y + 1)) {
            p->y = (p->y + 1) % TORIQUE;
            return;
        }
    }
}

void deplacement_ami(struct position *p, int i, struct position ad) {

    if (get_ami_tab(i) != NULL) {
        int j = rand_a_b(0, 2);

        int prio = get_cout_action_ami(get_ami_tab(i));
        for (; j < 2; j++) {
            augmenter_cout_action_ami(get_ami_tab(i), prio);
            deplacement_une_case_ami(p, ad);
        }

        remplir_grille(p->x, p->y, i, true);
    }
}

bool est_autorise(int i) {
    return grille_dj->autorisation[i];
}

void init_autorisation() {
    for (int i = 0; i < grille_dj->nb_ami; i++) {
        grille_dj->autorisation[i] = false;
    }
}

void afficher_position_ami() {

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        printf("L' ami %d attaque %d --------   X=%d Y=%d\n", i, 
                grille_dj->numero_ennemi[i],
                grille_dj->tab_position_ami[i].x, 
                grille_dj->tab_position_ami[i].y);
    }
    printf(" \n");
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
        remplir_grille(grille_dj->tab_position_futur[i].x, grille_dj->tab_position_futur[i].y, i, false);
        if (i < get_nb_joueur_vivant() && !est_mort(get_joueur(i))) {
            set_position_x(get_joueur(i), grille_dj->tab_position_futur[i].x);
            set_position_y(get_joueur(i), grille_dj->tab_position_futur[i].y);
        }

    }

    for (int i = 0; i < grille_dj->nb_ami; i++) {
        if (est_autorise(i) == true) {

            struct position adversaire = grille_dj->tab_position_actuelle[grille_dj->numero_ennemi[i]];
            deplacement_ami(&grille_dj->tab_position_ami[i], i, adversaire);

        }
    }

    init_autorisation();

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

void autoriser(int i) {
    grille_dj->autorisation[i] = true;
}

void non_autoriser(int i) {
    grille_dj->autorisation[i] = false;
}
