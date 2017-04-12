/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : liste.h

prototypes des fonctions permettants la creation et le traitement d'une liste de lettres
definition d'une liste de lettres
*/

#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOMBRE_LETTRES  20  //nombre de lettres dans la liste des joueurs
#define ALPHABET        26  //nombre de lettres dans l'alphabet

#define ASCII_ENTREE    10  //code ascii pour '\n'
#define FIN_DE_CHAINE    0  //code ascii pour '\0'
#define ASCII_A         65  //code ascii pour 'A'

#define FAUX             0  //valeur boolenne pour faux
#define VRAI             1  //valeur boolenne pour vrai


//definition d'une liste de lettres
struct liste{
char lettre;            //contient un caractere
struct liste* suivant;  //pointeur sur l'element suivant de la liste
};
typedef struct liste* pliste;//definition d'un pointeur sur liste

//fonction retournant une lettre au hasard
char tirage_lettre();

//procedure d'initialisation d'une liste de lettres
void init(pliste* debut);

//fonction creant et retournant un pointeur de type pliste
pliste creerVD(pliste debut);

//procedure ajoutant un element (un caractere) au debut d'une liste
void ajoutdebut(pliste* debut);

//procedure creant une liste de lettres
void remplissage(pliste* debut,int l);

//procedure affichant les caracteres d'une liste
void affichage_liste_lettres(pliste debut);

//fonction supprimant un element d'une liste qui retourne le caractere contenu dans l'element supprime
int supprimer(pliste* debut,int lettre);

//procedure permettant de liberer la memoire occupee par une lettre
void liberer_memoire_liste(pliste* debut);

//fonction retournant le nombre d'elements d'une liste
int longueur_liste(pliste debut);

//fonction verifiant si les listes de lettres des deux joueurs sont vides
int listes_vides(pliste joueur1,pliste joueur2);

//procedure permettant d'ajouter un caractere a la fin d'une liste
void ajouter_fin(pliste* debut,char l);

//fonction permettant de saisir une chaine de caracteres
pliste saisie_chaine(FILE* fichier);

//fonction permettant de convertir une liste de caracteres en tableau de caracteres
char* tableau_caracteres(pliste saisie);

#endif // LISTE_H_INCLUDED
