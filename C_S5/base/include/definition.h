#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include <stdio.h>
#include <stdlib.h>


//L'interface definition permet de mettre en place tout les #define de base

//Couleur
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_BOLD_OFF      "\x1b[22m"

//Relier au carte
#define NB_CARTE_BEGIN 5
#define MEMENTO 50
#define PROBA 146

//Relier a la grille 
#define TAILLE 50
#define TORIQUE (TAILLE)

//Relier aux amis 
#define NB_AMI 100

//Relier au plateau
#define NB_JOUEUR 15

//definition 
#define FAIL -1

#endif
