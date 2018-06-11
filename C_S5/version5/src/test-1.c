#include "../include/plateau.h"
#include "../include/memento.h"
#include "../include/grille.h"
#include "../include/ami.h"
#include "../include/definition.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

bool test_equality_int(int expected, int value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

bool test_equality_bool(bool expected, bool value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

void test_failure_traiter_carte(carte i) {
    traiter_carte(false,i, 0,0,0);
}

void test_failure_joueur(joueur j, int i) {
    afficher_main(j);
    afficher_joueurs();
    choisir_carte(j);
    piocher(j, i);
    augmenter_idee(j);
}

void test_failure_plateau(plateau_de_jeu pdj) {
    afficher_resultat();
}

bool test_rand_a_b() {
    bool result = true;

    int a = 0;
    int b = 10;
    int r = rand_a_b(a, b);

    result = result && test_equality_bool(true, r >= a, "rand_a_b() >= a");
    result = result && test_equality_bool(true, r <= b, "rand_a_b() <= b");

    return result;
}

bool test_creer_carte() {
    bool result = true;

    carte c1 = creer_carte("think");
    result = result && test_equality_int(5, get_cout(c1), "think get_cout");
    result = result && test_equality_int(20, get_rarete(c1), "think get_rarete");

    carte c2 = creer_carte("steal");
    result = result && test_equality_int(10, get_cout(c2), "steal get_cout");
    result = result && test_equality_int(10, get_rarete(c2), "steal get_rarete");

    carte c3 = creer_carte("panacea");
    result = result && test_equality_int(2, get_cout(c3), "panacea get_cout");
    result = result && test_equality_int(50, get_rarete(c3), "panacea get_rarete");

    carte c4 = creer_carte("razor");
    result = result && test_equality_int(2, get_cout(c4), "razor get_cout");
    result = result && test_equality_int(50, get_rarete(c4), "razor get_rarete");

    carte c5 = creer_carte("hell");
    result = result && test_equality_int(100, get_cout(c5), "hell get_cout");
    result = result && test_equality_int(1, get_rarete(c5), "hell get_rarete");

    supprimer_carte(c1);
    supprimer_carte(c2);
    supprimer_carte(c3);
    supprimer_carte(c4);
    supprimer_carte(c5);
    return result;
}

bool test_creer_joueur() {
    creer_grille(10);
    bool result = true;
    int numero = 1;

    joueur j = creer_joueur(numero);
    result = result && test_equality_int(1, get_numero(j), "get_numero");
    result = result && test_equality_int(50, get_energie(j), "get_energie");
    result = result && test_equality_int(0, get_idee(j), "get_idee");
    result = result && test_equality_int(1, get_gain(j), "get_gain");
    result = result && test_equality_int(NB_CARTE_BEGIN, get_nb_carte(j), "get_nb_carte");

    supprimer_joueur(j);
    supprimer_grille();
    return result;
}

bool test_creer_plateau() {
    bool result = true;
    int nb_joueur = 2;
    creer_plateau(nb_joueur);

    result = result && test_equality_int(nb_joueur, get_nb_joueur(), "get_nb_joueur");
    supprimer_plateau();
    return result;
}

bool test_choisir_carte() {
    bool result = true;
    int numero = 5;

    creer_grille(10);
    joueur j = creer_joueur(numero);
    set_idee(j, 1000);

    int num_carte = choisir_carte(j);

    result = result && test_equality_bool(true, (num_carte >= 0), "num_carte >=0");
    result = result && test_equality_bool(true, (num_carte < 5), "num_carte >5");

    piocher(j, num_carte);

    supprimer_joueur(j);
    supprimer_grille();

    return result;
}

bool test_traiter_carte() {

    creer_plateau(2);
    
    joueur j1 = get_joueur(0);
    joueur j2 = get_joueur(1);
    bool result = true;


    carte c1 = creer_carte("think");
    carte c2 = creer_carte("steal");
    carte c3 = creer_carte("panacea");
    carte c4 = creer_carte("razor");
    carte c5 = creer_carte("hell");


    traiter_carte(false,c1, get_numero(j1), get_numero(j2),0);
    result = result && test_equality_int(2, get_gain(j1), "Carte think");

    traiter_carte(false,c2, get_numero(j1), get_numero(j2),0);
    result = result && test_equality_int(3, get_gain(j1), "Carte steal1");
    result = result && test_equality_int(1, get_gain(j2), "Carte steal2");


    set_energie(j1, 50);
    traiter_carte(false, c3, get_numero(j1), get_numero(j2),0);
    result = result && test_equality_int(60, get_energie(j1), "Carte Panacea");



    traiter_carte(false,c4, get_numero(j2), get_numero(j1),0);
    result = result && test_equality_int(50, get_energie(j1), "Carte Razor");


    traiter_carte(false,c5, get_numero(j1), get_numero(j2),0);
    result = result && test_equality_bool(true, get_energie(j2) < 0, "Carte Hell");



    supprimer_carte(c1);
    supprimer_carte(c2);
    supprimer_carte(c3);
    supprimer_carte(c4);
    supprimer_carte(c5);

    supprimer_plateau();


    return result;
}

bool test_augmenter_idee() {
    creer_grille(10);
    bool result = true;
    joueur j = creer_joueur(8);
    int i_act = get_idee(j);
    augmenter_idee(j);
    int i_after = get_idee(j);
    int gain = get_gain(j);

    result = result && test_equality_int(i_act + gain, i_after, "Augmenter Idee");

    supprimer_joueur(j);
    supprimer_grille();

    return result;
}

bool test_piocher() {

    bool result = true;

    creer_plateau(2);
    joueur j = get_joueur(0);
    set_idee(j, 100);

    joueur adv = get_joueur(1);

    int choix_numero = choisir_carte(j);
    carte c = get_carte_main(choix_numero, j);
    
    traiter_carte(false, c, get_numero(j), get_numero(adv),0);
    piocher(j, choix_numero);

    int nb_carte = get_nb_carte(j);
    result = result && test_equality_int(NB_CARTE_BEGIN, nb_carte, "Nombre de cartes");

    supprimer_plateau();

    return result;

}

bool test_quitte_partie() {

    bool result = true;
    creer_plateau(3);
    int nb_avant = get_nb_joueur_vivant();
    quitte_partie(1);
    int nb_apres = get_nb_joueur_vivant();

    result = result && test_equality_int(nb_avant, nb_apres + 1, "quitter partie");
    supprimer_plateau();
    return result;
}

bool test_ajouter_memento_fin(){
  bool result = true;
  memento_list m =creer_memento();
  carte c = creer_carte("razor");
   
  m=ajouter_memento_fin(m,c);
  
  int longueur_attendue=1;
  int longueur = get_longueur(m);
  result = result && test_equality_int(longueur_attendue, longueur, "test_ajouter_fin");
  
  supprimer_tout_memento(m);
  free(m);
  
  return result; 
  
}

bool test_remplir_memento() {
    bool result = true;
    memento_list lm = creer_memento();
    lm = remplir_memento(lm);
    
    result = result && test_equality_bool(true, lm != NULL, "creer_memento NULL");
    result = result && test_equality_int(MEMENTO, get_longueur(lm), "get_longueur()");
    
    supprimer_tout_memento(lm);
    free(lm);
    
    return result;
}


bool test_melanger_memento(){
 
  bool result = true;
  
  memento_list mem= creer_memento();
  mem = remplir_memento(mem);


  return result;
}

bool test_creer_memento() {
    bool result = true;
    
    memento_list lm = creer_memento();
    result = result && test_equality_bool(true, lm != NULL, "creer_memento NULL");
    result = result && test_equality_int(0, get_longueur(lm), "get_longueur()");
    
    carte c_think = creer_carte("think");
    carte c_hell = creer_carte("hell");
    lm = ajouter_memento_fin(lm, c_think);
    lm = ajouter_memento_fin(lm, c_hell);
    memento m = get_premier(lm);
    memento m2 = get_suivant(m);
    result = result && test_equality_int(2, get_longueur(lm), "get_longueur()");
    result = result && test_equality_bool(0, strcmp(get_nom(get_carte(m)), "think"), "get_premier()");
    result = result && test_equality_bool(0, strcmp(get_nom(get_carte(m2)), "hell"), "get_suivant()");
    
    
    lm = supprimer_memento_debut(lm);
    result = result && test_equality_int(1, get_longueur(lm), "get_longueur()");
    
    
    supprimer_tout_memento(lm);
    free(lm);
    
    return result;
    
}

bool test_creer_grille() {
    bool result = true;

    creer_grille(10);

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            result = result && test_equality_bool(true, est_libre(i, j), "initialisation grille");
        }
    }

    supprimer_grille();

    return result;
}

