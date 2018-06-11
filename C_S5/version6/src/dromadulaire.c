#include "../include/dromadulaire.h"
#include "../include/grille.h"
#include "../include/definition.h"

#include <string.h>
#include <time.h>
#include <stdbool.h>

static dromadulaire droma; 

struct position {
    int x;
    int y;
};

struct dromadulaire {
    struct position position;
    
};

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

static int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

static void definir_position() {

    int x_pos = 0;
    int y_pos = 0;

    do {
        x_pos = rand_a_b(0, TORIQUE);
        y_pos = rand_a_b(0, TORIQUE);
    } while (!est_libre(x_pos, y_pos) && !est_libre(x_pos+1, y_pos) &&
            !est_libre(x_pos, y_pos+1) && !est_libre(x_pos-1, y_pos) &&
            !est_libre(x_pos, y_pos-1));

    droma->position.x = x_pos % TORIQUE;
    droma->position.y = y_pos % TORIQUE;
    remplir_grille_droma(x_pos, y_pos);
}

void creer_dromadulaire() {

    droma = calloc(1, sizeof (struct dromadulaire));
    if (!droma) {
        echec("dromadulaire non créé: cree_dromadulaire()");
        return ;
    }

    definir_position();
}