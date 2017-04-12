/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : score.h

prototypes des fonctions permettants la creation et le traitement d'une liste de scores
definition d'un score
definition d'une liste de scores
*/

#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

#define NOMBRE_SCORES          10 //nombre de scores maximum enregistres
#define SCORES "liste_scores.txt" //fichier contenant les meilleurs scores

//definition d'un score
typedef struct{
char* nom;  //contient le nom du joueur
int points; //ainsi que son nombre de points
}score;

//definition d'une liste de score
struct liste_scores{
score meilleur;                 //contient un score
struct liste_scores* suivant;   //et un lien vers le score suivant
};
//on definit un pointeur sur liste_scores
typedef struct liste_scores* pliste_scores;

//procedure d'initialisation d'une liste de scores
void init_score(pliste_scores* debut);

//fonction creant un element d'une liste de scores
pliste_scores creerVD_score(pliste_scores debut,score s);

//procedure permettant de recuperer les scores enregistres
void stocker_score(pliste_scores* debut);

//procedure permettant d'afficher les scores
void affichage_scores(pliste_scores debut);

//fonction permettant de determiner la longueur d'une liste de scores
int longueur_liste_scores(pliste_scores debut);

//procedure permettant d'ajouter un scores dans la liste des meilleurs scores
void ajouter_scores(pliste_scores* debut,char* nom,int points);

//procedure permettant de trier une liste de scores dans l'ordre decroissant du nombre de points
void trier_scores(pliste_scores* debut);

//procedure permettant de trier un tableau d'entier dans l'ordre croissant
void trier_tableau(score* tab,int n);

//procedure permettant d'echanger deux elements de type score
void echanger(score* a,score* b);

//procedure permettant de detruire une liste de score
void vider_liste_scores(pliste_scores* debut);

//fonction renvoyant le dernier element d'une liste de scores
pliste_scores dernier_score(pliste_scores debut);

#endif // SCORES_H_INCLUDED
