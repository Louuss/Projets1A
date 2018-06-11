#include "../include/plateau.h"
#include "../include/definition.h"
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>


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

// créer le plateau et les joueurs en fonction du nombre passe
// en parametre 
void creer_plateau(int nb_joueur) {

    if (nb_joueur == 0) {
        echec("nombre de joueur NULL: creer_plateau()");
        return;
    }

    plateau = calloc(1, sizeof (struct plateau_de_jeu));
    if (!plateau) {
        echec("plateau non créé: creer_plateau()");
        return;
    }


    plateau->tab_joueur = calloc(nb_joueur, sizeof (joueur));
    if (!plateau->tab_joueur) {
        echec("tableau de joueur non créé: creer_plateau()");
        return;
    }

    for (int i = 0; i < nb_joueur; i++) {
        plateau->tab_joueur[i] = creer_joueur(i);
    }

    plateau->nb_joueur = nb_joueur;
    plateau->nb_joueur_vivant = nb_joueur;
    plateau->classement_joueur = calloc(nb_joueur, sizeof (int));
    if (!plateau->classement_joueur) {
        echec("tableau de classement non créé: creer_plateau()");
        return;
    }

}
// supprime le plateau et tous les joueurs (et toutes les carte de tous 
// les joueurs 
void supprimer_plateau() {

    for (int i = 0; i < plateau->nb_joueur_vivant; i++) {
        supprimer_joueur(plateau->tab_joueur[i]);
    }
    free(plateau->tab_joueur);

    free(plateau->classement_joueur);
    free(plateau);


}

// cette fonction traite les carte : i correspond a la position dans la main
// du joueur moi. On regarde a quelle carte cela correspond et traite la 
// carte correspondante. pour savoir quelle carte a ete choisi, on compare
// son nom avec le nom des cartes 
void traiter_carte(int i, joueur moi, joueur adversaire) {

    if (moi == NULL || adversaire == NULL) {
        echec("moi ou adversaire NULL : traiter_carte()");
        return;
    }

    if (strcmp(get_nom(get_carte_main(i, moi)), "think") == 0) {
        set_gain(moi, get_gain(moi) + 1);

    } else if (strcmp(get_nom(get_carte_main(i, moi)), "steal") == 0) {
        set_gain(moi, get_gain(moi) + 1);
        if (get_gain(adversaire) != 1)
            set_gain(adversaire, get_gain(adversaire) - 1);

    } else if (strcmp(get_nom(get_carte_main(i, moi)), "panacea") == 0) {
        set_energie(moi, get_energie(moi) + 10);

    } else if (strcmp(get_nom(get_carte_main(i, moi)), "razor") == 0) {
        set_energie(adversaire, get_energie(adversaire) - 10);

    } else if (strcmp(get_nom(get_carte_main(i, moi)), "hell") == 0) {
        set_energie(adversaire, get_energie(adversaire) - INT_MAX);
    }

    set_idee(moi, get_idee(moi) - get_cout(get_carte_main(i, moi)));


}
// cette fontion ajoute le numero du joueur au tableau de classement
void classer_joueur(int numero) {
    //on classe le numero du joueur a la derniere case libre
    plateau->classement_joueur[plateau->nb_joueur_vivant ] = numero;
}
// sert a afficher le resultat
void afficher_resultat(int tour) {

    if (plateau == NULL) {
        echec("plateau NULL: afficher_resultat()");
        return;
    }

    printf("-----------------------------FIN DU JEU-----------------------------\n");
    int i;
    if(tour<1000){
      i=0;
    }else{
      i=2;
    }
    for (; i < plateau->nb_joueur; i++) {
        printf("Le joueur numero %d est %deme\n", plateau->classement_joueur[i], i + 1);
    
    }
}
// affiche les joueurs encore vivants
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
// sert a faire quitter la partie à un joueur
// il ne pourra plus jouer ou etre pris pour cible par la suite 
void quitte_partie(int numj) {

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

        if (b != false){ //Si on a trouvé le joueur
	  supprimer_joueur(tmp);
	}else{           //Sinon notre joueur est dernier
	  supprimer_joueur( plateau->tab_joueur[plateau->nb_joueur_vivant - 1]);
	}
        plateau->nb_joueur_vivant--;
       
    }else{
        
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
// sert à gérer le cas de l'égalite au bout d'un certain nombre de tour
// pour eviter les boucles infinis 
void classe_joueur_egalite(int j1, int j2){

}
