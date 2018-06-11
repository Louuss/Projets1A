#include "../include/ami.h"
#include "../include/grille.h"
#include "../include/carte.h"
#include "../include/definition.h"

#include <string.h>
#include <time.h>

struct ami {
    int numero_adversaire;
    int numero_maitre;
    int numero_joueur;

    int vie;
    int energie;
    int idee;
    int gain;
    
    int temps;
    int cout_action;
    
    carte c;
    struct position position;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void definir_pos(ami a, struct position p) {
    if (est_libre(p.x + 1, p.y)) {
        a->position.x = (p.x + 1) % TORIQUE;
        a->position.y = p.y;

    } else if (est_libre(p.x - 1 + TORIQUE, p.y)) {
        a->position.x = (p.x - 1 + TORIQUE) % TORIQUE;
        a->position.y = p.y;

    } else if (est_libre(p.x, p.y + 1)) {
        a->position.x = p.x;
        a->position.y = (p.y + 1) % TORIQUE;

    } else if (est_libre(p.x, p.y - 1 + TORIQUE)) {
        a->position.x = p.x;
        a->position.y = (p.y - 1 + TORIQUE) % TORIQUE;
    }
}

ami creer_ami(int adversaire, int num, struct position p, carte c) {

    ami a = calloc(1, sizeof (struct ami));
    if (!a) {
        echec("ami non créé: cree_ami()");
        return NULL;
    }

    a->numero_adversaire = adversaire;
    a->numero_maitre = nb_ami_g();
    a->numero_joueur = num;
    a->vie = 20;
    a->energie = 1;
    a->idee = 1;
    a->gain = 1;
    a->temps = 0;
    a->cout_action = 15;
    a->c = c;


    definir_pos(a, p);
    remplir_grille(a->position.x, a->position.y, adversaire, true);
    augmenter_nb_ami();

    return a;

}

void supprimer_ami(ami a) {
    supprimer_carte(a->c);
    free(a);
}

int numero_joueur_ami(ami a) {
    //TODO

    return a->numero_joueur;
}

void augmenter_gain(ami a) {
    //TODO

    a->gain++;
}

int get_numero_cible(ami a) {
    //TODO

    return a->numero_adversaire;
}

int get_numero_maitre(ami a) {
    //TODO

    return a->numero_maitre;
}

carte recuperer_carte_ami(ami a) {
    //TODO

    return a->c;
}

void augmenter_energie(ami a, int i) {
    //TODO

    a->energie += i;
}

void diminuer_energie(ami a, int i) {
    //TODO

    a->energie -= i;
}

void diminuer_idee(ami a, int i) {
    //TODO

    a->idee -= i;
}

int get_idee_ami(ami a) {
    //TODO

    return a->idee;
}

void diminuer_vie(ami a) {
    a->vie--;
}

int get_vie_ami(ami a) {
    //TODO

    return a->vie;
}

void afficher_ami(ami a) {

    if (a == NULL) {
        echec("joueur NULL: afficher_main()");
        return;
    }
    printf(ANSI_BOLD"  AMI %d :"ANSI_BOLD_OFF"\n", a->numero_maitre);
    printf("        -Temps : %d\n",a->temps);
    printf("        -Nombre de tour restant : %d\n", a->vie);
    printf("        -Energie : %d\n", a->energie);
    printf("        -Idee : %d\n", a->idee);
    printf("        -Gain : %d\n", a->gain);

    printf("             __________ \n");
    if (strcmp(get_nom(a->c), "panacea") == 0) {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"  %s "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(a->c));
    } else if (strcmp(get_nom(a->c), "hell") == 0) {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"   %s   "ANSI_COLOR_RESET ANSI_BOLD_OFF"|  ", get_nom(a->c));
    } else {
        printf("            |"ANSI_COLOR_RED ANSI_BOLD"  %s"ANSI_COLOR_RESET ANSI_BOLD_OFF"   |  ", get_nom(a->c));
    }
    printf("\n");
    printf("            |          |\n");
    if (get_cout(a->c) < 10) {
        printf("            |"ANSI_COLOR_YELLOW"         %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    } else if (get_cout(a->c) == 100) {
        printf("            |"ANSI_COLOR_YELLOW"       %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    } else {
        printf("            |"ANSI_COLOR_YELLOW"        %d"ANSI_COLOR_RESET"|  ", get_cout(a->c));
    }
    printf("\n");
    if (get_rarete(a->c) == 1) {
        printf("            |"ANSI_COLOR_YELLOW"     %d/131"ANSI_COLOR_RESET"|  ", get_rarete(a->c));
    } else {
        printf("            |"ANSI_COLOR_YELLOW"    %d/131"ANSI_COLOR_RESET"|  ", get_rarete(a->c));
    }
    printf("\n");
    printf("            |__________|\n");

    printf("\n\n\n");
}

void augmenter_idee_ami(ami a) {
    //TODO

    a->idee++;
}

struct position get_pos_ami(ami a) {
    //TODO

    return a->position;
}

int get_priorite_ami(ami a) {
    //TODO

    return a->temps;
}

void diminuer_priorite_ami(ami a, int i) {
    //TODO

    a->temps -= i;
}

void augmenter_priorite_ami(ami a, int i) {
    //TODO 
    
    a->temps += i;
}

void set_numero_cible(ami a, int i){
    //TODO
    
    a->numero_adversaire = i;
    
}

int get_cout_action_ami(ami a){
    return a->cout_action;
}

void diminuer_cout_action_ami(ami a, int i){
    a->cout_action -= i;
}

void augmenter_cout_action_ami(ami a, int i){
     a->cout_action += i;
}