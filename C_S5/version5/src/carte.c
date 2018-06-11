#include "../include/carte.h"
#include "../include/plateau.h"
#include "../include/definition.h"
#include "../include/liste_priorite.h"
#include <string.h>
#include <time.h>
#include <limits.h>

struct carte {
    char* nom;
    int cout;
    int rarete;
    pointeur_fonction application_carte;
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

void kitty_think(int moi, int ad, bool ami, int num_a) {
    if (ami == false) {
        set_gain(get_joueur_tab(moi), get_gain(get_joueur_tab(moi)) + 1);
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 5);
    } else {
        augmenter_gain(get_ami_tab(moi));
        diminuer_idee(get_ami_tab(moi), 5);
    }
}

void kitty_steal(int moi, int ad, bool ami, int num_a) {
    if (ami == false) {
        set_gain(get_joueur_tab(moi), get_gain(get_joueur_tab(moi)) + 1);
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 10);
    } else {
        augmenter_gain(get_ami_tab(moi));
        diminuer_idee(get_ami_tab(moi), 10);
    }
    
    if (get_gain(get_joueur(ad)) != 1)
        set_gain(get_joueur(ad), get_gain(get_joueur(ad)) - 1);
}

void kitty_panacea(int moi, int ad, bool ami, int num_a) {
    if (ami == false) {
        set_energie(get_joueur_tab(moi), get_energie(get_joueur_tab(moi)) + 10);
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 2);
    } else {
        augmenter_energie(get_ami_tab(moi),10);
        diminuer_idee(get_ami_tab(moi), 2);
    }
}

void kitty_razor(int moi, int ad, bool ami, int num_a) {
    set_energie(get_joueur(ad), get_energie(get_joueur(ad)) - 10);

    if (ami == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 2);
    } else {
       diminuer_idee(get_ami_tab(moi), 2);
    }
}

void kitty_hell(int moi, int ad, bool ami, int num_a) {
    set_energie(get_joueur(ad), get_energie(get_joueur(ad)) - INT_MAX);

    if (ami == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 100);
    } else {
        diminuer_idee(get_ami_tab(moi), 100);
    }
}

void kitty_stone(int moi, int ad, bool ami, int num_a) {
    creer_bloc(get_position_x(get_joueur(ad)), get_position_y(get_joueur(ad)));

    if (ami == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 10);
    } else {
        diminuer_idee(get_ami_tab(moi), 10);
    }

}

void kitty_puppy(int moi, int ad, bool ami_b, int num_a) {
    ami a;
    if (ami_b == true){
        a = creer_ami(get_numero(get_joueur(ad)),get_numero(get_joueur_tab(num_a)), get_position(get_joueur_tab(num_a)), choisir_aleatoirement_carte());
        set_ami(get_nb_ami(get_joueur_tab(num_a)), get_joueur_tab(num_a), a);
        augmenter_nb_ami_joueur(get_joueur_tab(num_a));
    }else{
        a = creer_ami(get_numero(get_joueur(ad)),get_numero(get_joueur_tab(moi)), get_position(get_joueur_tab(moi)), choisir_aleatoirement_carte());
        set_ami(get_nb_ami(get_joueur_tab(moi)), get_joueur_tab(moi), a);
        augmenter_nb_ami_joueur(get_joueur_tab(moi));
    }
    set_ami_plateau(get_nb_ami_plateau(), a);
    
    augmenter_nb_ami_plateau();

    if (ami_b == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 5);
    } else {
        diminuer_idee(get_ami_tab(moi), 5);
    }
    
    replacer_joueur(true, NULL, a);
}

void kitty_slow(int moi, int ad, bool ami, int num_a) {
    if (ami == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 2);
        set_cout_action(get_joueur_tab(moi),get_cout_action(get_joueur_tab(moi)) + 1);
    } else {
        diminuer_idee(get_ami_tab(moi), 2);
        augmenter_cout_action_ami(get_ami_tab(moi), 1);
    }
}

void kitty_speed(int moi, int ad, bool ami, int num_a) {
    
    
    if (ami == false) {
        set_idee(get_joueur_tab(moi), get_idee(get_joueur_tab(moi)) - 5);
        if (get_cout_action(get_joueur_tab(moi)) > 1)
            set_cout_action(get_joueur_tab(moi),get_cout_action(get_joueur_tab(moi)) - 1);
    } else {
        diminuer_idee(get_ami_tab(moi), 5);
        if (get_cout_action_ami(get_ami_tab(moi)) > 1)
            diminuer_cout_action_ami(get_ami_tab(moi), 1);
    }
}

carte creer_carte(char* nom) {
    if (nom == NULL) {
        echec("nom NULL: creer_carte()");
        return NULL;
    }

    carte c = malloc(sizeof (struct carte));

    if (strcmp(nom, "think") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
        c->application_carte = kitty_think;
    }

    else if (strcmp(nom, "steal") == 0) {
        c->nom = nom;
        c->cout = 10;
        c->rarete = 100 / 10;
        c->application_carte = kitty_steal;
    }

    else if (strcmp(nom, "panacea") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
        c->application_carte = kitty_panacea;
    }

    else if (strcmp(nom, "razor") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
        c->application_carte = kitty_razor;
    }


    else if (strcmp(nom, "hell") == 0) {
        c->nom = nom;
        c->cout = 100;
        c->rarete = 1;
        c->application_carte = kitty_hell;
    }

    else if (strcmp(nom, "stone") == 0) {
        c->nom = nom;
        c->cout = 10;
        c->rarete = 100 / 10;
        c->application_carte = kitty_stone;
    }

    else if (strcmp(nom, "puppy") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
        c->application_carte = kitty_puppy;
    }
    
    else if (strcmp(nom, "slow") == 0) {
        c->nom = nom;
        c->cout = 2;
        c->rarete = 100 / 2;
        c->application_carte = kitty_slow;
    }

    else if (strcmp(nom, "speed") == 0) {
        c->nom = nom;
        c->cout = 5;
        c->rarete = 100 / 5;
        c->application_carte = kitty_speed;
    }
    
    return c;
}

void supprimer_carte(carte c) {
    free(c);
}

carte copie_carte(carte c) {
    return creer_carte(c->nom);
}

char* get_nom(carte c) {
    if (c == NULL) {
        echec("carte NULL : get_nom()");
        return NULL;
    }

    return c->nom;
}

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
    if (c == NULL) {
        echec("carte NULL : set_cout()");
        return;
    }

    c->cout = a;
}

void set_rarete(carte c, int a) {
    if (c == NULL) {
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
    return rand() % (max - min) + min;
}

carte choisir_aleatoirement_carte() {

    int alea = rand_a_b(0, PROBA);

    if (alea < 20) {
        return creer_carte("think");
    } else if (alea < 30) {
        return creer_carte("steal");
    } else if (alea < 80) {
        return creer_carte("panacea");
    } else if (alea < 130) {
        return creer_carte("razor");
    } else if (alea == 131) {
        return creer_carte("hell");
    } else if (alea < 141) {
        return creer_carte("stone");
    }else if (alea < 146) {
        return creer_carte("puppy");
    }else if (alea < 166) {
        return creer_carte("slow");
    }

    return creer_carte("speed");
}

pointeur_fonction get_application_carte(carte c) {
    //TODO

    return c->application_carte;
}
