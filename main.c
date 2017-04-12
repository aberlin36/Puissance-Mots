/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : main.c
programme principale
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dico.h"
#include "liste.h"
#include "scores.h"

#define LIGNE       3   //nombre de lignes de la grille de jeu
#define COLONNE     3   //nombre de colonne de la grille de jeu
#define INIT_TOUR   2   //initialisation du nombre de tour de jeu

#define ASCII_0    48   //code ascii pour '0'
#define ASCII_1    49   //code ascii pour '1'
#define ASCII_2    50   //code ascii pour '2'
#define ASCII_3    51   //code ascii pour '3'
#define ASCII_4    52   //code ascii pour '4'

#define REGLES "regles.txt" //fichier texte contenant les regles du jeu


//definition d'un joueur
typedef struct{
char* nom;      //nom du joueur
pliste debut;   //liste de lettres du joueur
int points;     //nombre de points du joueur
}joueur;

//position d'un element dans un tableau deux dimensions
typedef struct{
int i;  //coordonnee sur la ligne
int j;  //coordonnee sur la colonne
}position;


//procedure initialisant les informations relatives au deux joueurs
void initialisation(joueur *a,joueur *b);

//procedure initialisant le nombre de tours du jeu
void init_nb_tours(int *nb_tours);

//procedure affichant la grille de jeu
void afficher_grille(char grille[LIGNE][COLONNE]);

//procedure initialisant la grille de jeu avec un caractere
void init_grille(char grille[LIGNE][COLONNE],int c);

//fonction retournant la derniere ligne vide d'une colonne
int ligne(char grille[LIGNE][COLONNE],int j);

//fonction permettant a un joueur de decider ce qu'il va va faire de ses lettres
position decision(joueur* jcourant,char grille[LIGNE][COLONNE],pnoeud racine);

//fonction verifiant si la grille est pleine
int grille_pleine(char grille[LIGNE][COLONNE],int c);

//fonction permettant de detecter un mot verticalement dans la grille
int detection_verticale(pnoeud racine,char grille[LIGNE][COLONNE],position p);

//fonction permettant de detecter un mot horizontalement dans la grille
int detection_horizontale(pnoeud racine,char grille[LIGNE][COLONNE],position p);

//fonction permettant de detecter un mot diagonalement dans la grille
int detection_diagonale(pnoeud racine,char grille[LIGNE][COLONNE],position p);

//procedure permettant de calculer le nombre de points gagnés
void points_gagnes(pnoeud racine,char grille[LIGNE][COLONNE],position p,int* nb_points);

//procedure permettant de jouer a puissance mot
void jouer(pliste_scores* debut);

//fonction changeant une lettre minuscule en majuscule
char maj(char lettre);

//procedure permettant de placer une lettre dans la grille
void jouer_lettre(position* p,char grille[LIGNE][COLONNE],joueur* jcourant);

//procedure permettant de rechercher un mot dans le dictionnaire
void rechercher_dico(pnoeud dico);

//procedure permettant de changer les lettres d'un joueur
void changer_lettres(pliste* debut);

//fonction permettant de saisir un caractere
int saisie_caractere(int c);

//fonction transformant un tableau de caractere en nombre
int nombre(char* tab);

//procedure executant un tour de jeu pour un joueur
void tour(joueur* jcourant,joueur autre,char grille[LIGNE][COLONNE],pnoeud racine);

//procedure permettant d'afficher les regles du jeu
void afficher_regles();

