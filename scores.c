/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : score.c

fonctions permettants la creation et le traitement d'une liste de scores
*/

#include "scores.h"

//prend en parametre une liste de scores
void init_score(pliste_scores* debut)
{
    *debut=NULL;
}

//prend en parametres une liste de scores et un score
pliste_scores creerVD_score(pliste_scores debut,score s)
{
    //on cree un nouvel element pour la liste de score
    pliste_scores nouveau=(pliste_scores)malloc(sizeof(struct liste_scores));
    if(nouveau==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction creerVD_score");
        return(NULL);
    }

    //on remplit ses champs
    nouveau->meilleur.points=s.points;
    nouveau->meilleur.nom=s.nom;
    nouveau->suivant=debut;

    //on retourne le nouvel element cree
    return(nouveau);
}

//prend en parametre une liste de score
void stocker_score(pliste_scores* debut)
{
    FILE* liste_scores;
    score s;

    //on initialise la liste des scores
    init_score(debut);

    //on ouvre le fichier contenant les scores en mode lecture
    liste_scores=fopen(SCORES,"r");

    if(liste_scores==NULL)
    {
        fprintf(stderr,"\nErreur d'ouverture du fichier %s",SCORES);
    }

    //tant qu'on n'est pas a la fin du fichier
    while(!feof(liste_scores))
    {
        //on recupere le nom du joueur
        s.nom=tableau_caracteres(saisie_chaine(liste_scores));
        //ainsi que son nombre de points gagne
        fscanf(liste_scores,"%d\n",&s.points);

        //si le fichier n'est pas vide
        if(s.nom[0]!=FIN_DE_CHAINE)
        {
            //on ajoute le score saisi dans la liste des scores
           *debut=creerVD_score(*debut,s);
        }
    }

    //on ferme le fichier contenant les scores
    fclose(liste_scores);
}

//prend en parametre une liste de scores
void affichage_scores(pliste_scores debut)
{
    pliste_scores courant;

    courant=debut;
    printf("\n");

    //si la liste de scores est vide
    if(courant==NULL)
    {
        //il n'y a pas de scores enregistres
        printf("\t\t\t\tAucun score\n");
    }

    //sinon
    else
    {
        //on trie la liste des scores dans l'ordre decroissant des nombres de points
        trier_scores(&debut);

        //on affiche la liste des scores
        courant=debut;
        printf("\n\n\t\t\t************SCORES************\n");
        printf("\t\t\t*                            *\n");
        while(courant!=NULL)
        {
            printf("\t\t\t*%-21s     %.2d*\n",courant->meilleur.nom,courant->meilleur.points);
            courant=courant->suivant;
        }
        printf("\t\t\t*                            *\n");
        printf("\t\t\t******************************\n\n");
    }
}

//prend en parametres une liste de scores, une chaine de caractere et un entier
void ajouter_scores(pliste_scores* debut,char* nom,int points)
{
    FILE* liste_scores;
    pliste_scores courant;

    //on recupere les scores
    stocker_score(debut);

    //si il y a moins de 10 scores dans la liste
    if(longueur_liste_scores(*debut)<NOMBRE_SCORES)
    {
        //on ouvre le fichier contenant les scores en mode ecriture a la fin
        liste_scores=fopen(SCORES,"a");

        //on rajoute le nouveau score dans le fichier
        fprintf(liste_scores,"\n%s",nom);
        fprintf(liste_scores,"\n%d",points);

        //on ferme le fichier
        fclose(liste_scores);
    }

    //si il y a 10 scores ou plus dans la liste
    else
    {
        //on trie les scores dans l'ordre decroissant
        trier_scores(debut);

        //si le score le plus petit de la liste est inferieur au nouveau score
        if(dernier_score(*debut)->meilleur.points<points)
        {
            //on ajoute le nouveau score dans la liste
            dernier_score(*debut)->meilleur.points=points;
            dernier_score(*debut)->meilleur.nom=nom;

            //on trie la nouvelle liste
            trier_scores(debut);

            //on ouvre le fichier contenant les scores en mode ecriture
            liste_scores=fopen(SCORES,"w");

            //on enregiste la nouvelle liste des score dans le fichier
            courant=*debut;
            while(courant!=NULL)
            {
                fprintf(liste_scores,"%s\n",courant->meilleur.nom);
                fprintf(liste_scores,"%d\n",courant->meilleur.points);
                courant=courant->suivant;
            }

            //on ferme le fichier
            fclose(liste_scores);
        }
    }
}

//prend en parametre une liste de scores
int longueur_liste_scores(pliste_scores debut)
{
    pliste_scores courant;
    int nb_scores;

    //on determine le nombre de scores dans la liste
    courant=debut;
    nb_scores=0;
    while(courant!=NULL)
    {
        nb_scores++;
        courant=courant->suivant;
    }
    //on retourne le nombre de scores
    return(nb_scores);
}

//prend en parametre une liste de scores
void trier_scores(pliste_scores* debut)
{
    int n;
    int i;
    pliste_scores courant;
    score* tab;

    //on cree un tableau de la meme taille que la liste pris en parametre
    n=longueur_liste_scores(*debut);
    tab=(score*)malloc(n*sizeof(score));

    if(tab==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction trier_scores");
    }

    //on remplie le tableau avec les elements de la liste
    courant=*debut;
    for(i=0;i<n;i++)
    {
        tab[i]=courant->meilleur;
        courant=courant->suivant;
    }

    //on detruit la liste
    vider_liste_scores(debut);

    //on trie le tableau
    trier_tableau(tab,n);

    //on remplie la liste avec les valeurs triees du tableau
    for(i=0;i<n;i++)
    {
        *debut=creerVD_score(*debut,tab[i]);
    }

    //on detruit le tableau
    free(tab);
}

//prend en parametre un tableau de scores et sa taille
void trier_tableau(score* tab,int n)
{
    //on utilise un tri a bulle
    //on veut trier le tableau dans l'ordre croissant des scores

    int i;
    int booleen;

    do
    {
        booleen=FAUX;
        //on parcour le tableau
        for(i=0;i<n-1;i++)
        {
            //si un score est plus grand que le score suivant
            if(tab[i].points>tab[i+1].points)
            {
                //on les echange
                echanger(&tab[i],&tab[i+1]);
                booleen=VRAI;
            }
        }
    }while(booleen==VRAI);
    //tant qu'il y a eu des echange
}

//prend en parametres deux elements de type score
void echanger(score* a,score* b)
{
    score c;
    c=*a;
    *a=*b;
    *b=c;
}

//prend en parametre une liste de scores
void vider_liste_scores(pliste_scores* debut)
{
    pliste_scores supp;

    //tant qu'on n'est pas au bout de la liste
    while(*debut != NULL)
    {
        //on detruit chaque element
        supp=*debut;
        *debut=(*debut)->suivant;
        free(supp);
    }
}

//prend en parametre une liste de score
pliste_scores dernier_score(pliste_scores debut)
{
    pliste_scores courant;
    courant=debut;

    //on parcour la liste jusqu'au bout
    while(courant->suivant!=NULL)
    {
        courant=courant->suivant;
    }

    //on retourne le dernier element de la liste
    return(courant);
}
