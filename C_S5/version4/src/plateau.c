#include "../include/plateau.h"
#include <string.h>
#include <time.h>
#include <limits.h>
#include "../include/definition.h"

static plateau_de_jeu plateau;

struct plateau_de_jeu {
    joueur* tab_joueur;
    int nb_joueur;
    int nb_joueur_vivant;
    int* classement_joueur;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void creer_plateau(int nb_joueur) {

    if (nb_joueur == 0) {
        echec("nombre de joueur NULL: creer_plateau()");
        return;
    }

    creer_grille(nb_joueur);

    plateau = malloc(sizeof (struct plateau_de_jeu));
    if (!plateau) {
        echec("plateau non créé: creer_plateau()");
        return;
    }


    plateau->tab_joueur = malloc(nb_joueur * sizeof (joueur));
    if (!plateau->tab_joueur) {
        echec("tableau de joueur non créé: creer_plateau()");
        return;
    }

    for (int i = 0; i < nb_joueur; i++) {
        plateau->tab_joueur[i] = creer_joueur(i);
    }

    plateau->nb_joueur = nb_joueur;
    plateau->nb_joueur_vivant = nb_joueur;
    plateau->classement_joueur = malloc(nb_joueur * sizeof (int));
    if (!plateau->classement_joueur) {
        echec("tableau de classement non créé: creer_plateau()");
        return;
    }

}

void traiter_carte(bool ami, carte c, int numero_j, int numero_adversaire, int numero_ami) { 
    if (c == NULL) {
        echec("carte c : traiter_carte()");
        return;
    }
        
    pointeur_fonction p = get_application_carte(c);
    (*p)(numero_j, numero_adversaire, ami, numero_ami);
}

void classer_joueur(int numero) {
    //on classe le numero du joueur a la derniere case libre
    plateau->classement_joueur[plateau->nb_joueur_vivant ] = numero;
}

void afficher_resultat() {

    if (plateau == NULL) {
        echec("plateau NULL: afficher_resultat()");
        return;
    }

    printf("-----------------------------FIN DU JEU-----------------------------\n");
    for (int i = 0; i < plateau->nb_joueur; i++) {
        printf("Le joueur numero %d est %deme\n", plateau->classement_joueur[i], i + 1);
    }
}

void afficher_joueurs() {

    if (plateau == NULL) {
        echec("plateau NULL: afficher_joueurs()");
        return;
    }
    printf("___________________________________________________________________\n");
    printf("\n");
    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        if ((plateau->tab_joueur[i]) != NULL) {
            printf(ANSI_BOLD"JOUEUR %d :"ANSI_BOLD_OFF"\n", get_numero(plateau->tab_joueur[i]));
            printf("    -Energie : %d\n", get_energie(plateau->tab_joueur[i]));
            printf("    -Idee : %d\n", get_idee(plateau->tab_joueur[i]));
            printf("    -Gain : %d\n", get_gain(plateau->tab_joueur[i]));
            afficher_main(plateau->tab_joueur[i]);
        }
    }
}

void quitte_partie(int numj) {

    //si j'ai plusieurs joueurs
    if (plateau->nb_joueur_vivant - 1 != 0) {
        bool b = false;
        joueur tmp;

        for (int i = 0; i < plateau->nb_joueur_vivant - 1; i++) {
            if (get_numero(plateau->tab_joueur[i]) == numj) {
                b = true;
                tmp = plateau->tab_joueur[i];
            }
            if (b == true)
                plateau->tab_joueur[i] = plateau->tab_joueur[i + 1];
        }


        if (b != false) { //Si on a trouvé le joueur
            supprimer_joueur(tmp);
        } else { //Sinon notre joueur est dernier
            supprimer_joueur(plateau->tab_joueur[plateau->nb_joueur_vivant - 1]);
        }
        plateau->nb_joueur_vivant--;

    } else { // Sinon je n'ai qu'un joueur 
        supprimer_joueur(plateau->tab_joueur[0]);
        plateau->nb_joueur_vivant--;

    }

}

int get_nb_joueur_vivant() {
    return plateau->nb_joueur_vivant;
}

joueur get_joueur(int i) {
    return plateau->tab_joueur[i];
}

int get_nb_joueur() {
    return plateau->nb_joueur;
}

void supprimer_plateau() {

    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        supprimer_joueur(plateau->tab_joueur[i]);
    }
    free(plateau->tab_joueur);

    free(plateau->classement_joueur);
    free(plateau);

    supprimer_grille();
}

void faire_jouer_ami(joueur j, joueur adversaire, int m, int ad) {
    if (get_nb_ami(j) != 0) {
        for (int z = 0; z < get_nb_ami(j); z++) {
            //recuperer l'ami

            ami a = get_ami(z, j);
            // recuperer son adversaire DIFFICILE SI CE DERNIER EST MORT
            //adversaire = get_joueur(get_numero_cible(a));

            //recuperer sa carte
            carte c = recuperer_carte_ami(a);

            if (get_cout(c) <= get_idee_ami(a)) {
                //jouer sa carte
                traiter_carte(true,c, m, ad, z);
                non_autoriser(get_numero_maitre(a));
            } else {
                augmenter_idee_ami(a);
                autoriser(get_numero_maitre(a));
            }

            diminuer_vie(a);

            if (get_vie_ami(a) == 0) {
                ami_mort(j, z);
                if (get_nb_ami(j) > 1)
                    z--;
            }

        }
    }
}