int main()
{
    pliste_scores debut;    //creation d'une liste de scores
    int choix;              //choix du joueur

    do
    {
        //menu
        printf("\n\t\t\t***************************\n");
        printf("\t\t\t*BIENVENUE A PUISSANCE MOT*\n");
        printf("\t\t\t***************************\n\n");
        printf("\t\tEntrez %c pour afficher les regles du jeu\n",ASCII_1);
        printf("\t\tEntrez %c pour afficher les %d meilleurs scores\n",ASCII_2,NOMBRE_SCORES);
        printf("\t\tEntrez %c pour jouer\n",ASCII_3);
        printf("\t\tEntrez %c pour quitter le jeu\n",ASCII_0);

        //saisie du choix du joueur
        printf("\n\t\tQue voulez vous faire ? ");
        choix=saisie_caractere(choix);

        switch(choix)//selon le choix du joueur
        {
            case ASCII_1 ://on affiche les regles du jeu
            afficher_regles();
            break;

            case ASCII_2 :
            stocker_score(&debut);      //on récupere les scores enregistres
            affichage_scores(debut);    //on les affiche
            vider_liste_scores(&debut); //on libere la memoire occupee par les scores
            break;

            case ASCII_3 ://on joue
            jouer(&debut);
            vider_liste_scores(&debut);
            break;

            case ASCII_0 ://on quitte le jeu
            printf("\n\tA bientot!\n");
            break;

            default ://la saisie du choix par le joueur est non valide
            printf("\ncommande inconnue!\n");
            break;
        }
    }while(choix!=ASCII_0);//tant que le joueur ne veut pas quitter le jeu

    return EXIT_SUCCESS;
}

//prend en parametres les deux joueurs
void initialisation(joueur *a,joueur *b)
{
    //on saisie leurs noms
    printf("\nJoueaur 1, Veuillez saisir votre nom : ");
    a->nom=tableau_caracteres(saisie_chaine(stdin));
    printf("\nJoueaur 2, Veuillez saisir votre nom : ");
    b->nom=tableau_caracteres(saisie_chaine(stdin));

    //leurs noms doivent etre differents
    while(strcmp(a->nom,b->nom)==0)
    {
        printf("\nChoisissez un nom different de celui du joueur 1 : ");
        b->nom=tableau_caracteres(saisie_chaine(stdin));
    }

    //on leur attribue une liste de lettres
    remplissage(&a->debut,NOMBRE_LETTRES);
    remplissage(&b->debut,NOMBRE_LETTRES);

    //au debut ils n'ont aucun point
    a->points=0;
    b->points=0;
}

//prend en parametres le nombre de tours de jeu
void init_nb_tours(int *nb_tours)
{
    int hasard;
    hasard=(rand()%INIT_TOUR);//hasard vaudra entre 0 et INIT_TOUR (2) non compris
    switch(hasard)//il y a INIT_TOUR cas selon les valeurs de hasard
    {
        case 0 :        //si hasard vaut 0
        *nb_tours=1;    //le nombre de tour est initialise a 1
        break;

        case 1 :        //si hasard vaut 1
        *nb_tours=2;    //le nombre de tour est initialise a 2
        break;
    }
}

//prend en parametre la grille de jeu
void afficher_grille(char grille[LIGNE][COLONNE])
{
    int i,j;        //compteurs
    int booleen=FAUX;  //variable booleenne initialisee a faux

    printf("\nVoici la grille de jeu :\n\n");
    //on parcour la grille pour afficher ses elements
    for(i=0;i<LIGNE;i++)
    {
        for(j=0;j<COLONNE;j++)
        {
            if(booleen==0)//si on n'a pas encore afficher le numero des colonnes
            {
                for(j=0;j<COLONNE;j++)
                {
                    //on affiche le numero des colonnes
                    if(j==0)
                    {
                         printf("\t\t%.2d ",j+1);
                    }
                    else
                    {
                        printf("%.2d ",j+1);
                    }

                }
                printf("\n");
                booleen=1;//booleen vaut maintenant vrai
                j=0;//on reinitialise le compteur j a 0
            }
            if(j==0)
            {
                printf("\t\t%c  ",grille[i][j]);
            }
            else
            {
                printf("%c  ",grille[i][j]);
            }
        }
        printf("\n");
    }
}

//prend en parametre la grille de jeu et un caractere
void init_grille(char grille[LIGNE][COLONNE],int c)
{
    int i,j;

    //on remplit la grille avec le caractere pris en parametre
    for(i=0;i<LIGNE;i++)
    {
        for(j=0;j<COLONNE;j++)
        {
            (grille[i][j])=c;
        }
    }
}

