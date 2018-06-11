#include "../include/memento.h"
#include "../include/definition.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>


// le memento est representé par une liste chainée 
// le memento_list est une liste de memento
// un memento represente une carte et est lié au précédent et au suivant 
struct memento_list {
    int longueur;
    memento premier;
    memento dernier;
};

struct memento {
    memento precedent;
    memento suivant;
    carte c;
};

// sert a initialiser le memento_list
// le memento list créé est vide 
memento_list creer_memento() {
    memento_list m_new = calloc(1,sizeof (struct memento_list));
    if (m_new != NULL) {
        m_new->longueur = 0;
        m_new->premier = NULL;
        m_new->dernier = NULL;
    }
    return m_new;
}

// sert à liberer l'espace d'un memento 
void supprimer_memento(memento m) {
    supprimer_carte(m->c);
    free(m);
}
// sert à ajouter une carte a la fin du memento_list
memento_list ajouter_memento_fin(memento_list p_list, carte ca) {

    if (p_list != NULL) {
        memento p_new = calloc(1,sizeof *p_new);
        if (p_new != NULL) {
            p_new->c = ca;
            p_new->suivant = NULL;
            if (p_list->dernier == NULL) {
                p_new->precedent = NULL;
                p_list->premier = p_new;
                p_list->dernier = p_new;
            } else {
                p_list->dernier->suivant = p_new;
                p_new->precedent = p_list->dernier;
                p_list->dernier = p_new;
            }
            p_list->longueur++;
        }
    }
    return p_list;
}
// supprime le premier element d'un memento_list
memento_list supprimer_memento_debut(memento_list m) {

    if (m != NULL) {
        if (m->longueur > 1) {
            memento tmp = m->premier->suivant;
            supprimer_memento(m->premier);

            m->premier = tmp;
            m->longueur--;

            return m;

        } else {
            supprimer_memento(m->premier);
            free(m);
        }
    }

    return NULL;
}

static int echec(char *msg) {
    printf("Error : %s\n", msg);
    return (EXIT_FAILURE);
}

// cette fonction remplit un memento 
memento_list remplir_memento(memento_list m) {
    if (m == NULL) {
        echec("memento NULL: remplir_memento()");
        return NULL;
    }

    for (int i = 0; i < MEMENTO; i++) {
        carte ca = choisir_aleatoirement_carte();
        m = ajouter_memento_fin(m, ca);
    }

    return m;
}

carte get_carte(memento m) {
    return m->c;
}

memento get_suivant(memento m) {
    return m->suivant;
}

memento get_premier(memento_list m) {
    return m->premier;
}

//melange le memento 
memento_list melanger_memento(memento_list memento) {

  supprimer_tout_memento(memento);
  memento = remplir_memento(memento);
  return memento; 
  
}
// supprime tous les memento du memento_list et supprime le memento_list
void supprimer_tout_memento(memento_list m) {

    memento p_temp;
    memento p_del;

    if (m != NULL) {
        p_temp = m->premier;
        while (p_temp != NULL) {
            p_del = p_temp;
            p_temp = p_temp->suivant;
            supprimer_memento(p_del);
        }
    }
}
// sert à afficher le memento
void afficher_memento(memento_list m) {
    memento tmp = m->premier;
    for (int i = 0; i < m->longueur; i++) {
        tmp = tmp->suivant;
    }
}

int get_longueur(memento_list lm){
    if (lm == NULL){
        echec("liste de memento NULL : longueur_memento()");
        return EXIT_FAILURE;
    }
    
    return lm->longueur;
}
