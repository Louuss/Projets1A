#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include <stdio.h>
#include <stdlib.h>


//Couleur
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_BOLD_OFF      "\x1b[22m"
#define DROMA            "\e[105m"
#define CARAMEL            "\e[103m"
#define DEFAULT            "\e[49m"

//Relier au carte
#define NB_CARTE_BEGIN 5
#define MEMENTO 50
#define PROBA 186

//Relier a la grille 
#define TAILLE 50
#define TORIQUE (TAILLE)

//Relier aux amis 
#define NB_AMI 100

//Relier au plateau
#define NB_JOUEUR 5

//Relier au priorite
#define NB_PRIO_BEGIN 1

//definition 
#define FAIL -1

#endif