bool test_creer_bloc() {
    bool result = true;

    creer_grille(10);

    
    creer_bloc(0, 0);
    result = result && test_equality_bool(false, !est_libre(0, 0), "est_libre_creation()");
    
    supprimer_grille();

    return result;
}

bool test_est_joueur() {
    bool result = true;

    creer_grille(10);

    joueur j = creer_joueur(5);
    set_position_x(j, 0);
    set_position_y(j, 0);
    
    creer_bloc(0, 1);
    creer_bloc(1, 0);
    creer_bloc(1, 2);
    creer_bloc(2, 1);
    
    remplir_grille(get_position_x(j), get_position_y(j), get_numero(j),false);
    result = result && test_equality_bool(0, est_encercle(get_position_x(j), get_position_y(j)), "est_encerclé()");  
    

    supprimer_joueur(j);
    supprimer_grille();

    return result;
}

bool test_est_encercle() {
    bool result = true;

    creer_grille(10);

    joueur j = creer_joueur(5);
    set_position_x(j, 1);
    set_position_y(j, 1);
    
    
    remplir_grille(get_position_x(j), get_position_y(j), get_numero(j),false);
    result = result && test_equality_int( get_numero(j), est_joueur(get_position_x(j), get_position_y(j)), "est_joueur()");  
    

    supprimer_joueur(j);
    supprimer_grille();

    return result;
}

