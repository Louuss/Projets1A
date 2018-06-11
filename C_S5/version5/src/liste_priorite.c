#include "../include/definition.h"
#include "../include/liste_priorite.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>


static tete_list_prio liste_priorite;

struct tete_list_prio {
    int longueur;
    priorite premier;
    priorite dernier;
};

struct priorite {
    int priorite;
    int nb_joueur;
    priorite suivant;
    priorite precedent;
    list_joueur premier;
    list_joueur dernier;
};

struct list_joueur {
    list_joueur precedent;
    list_joueur suivant;
    bool ami;
    joueur j;
    ami a;
};

void creer_liste_prio() {
    liste_priorite = malloc(sizeof (struct tete_list_prio));
    if (liste_priorite != NULL) {
        liste_priorite->longueur = 0;
        liste_priorite->premier = NULL;
        liste_priorite->dernier = NULL;
    }

}

void ajouter_prio_fin(int p) {

    if (liste_priorite != NULL) {
        priorite p_new = malloc(sizeof *p_new);
        if (p_new != NULL) {
            p_new->priorite = p;
            p_new->nb_joueur = 0;
            p_new->premier = NULL;
            p_new->dernier = NULL;
            p_new->suivant = NULL;
            if (liste_priorite->dernier == NULL) {
                p_new->precedent = NULL;
                liste_priorite->premier = p_new;
                liste_priorite->dernier = p_new;
            } else {
                liste_priorite->dernier->suivant = p_new;
                p_new->precedent = liste_priorite->dernier;
                liste_priorite->dernier = p_new;
            }
            liste_priorite->longueur++;
        }
    }
}

void ajouter_prio_debut(int p) {
    if (liste_priorite != NULL) {
        priorite p_new = malloc(sizeof *p_new);
        if (p_new != NULL) {
            p_new->priorite = p;
            p_new->nb_joueur = 0;
            p_new->premier = NULL;
            p_new->dernier = NULL;
            p_new->precedent = NULL;

            if (liste_priorite->dernier == NULL) {
                p_new->suivant = NULL;
                liste_priorite->premier = p_new;
                liste_priorite->dernier = p_new;
            } else {
                liste_priorite->premier->precedent = p_new;
                p_new->suivant = liste_priorite->premier;
                liste_priorite->premier = p_new;
            }
            liste_priorite->longueur++;
        }
    }
}

bool get_ami_bool(priorite p) {
    return p->premier->ami;
}

int recuperer_joueur_debut(priorite p) {

    int result = 0;
    bool ami = get_ami_bool(p);
    if (p != NULL) {
        if (p->premier != NULL) {
            ami = p->premier->ami;

            if (p->premier->suivant != NULL) {
                list_joueur tmp = p->premier->suivant;

                if (ami == true) {
                    result = get_numero_maitre(p->premier->a);
                    result = 0 - result;

                } else {
                    result = get_numero(p->premier->j);
                }

                p->premier = tmp;

            } else {
                if (ami == true) {
                    result = get_numero_maitre(p->premier->a);
                    result = 0 - result;

                } else {
                    result = get_numero(p->premier->j);
                }
            }
        }
    }

    p->nb_joueur--;

    return result;
}

void ajouter_joueur_fin(joueur j, priorite p) {

    if (p != NULL) {
        list_joueur j_new = malloc(sizeof *j_new);
        if (j_new != NULL) {
            j_new->j = j;
            j_new->ami = false;
            j_new->a = NULL;
            j_new->suivant = NULL;
            if (p->dernier == NULL) {
                j_new->precedent = NULL;
                p->premier = j_new;
                p->dernier = j_new;
            } else {
                p->dernier->suivant = j_new;
                j_new->precedent = p->dernier;
                p->dernier = j_new;
            }
        }
        p->nb_joueur++;
    }
}

void ajouter_ami_fin(ami a, priorite p) {

    if (p != NULL) {
        list_joueur j_new = malloc(sizeof *j_new);
        if (j_new != NULL) {
            j_new->j = NULL;
            j_new->ami = true;
            j_new->a = a;
            j_new->suivant = NULL;
            if (p->dernier == NULL) {
                j_new->precedent = NULL;
                p->premier = j_new;
                p->dernier = j_new;
            } else {
                p->dernier->suivant = j_new;
                j_new->precedent = p->dernier;
                p->dernier = j_new;
            }
        }
        p->nb_joueur++;
    }
}

priorite inserer_prio(priorite curseur, int prio) {
    if (curseur != NULL) {
        curseur = curseur->precedent;
        liste_priorite->longueur++;
        
        priorite p_new = malloc(sizeof (struct priorite));
        if (p_new != NULL) {
            p_new->priorite = prio;
            p_new->nb_joueur =0;
            p_new->premier = NULL;
            p_new->dernier = NULL;

            p_new->precedent = curseur;
            p_new->suivant = curseur->suivant;
            curseur->suivant = p_new;
            curseur->suivant->suivant->precedent = p_new;
        }
        return p_new;
    }
return NULL;
}

void replacer_joueur(bool a, joueur j, ami am) {


    int prio = 0;
    if (a == true) {
        prio = get_priorite_ami(am);
    } else {
        prio = get_priorite(j);
    }

    priorite curseur = liste_priorite->premier;
    if (curseur != NULL) {

        if (prio < curseur->priorite) {
            ajouter_prio_debut(prio);
            curseur = liste_priorite->premier;

            if (a == true) {
                ajouter_ami_fin(am, curseur);
            } else {
                ajouter_joueur_fin(j, curseur);
            }

        } else {


            //Trouver la priorite
            while (prio > curseur->priorite) {
                if (curseur->suivant == NULL) {
                    ajouter_prio_fin(prio);
                    curseur = curseur->suivant;
                    break;
                }

                curseur = curseur->suivant;
            }

            if (prio == curseur->priorite) {
                if (a == true) {
                    ajouter_ami_fin(am, curseur);
                } else {
                    ajouter_joueur_fin(j, curseur);
                }
            } else {
                curseur = inserer_prio(curseur, prio);
                if (a == true) {
                    ajouter_ami_fin(am, curseur);
                } else {
                    ajouter_joueur_fin(j, curseur);
                }
            }
        }

    } else {
        ajouter_prio_fin(prio);
        replacer_joueur(a, j, am);
    }
}

void supprimer_joueur_list(list_joueur lj) {
    if (lj->ami == true) {
        supprimer_ami(lj->a);
    } else {
        supprimer_joueur(lj->j);
    }
    free(lj);
}

priorite recuperer_liste_debut() {
    priorite tmp = liste_priorite->premier;
    liste_priorite->longueur--;
    if (tmp != NULL) {
        if (liste_priorite->longueur == 0) {
            liste_priorite->premier = NULL;
            liste_priorite->dernier = NULL;
        } else {
            liste_priorite->premier = liste_priorite->premier->suivant;
        }
        tmp->suivant = NULL;
    }


    return tmp;
}

int get_joueur_list(priorite p) {
    //TODO

    return p->nb_joueur;
}

void afficher_tete_liste(){
    priorite p = liste_priorite->premier;
    while(p != NULL){
        printf(" %d -> ",p->priorite);
        p = p->suivant;
    }
}

void supprimer_priorite(priorite p){
  free(p); 
}

void supprimer_tete_liste(){
  while(liste_priorite->premier !=NULL)
    {
      priorite p = recuperer_liste_debut(); 
      supprimer_priorite(p); 
    } 
}
