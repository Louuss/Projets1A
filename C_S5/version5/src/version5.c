#include "../include/plateau.h"
#include "../include/grille.h"
#include "../include/liste_priorite.h"
#include "../include/definition.h"
#include <getopt.h>
#include <string.h>


int seed = 0;

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

void parse_opts(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                seed = atoi(optarg);
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-s seed] \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[]) {

    parse_opts(argc, argv);
    printf("Seed : %d\n", seed);

    srand(seed);

    creer_plateau(NB_JOUEUR);

    joueur j;
    ami a;

    int nb_joueur_vivant = get_nb_joueur_vivant();

    while (get_nb_joueur_vivant() > 1) {
        afficher_joueurs();
        afficher_grille();

        priorite list_joueur = recuperer_liste_debut();

        int i = 0;
        while (list_joueur != NULL && get_joueur_list(list_joueur) > 0) {

            bool est_ami = get_ami_bool(list_joueur);
            int num_joueur = recuperer_joueur_debut(list_joueur);

            //recuperation du joueur ou ami
            if (est_ami == false) {
                j = get_joueur_tab(num_joueur);

            } else {
                num_joueur = -num_joueur;
                a = get_ami_tab(num_joueur);
                if (a != NULL) {
                    j = get_joueur_tab(numero_joueur_ami(a));
                    if (j == NULL) {
                        ami_mort_plateau(num_joueur);
                    }
                }


            }
            //traitement du joueur ou ami
            if (est_ami == false) {
                if (j != NULL) {
                    
                    int r;
                    do {
                        r = rand_a_b(0, get_nb_joueur_vivant());
                    } while (get_numero(get_joueur(r)) == get_numero(j));

                    augmenter_idee(j);
                    deplacement_total(get_numero(j));

                    int choix_numero = choisir_carte(j);

                    if (choix_numero != FAIL) { //si une carte a été selectionnée 

                        carte c = get_carte_main(choix_numero, j);
                        traiter_carte(false, c, num_joueur, r, -1);

                        piocher(j, choix_numero);
                    }

                    if (est_mort(j)) {
                        quitte_partie(num_joueur);
                        classer_joueur(num_joueur);
                        nb_joueur_vivant--;

                        if (get_nb_joueur_vivant() > 1)
                            i--;

                    } else {
                        replacer_joueur(false, j, NULL);
                    }

                }
            } else {
                if (a != NULL) {
                    //On diminue la vie de l'ami
                    diminuer_vie(a);

                    int r;
                    do {
                        r = rand_a_b(0, get_nb_joueur_vivant());
                    } while (get_numero(get_joueur(r)) == get_numero(j));

                    //recuperer sa carte
                    carte c = recuperer_carte_ami(a);

                    if (get_cout(c) <= get_idee_ami(a)) {
                        //jouer sa carte
                        traiter_carte(true, c, num_joueur, r, numero_joueur_ami(a));
                        non_autoriser(get_numero_maitre(a));

                    } else {
                        augmenter_idee_ami(a);
                        autoriser(get_numero_maitre(a));
                    }

                    //Tue l'ami s'il est mort sinon il le replace
                    if (get_vie_ami(a) == 0) {
                        ami_mort(j, num_joueur);
                        ami_mort_plateau(num_joueur);
                        if (get_nb_ami(j) > 1)
                            i--;
                    } else {
                        replacer_joueur(true, NULL, a);
                    }
                }
                printf("\n");

            }

            i++;
        }

	supprimer_priorite(list_joueur); 
        faire_deplacement_simultanement();
	
        //tuer les joueurs meme s'il ne joue pas
        for (int i = 0; i < get_nb_joueur_vivant(); i++) {
            joueur j = get_joueur(i);
            int num_joueur = get_numero(j);
            if (est_mort(j)) {
                quitte_partie(num_joueur);
                classer_joueur(num_joueur);
                nb_joueur_vivant--;

                if (get_nb_joueur_vivant() > 1)
                    i--;
            }
        }
           
        
    }

    afficher_joueurs();

    if (get_nb_joueur_vivant() == 1) {

        int numero = get_numero(get_joueur(0));

        quitte_partie(numero);

        classer_joueur(numero);
    }

    afficher_resultat();

    supprimer_plateau();
}


