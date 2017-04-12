/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : dico.h

prototypes des fonctions permettants la creation et l'utilisation d'un dictionnaire
definition d'un arbre binaire de recherche
*/

#ifndef DICO_H_INCLUDED
#define DICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"

#define ASCII_a  97  //code ascii pour 'a'
#define ASCII_z 122  //code ascii pour 'z'
#define ASCII_Z  90  //code ascii pour 'Z'

#define MOTS "liste_mots.txt"   //fichier texte contenant les mots


//definition d'un element d'un arbre
struct noeud{
char* mot;              //contient un mot
struct noeud* gauche;   //un pointeur vers un mot plus petit (au sens des mots)
struct noeud* droit;    //un pointeur vers un mot plus grand
};
typedef struct noeud* pnoeud;//definition d'un pointeur sur noeud

//procedure d'initialisation de l'arbre
void init_racine(pnoeud* racine);

//fonction permettant de creer un noeud
pnoeud creerNoeud(char* mot);

//procedure ajoutant un noeud dans l'arbre
void ajouter_noeud(pnoeud* racine,char* mot);

//procedure permetttant de creer un dictionnaire
void creerDico(pnoeud* racine);

//fonction permettant de rechercher un mot dans l'arbre
int rechercher_mot(pnoeud racine,char* mot);

//procedure liberant la memoire occupe par l'arbre
void liberer_memoire_arbre(pnoeud* racine);

//procedure mettant en majuscule un mot
void mettre_majuscule(char* mot);

#endif // DICO_H_INCLUDED
