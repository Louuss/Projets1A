#include "../include/plateau.h"
#include "../include/definition.h"
#include "../include/liste_priorite.h"
#include "../include/dromadulaire.h"
#include <string.h>
#include <time.h>
#include <limits.h>

static plateau_de_jeu plateau;

struct plateau_de_jeu {
    joueur* tab_joueur;
    ami* tab_ami;
    int nb_joueur;
    int nb_ami;
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
    creer_dromadulaire();

    creer_liste_prio();

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
        replacer_joueur(false, plateau->tab_joueur[i], NULL);
    }

    plateau->tab_ami = calloc(NB_AMI, sizeof (ami));
    if (!plateau->tab_ami) {
        echec("tableau d'ami non créé: creer_plateau()");
        return;
    }


    plateau->nb_joueur = nb_joueur;
    plateau->nb_ami = 0;
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
    
    if (ami == false){
        set_priorite(get_joueur_tab(numero_j), get_priorite(get_joueur_tab(numero_j)) + get_cout_action(get_joueur_tab(numero_j)));
    }else{
        augmenter_priorite_ami(get_ami_tab(numero_j), get_cout_action_ami(get_ami_tab(numero_j)));
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
        if (plateau->classement_joueur[i] >= 10)
            printf("Le joueur numero %d est %deme\n", plateau->classement_joueur[i], i + 1);
        else
            printf("Le joueur numero %d  est %deme\n", plateau->classement_joueur[i], i + 1);
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
            printf("    -Temps : %d\n", get_priorite(plateau->tab_joueur[i]));
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

ami get_ami_indice(int i){
    return plateau->tab_ami[i];
}

int get_nb_joueur() {
    return plateau->nb_joueur;
}

joueur get_joueur_tab(int num) {
    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        if (get_numero(plateau->tab_joueur[i]) == num)
            return plateau->tab_joueur[i];
    }
    
    printf("LE JOUERU N4EXISTE PAS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    return NULL;
}

ami get_ami_tab(int num) {
    for (int i = 0; i < plateau->nb_ami; i++) {
        if (plateau->tab_ami[i] != NULL) {
            if (get_numero_maitre(plateau->tab_ami[i]) == num)
                return plateau->tab_ami[i];
        }
    }

    return NULL;
}

void supprimer_plateau() {

    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        supprimer_joueur(plateau->tab_joueur[i]);
    }
    free(plateau->tab_joueur);

    free(plateau->tab_ami);

    free(plateau->classement_joueur);
    free(plateau);

    supprimer_grille();
}

void ami_mort_plateau(int numj) {

    //si j'ai plusieurs joueurs
    if (plateau->nb_ami - 1 != 0) {
        bool b = false;
        ami tmp;

        for (int i = 0; i < plateau->nb_ami - 1; i++) {
            if (i == numj) {
                b = true;
                tmp = plateau->tab_ami[i];
            }
            if (b == true)
                plateau->tab_ami[i] = plateau->tab_ami[i + 1];
        }
    }

    plateau->nb_ami--;

}

void set_ami_plateau(int i, ami a) {
    //TODO
    plateau->tab_ami[i] = a;
}

void augmenter_nb_ami_plateau() {
    plateau->nb_ami++;
}

int get_nb_ami_plateau() {
    return plateau->nb_ami;
}

void afficher_tab_ami_plateau() {
    for (int i = 0; i < plateau->nb_ami; i++) {
        printf("case[%d] = ami %d \n", i, get_numero_maitre(plateau->tab_ami[i]));
    }
}

void set_nb_joueur_vivant() {
    plateau->nb_joueur_vivant--;
}