//prend en parametres la grille de jeu et le numero de la colonne
int ligne(char grille[LIGNE][COLONNE],int j)
{
    int i=0;

    //tant qu'on ne rencontre pas le caractere \0 ou qu'on ne sort pas de la grille
    while((grille[i][j]==FIN_DE_CHAINE)&&(i<LIGNE))
    {
        i++;//on s'enfonce vers le fond de la colonne j
    }
    if(i==0)//si i vaut 0 c'est que la colonne est remplie
    {
        printf("colonne remplie");
    }
    //on retourne le numero de la ligne
    return(i-1);
}

//prend en parametres un joueur et la grille
position decision(joueur* jcourant,char grille[LIGNE][COLONNE],pnoeud racine)
{
    position p;
    int choix;
    int test;   //variable booleenne

    //on affiche la grille
    afficher_grille(grille);

    //on affiche les lettres dont le joueur dispose
    printf("\nVoici les lettres dont vous disposez :\n\n");
    affichage_liste_lettres((*jcourant).debut);

    //le joueur a plusieur choix de jeu
    printf("\n\n\t\tEntrez %c pour jouer une lettre\n",ASCII_1);
    printf("\t\tEntrez %c pour changer vos lettres\n",ASCII_2);
    printf("\t\tEntrez %c pour passer votre tour\n",ASCII_3);
    printf("\t\tEntrez %c pour rechercher un mot dans le dictionnaire\n",ASCII_4);

    do
    {
        //on saisie le choix du joueur
        printf("\n\t\tQue voulez vous faire ? ");
        choix=saisie_caractere(choix);

        test=FAUX;//on initialise test a faux

        //selon le choix du joueur
        switch(choix)
        {
            case ASCII_1 ://le joueur place une lettre dans la grille
            jouer_lettre(&p,grille,jcourant);
            break;

            case ASCII_2 ://le joueur change ses lettres
            changer_lettres(&jcourant->debut);
            p.i=LIGNE;
            break;

            case ASCII_3 ://le joueur passe son tour
            p.i=LIGNE;
            break;

            case ASCII_4 ://le joueur recherche un mot dans le dictionnaire
            rechercher_dico(racine);
            test=VRAI;
            break;

            default ://le choix du joueur n'est pas defini
            printf("\n\t\tcommande inconnue! Veuillez recommencer : ");
            test=VRAI;
            break;
        }
    }while(test!=FAUX);

    return p;//on retoutne la position de la lettre jouee dans la grille
}

//prend en parametre la grille de jeu et le caractere d'initialisation
int grille_pleine(char grille[LIGNE][COLONNE],int c)
{
    int i,j;
    int test;

    //on part du principe que la grille est pleine de lettres
    test=VRAI;//test vaut vrai

    for(i=0;i<LIGNE;i++)
    {
        for(j=0;j<COLONNE;j++)
        {
            //si on rencontre le caractere \0
            if(grille[i][j]==c)
            {
                //alors la grille n'est pas pleine
                test=FAUX;//test vaux faux
            }
        }
    }
    if(test==VRAI)
    {
        afficher_grille(grille);
        printf("\n\nLa grille est pleine!");
    }

    //on retourne vrai ou faux
    return(test);
}

//prend en parametres le dictionnaire, la grille et la position de la lettre jouee
int detection_verticale(pnoeud racine,char grille[LIGNE][COLONNE],position p)
{
    //on localise la lettre jouee dans la grille grace a sa position
    int i=p.i;
    int j=p.j;

    int k;  //compteur

    //zone memoire qui va recuperer le mot forme
    char* mot=malloc((LIGNE-i)+1);

    if(mot==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction detection_verticale");
        return(EXIT_FAILURE);
    }

    mot[LIGNE-i]=FIN_DE_CHAINE;

    k=0;
    while(i<LIGNE)//tant qu'on ne sort pas de la grille
    {
        //on recupere chaque lettre en se deplacant verticalement
        mot[k]=grille[i][j];
        i++;
        k++;
    }

    //si le mot recuperer est dans le dictionnaire
    if(rechercher_mot(racine,mot)==VRAI)
    {
        //le joueur gagne autant de points que le mot a de lettres
        printf("\nBRAVO! Vous avez ecrit verticalement le mot : %s\nVous gagnez %d points!\n",mot,k);
        return k;//on retourne le nombre de points
    }

    //on libere la memoire contenant le mot
    free(mot);

    //si le mot n'est pas dans le dictionnaire le joueur ne gagne pas de points
    return FAUX;//et donc on retourne FAUX
}