bool test_remplir_grille() {
    bool result = true;

    creer_grille(10);

    remplir_grille(0, 0, 1,false);
    result = result && test_equality_bool(false, est_libre(0, 0), "remplir_grille()");

    supprimer_grille();

    return result;

}

bool test_creer_ami(){
    creer_grille(10);
    bool result = true;
    int adversaire = 1;
    int numero = 2;
    
    joueur j = creer_joueur(5);
    

    ami a = creer_ami(adversaire, numero, get_position(j), choisir_aleatoirement_carte());
    result = result && test_equality_int(5, get_numero(j), "get_numero");
    result = result && test_equality_int(50, get_energie(j), "get_energie");
    result = result && test_equality_int(0, get_idee(j), "get_idee");
    result = result && test_equality_int(1, get_gain(j), "get_gain");
    result = result && test_equality_int(5, get_nb_carte(j), "get_nb_carte");

    supprimer_ami(a);
    supprimer_joueur(j);
    supprimer_grille();
    return result;
}

bool test_fonction_ami(){
    
    creer_grille(10);
    bool result = true;
    int adversaire = 1;
    int numero = 2;
    
    joueur j = creer_joueur(5);
    

    ami a = creer_ami(adversaire, numero, get_position(j), choisir_aleatoirement_carte());
    result = result && test_equality_int(5, get_numero(j), "get_numero");
    result = result && test_equality_int(1, get_numero_cible(a), "get_numero");
    
    result = result && test_equality_int(50, get_energie(j), "get_energie");
    result = result && test_equality_int(0, get_idee(j), "get_idee");
    
    result = result && test_equality_int(1, get_gain(j), "get_gain");
    augmenter_gain(a);
    result = result && test_equality_int(2, get_gain(j), "get_gain");
    
    result = result && test_equality_int(5, get_nb_carte(j), "get_nb_carte");

    supprimer_ami(a);
    supprimer_joueur(j);
    supprimer_grille();
    return result;
}

int main(int argc, char* argv[]) {
    bool result = true;
    joueur no_joueur = NULL;
    carte c = NULL;
    plateau_de_jeu no_plateau = NULL;
    int numero_carte = 0;


        printf("\n"ANSI_BOLD"VERSION 5 : TEST L'AFFICHAGE DES MESSAGES D'ERREURS"ANSI_BOLD_OFF" \n");
    test_equality_int(0, 1, "error test_equality_int ");
    test_equality_bool(true, false, "error test_equality_bool ");
    test_failure_traiter_carte(c);
    test_failure_joueur(no_joueur, numero_carte);
    test_failure_plateau(no_plateau);
    printf("----------------------------------------------------------\n");
    result = result && test_equality_bool(true, test_rand_a_b(), "rand_a_b()");
    result = result && test_equality_bool(true, test_creer_carte(), "creer_carte()");
    result = result && test_equality_bool(true, test_creer_joueur(), "creer_joueur()");
    result = result && test_equality_bool(true, test_creer_plateau(), "creer_plateau()");
    result = result && test_equality_bool(true, test_creer_grille(), "creer_grille()");
    result = result && test_equality_bool(true, test_choisir_carte(), "choisir_carte()");
    result = result && test_equality_bool(true, test_traiter_carte(), "traiter_carte()");
    result = result && test_equality_bool(true, test_augmenter_idee(), "augmenter_idee()");
    result = result && test_equality_bool(true, test_piocher(), "piocher()");
    result = result && test_equality_bool(true, test_ajouter_memento_fin(), "ajouter_fin_memento()");
    result = result && test_equality_bool(true, test_remplir_memento(), "remplir_memento()");
    result = result && test_equality_bool(true, test_creer_memento(), "creer_memento()");
    result = result && test_equality_bool(true, test_remplir_grille(), "remplir_grille()");
    result = result && test_equality_bool(true, test_est_joueur(), "est_joueur()");
    result = result && test_equality_bool(true, test_creer_bloc(), "creer bloc()");
    result = result && test_equality_bool(true, test_est_encercle(), "est_encercle()");
    result = result && test_equality_bool(true, test_creer_ami(), "creer_ami()");
        result = result && test_equality_bool(true, test_quitte_partie(), "quitte_partie()");


    if (result) {
        printf(ANSI_BOLD"YOUPI tout passe!"ANSI_BOLD_OFF"\n\n");
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE;
    
}