//prend en parametres le dictionnaire, la grille et la position de la lettre jouee
int detection_horizontale(pnoeud racine,char grille[LIGNE][COLONNE],position p)
{
    int i=p.i;
    int j=p.j;
    int k;

    //on récupere la taille du mot
    while((grille[i][j-1]!=FIN_DE_CHAINE)&&(j>0))
    {
        j--;
    }
    k=1;
    while((grille[i][j+1]!=FIN_DE_CHAINE)&&(j<COLONNE-1))
    {
        j++;
        k++;
    }

    char* mot=malloc(k+1);

    if(mot==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction detection_horizontale\n");
        return(EXIT_FAILURE);
    }

    mot[k]=FIN_DE_CHAINE;

    //on recupere le mot
    j=p.j;
    k=0;
    while((grille[i][j-1]!=FIN_DE_CHAINE)&&(j>0))
    {
        j--;
    }
    while((grille[i][j]!=FIN_DE_CHAINE)&&(j<COLONNE))
    {
        mot[k]=grille[i][j];
        j++;
        k++;
    }

    //on vérifie si le mot est dans le dictionnaire
    if(rechercher_mot(racine,mot)==VRAI)
    {
        printf("\nBRAVO! Vous avez ecrit horizontalement le mot : %s\nVous gagnez %d points!\n",mot,k);
        return k;
    }
    free(mot);
    return FAUX;
}

//prend en parametres le dictionnaire, la grille et la position de la lettre jouee
int detection_diagonale(pnoeud racine,char grille[LIGNE][COLONNE],position p)
{
    //meme principe que la fonction precedente

    int i=p.i;
    int j=p.j;
    int k;

    while((grille[i-1][j-1]!=FIN_DE_CHAINE)&&((j>0)&&(i>0)))
    {
        j--;
        i--;
    }
    k=1;
    while((grille[i+1][j+1]!=FIN_DE_CHAINE)&&((j<COLONNE-1)&&(i<LIGNE-1)))
    {
        j++;
        i++;
        k++;
    }

    char* mot=malloc(k+1);

    if(mot==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction detection_diagonale");
        return(EXIT_FAILURE);
    }

    mot[k]=FIN_DE_CHAINE;

    i=p.i;
    j=p.j;
    k=0;
    while((grille[i-1][j-1]!=FIN_DE_CHAINE)&&((j>0)&&(i>0)))
    {
        j--;
        i--;
    }
    while((grille[i][j]!=FIN_DE_CHAINE)&&((j<COLONNE)&&(i<LIGNE)))
    {
        mot[k]=grille[i][j];
        j++;
        i++;
        k++;
    }

    if(rechercher_mot(racine,mot)==VRAI)
    {
        printf("\nBRAVO! Vous avez ecrit diagonalement le mot : %s\nVous gagnez %d points!",mot,k);
        return k;
    }
    free(mot);
    return FAUX;
}

//prend en parametres le dictionnaire, la grille, la position d'une lettre dans la grille et le nombre de point
void points_gagnes(pnoeud racine,char grille[LIGNE][COLONNE],position p,int* nb_points)
{
    int n1,n2,n3;

    //on fait les trois detections de mot en recuperant a chaque fois le nombre de points gagnes
    n1=detection_verticale(racine,grille,p);
    n2=detection_horizontale(racine,grille,p);
    n3=detection_diagonale(racine,grille,p);

    //on ajoute les points gagnes au nombre de points actuel du joueur
    *nb_points+=(n1+n2+n3);
}

//prend en parametre la liste des meilleurs scores
void jouer(pliste_scores* debut)
{
    joueur joueur1,joueur2;         //variables contenants les informations liéés aux deux joueurs
    int nb_tours;                   //nombre de tours de jeu
    char grille[LIGNE][COLONNE];    //grille de jeu
    pnoeud racine;                  //dictionnaire

    srand(time(NULL));

    //on charge le dictionnaire
    printf("\nChargement du dictionnaire ");
    creerDico(&racine);
    printf("\n");

    initialisation(&joueur1,&joueur2);  //on recupere les informations des joueurs
    init_grille(grille,FIN_DE_CHAINE);  //on initialise la grille
    init_nb_tours(&nb_tours);           //on initialise le nombre de tours a 1 ou a 2

    do
    {
        if(nb_tours%2==0)               //si le nombre de tours est paire
        {
            //c'est le joueur 1 qui joue
            tour(&joueur1,joueur2,grille,racine);
        }
        else                            //si le nombre de tours est impaire
        {
            //c'est le joueur 2 qui joue
            tour(&joueur2,joueur1,grille,racine);
        }

        //on passe au tour suivant
        nb_tours++;

    }while((grille_pleine(grille,FIN_DE_CHAINE)!=VRAI)&&(listes_vides(joueur1.debut,joueur2.debut)!=VRAI));
    //le jeu s'arrete quand la grille est pleine ou lorsque un des joueurs n'a plus de lettres

    printf("\n*******************************************************************************\n");
    printf("\n\t\tLa partie est terminee\n");

    //si le joueur 1 a gagne
    if(joueur1.points>joueur2.points)
    {
        //on affiche son score
        printf("\nC'est %s qui l'emporte avec un score de %d points!\n",joueur1.nom,joueur1.points);

        //si son score est bon on l'ajoute dans la liste des 10 meilleurs scores
        ajouter_scores(debut,joueur1.nom,joueur1.points);
    }

    //meme chose si le joueur 2 gagne
    else if(joueur1.points<joueur2.points)
    {
        printf("\nC'est %s qui l'emporte avec un score de %d points!\n",joueur2.nom,joueur2.points);
        ajouter_scores(debut,joueur2.nom,joueur2.points);
    }

    //si il y a match nul
    else
    {
        printf("\nMATCH NUL!\n");
        printf("\nVous avez tous les deux un score de %d\n",joueur1.points);

        //les scores des deux joueurs peuvent etre enregistres dans la liste des 10 meilleurs scores
        ajouter_scores(debut,joueur1.nom,joueur1.points);
        ajouter_scores(debut,joueur2.nom,joueur2.points);
    }

    //on libere la memoire
    free(joueur1.nom);
    free(joueur2.nom);
    liberer_memoire_liste(&joueur1.debut);
    liberer_memoire_liste(&joueur2.debut);
    liberer_memoire_arbre(&racine);
}

//prend en parametre une lettre
char maj(char lettre)
{
    //si la lettre est en minuscule
    if((lettre>=ASCII_a)&&(lettre<=ASCII_z))
    {
        //on la met en majuscule
        lettre=lettre-(ASCII_a-ASCII_A);
    }
    //on renvoie la lettre
    return lettre;
}

//prend en parametre une position, la grille et le joueur
void jouer_lettre(position* p,char grille[LIGNE][COLONNE],joueur* jcourant)
{
    int i,j;
    int lettre;
    int test;

    do
    {   //le joueur choisit une lettre dans sa liste
        printf("\n\nChoisissez une lettre a jouer dans votre liste : ");
        lettre=saisie_caractere(lettre);
        lettre=maj(lettre);

        //on supprime cette lettre de sa liste
        lettre=supprimer(&(*jcourant).debut,lettre);

    }while(lettre==FIN_DE_CHAINE);
    //tant que le joueur saisit une lettre qu'il ne possede pas

    do
    {
        do
        {
            test=FAUX;

            //le joueur choisit une colonne de la grille ou jouer sa lettre
            printf("\nDans quelle colonne voulez vous placer votre lettre ? ");
            j=nombre(tableau_caracteres(saisie_chaine(stdin)));

            j--;
            //on verifie que la colonne existe
            if((j<0)||(j>(COLONNE-1)))
            {
                printf("\ncolonne non valide! Veuillez recommencer!");
                test=VRAI;
            }
        }while(test==VRAI);//tant que la colonne n'est pas valide

        //on determine la ligne ou sera placee la lettre
        i=ligne(grille,j);

    }while(i==-1);//tant que la colonne choisit est remplie

    //on place la lettre dans la grille
    grille[i][j]=lettre;

    //on releve la position de la lettre dans la grille
    p->i=i;
    p->j=j;
}

//prend en parametre le dictionnaire
void rechercher_dico(pnoeud dico)
{
    char* mot;

    //le joueur saisie un mot
    printf("\nSaisissez le mot recherche : ");
    mot=tableau_caracteres(saisie_chaine(stdin));
    mettre_majuscule(mot);

    //le programme verifie si le mot est dans le dictionnaire
    if(rechercher_mot(dico,mot)==VRAI)
    {
        printf("\nle mot %s est dans le dictionnaire\n",mot);
    }
    else
    {
        printf("\nle mot %s n'est pas dans le dictionnaire\n",mot);
    }
}

//prend en parametre une liste de lettre
void changer_lettres(pliste* debut)
{
    int l;

    l=longueur_liste(*debut);       //on determine le nombre de lettres qu'il possede
    liberer_memoire_liste(debut);   //on supprime ses lettres
    remplissage(debut,l);           //on lui redonne de nouvelles lettres
    printf("\nVoila vos nouvelles lettres :\n\n");
    affichage_liste_lettres(*debut);//on affiche ses nouvelles lettres
}

//prend en parametre un entier
int saisie_caractere(int c)
{
    int saisie;
    int test;

    //tant que l'utilisateur tape entree
    c=getchar();
    while(c==ASCII_ENTREE)
    {
        //on lui demande de saisir un caractere
        c=getchar();
    }
    //on enregistre la saisie
    saisie=c;

    //on test si le joueur entre plus d'un caractere
    test=FAUX;
    while(c!=ASCII_ENTREE)
    {
        c=getchar();
        test++;
    }

    //si le joueur a entre plus d'un caractere
    if(test>1)
    {
        //sa saisie n'est pas correcte
        return FIN_DE_CHAINE;
    }
    //sinon on retourne le caractere saisie
    return(saisie);
}

//prend en parametre un tableau de caracteres
int nombre(char* tab)
{
    int t;
    int i;
    int nombre;

    //on determine la taille du tableau
    i=0;
    while(tab[i]!=FIN_DE_CHAINE)
    {
        i++;
    }
    t=i;

    //on calcul le nombre
    nombre=0;
    for(i=t-1;i>=0;i--)
    {
        nombre=nombre+((tab[i]-ASCII_0)*pow(10,(t-(i+1))));
    }
    //on retourne le nombre
    return(nombre);
}

void tour(joueur* jcourant,joueur autre,char grille[LIGNE][COLONNE],pnoeud racine)
{
    position p;

    //le tour de jeu commence
    printf("\n*******************************************************************************");

    //on identifie le joueur qui va jouer ce tour
    printf("\nC'est a %s de jouer\n",(*jcourant).nom);

    //le joueur decide ce qu'il va faire avec ses lettres
    p=decision(jcourant,grille,racine);

    //si le joueur n'a pas change ses lettres ou passer son tour
    if(p.i!=LIGNE)
    {
        //on contabilise son nombre de points gagnés
        points_gagnes(racine,grille,p,&(*jcourant).points);
    }

    //on affiche les scores des deux joueurs
    printf("\n\nPour l'instant  %s a un score de %d",jcourant->nom,jcourant->points);
    printf(" et %s a un score de %d.",autre.nom,autre.points);
}

//ne prend pas de parametre
void afficher_regles()
{
    FILE* regles;
    char* phrase;

    //on ouvre le fichier contenant les regles du jeu en mode lecture
    regles=fopen(REGLES,"r");

    //on teste l'ouverture
    if(REGLES==NULL)
    {
        fprintf(stderr,"\nErreur d'ouverture du fichier %s",REGLES);
    }

    printf("\n");

    //tant qu'on n'est pas a la fin du fichier
    while(!feof(regles))
    {
        //on recupere les regles du jeu
        phrase=tableau_caracteres(saisie_chaine(regles));
        printf("%s\n",phrase);
        free(phrase);
    }

    //on ferme le fichier
    fclose(regles);
}
