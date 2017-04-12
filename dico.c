/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : dico.c

fonctions permettants la creation et l'utilisation d'un dictionnaire
*/

#include "dico.h"

//prend en parametre l'arbre
void init_racine(pnoeud* racine)
{
    *racine=NULL;
}

//prend en parametre un mot
pnoeud creerNoeud(char* mot)
{
    //on cree le noeud
    pnoeud nouveau=(pnoeud)malloc(sizeof(struct noeud));
    if(mot==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction creerNoeud");
        return(NULL);
    }

    //on remplit ses champs
    nouveau->mot=mot;
    nouveau->gauche=NULL;
    nouveau->droit=NULL;

    //on renvoie l'element cree
    return(nouveau);
}

//prend en parametre l'arbre et un mot
void ajouter_noeud(pnoeud* racine,char* mot)
{
    //si on est au bout de l'arbre
    if(*racine==NULL)
    {
        //on cree le nouveau noeud
        *racine=creerNoeud(mot);
    }

    //si le mot a ajouter est plus petit que le mot du noeud
    else if(strcmp(mot,(*racine)->mot)<0)
    {
        //on va a gauche
        ajouter_noeud(&(*racine)->gauche,mot);
    }

    //si le mot a ajouter est plus grand que le mot du noeud
    else if(strcmp(mot,(*racine)->mot)>0)
    {
        //on va a droite
        ajouter_noeud(&(*racine)->droit,mot);
    }
}

//prend en parametre l'arbre
void creerDico(pnoeud* racine)
{
    FILE* mots;
    char* mot;

    //on initialise le dictionnaire
    init_racine(racine);

    //on ouvre le fichier contenant les mots en mode lecture
    mots=fopen(MOTS,"r");

    if(mots==NULL)
    {
        fprintf(stderr,"\nErreur d'ouverture du fichier %s",MOTS);
    }

    //tant qu'on n'est pas a la fin du fichier
    while(!feof(mots))
    {
        //on recupere le mot
        mot=tableau_caracteres(saisie_chaine(mots));

        //on le met en majuscule
        mettre_majuscule(mot);

        //si le mot est valide et qu'il n'est pas deja dans le dictionnaire
        if((*mot!=FIN_DE_CHAINE)&&(rechercher_mot(*racine,mot)!=VRAI))
        {
            //on l'ajoute dans le dictionnaire
            ajouter_noeud(racine,mot);
        }
    }

    //on ferme le fichier
    fclose(mots);
}

//prend en parametre l'arbre et un mot
int rechercher_mot(pnoeud racine,char* mot)
{
    //si on est au bout de l'arbre
    if(racine==NULL)
    {
        //le mot n'a pas ete trouve
        //on retourne FAUX
        return FAUX;
    }

    //si le mot a ete trouve
    else if(strcmp(racine->mot,mot)==0)
    {
        //on retourne VRAI
        return VRAI;
    }

    //si le mot recherche est plus petit que le mot du noeud
    else if(strcmp(racine->mot,mot)>0)
    {
        //on va a gauche
        return(rechercher_mot(racine->gauche,mot));
    }

    //sinon on va a droite
    return(rechercher_mot(racine->droit,mot));
}

//prend en parametre l'arbre
void liberer_memoire_arbre(pnoeud* racine)
{
    if (*racine!=NULL)
    {
        liberer_memoire_arbre(&(*racine)->gauche);
        liberer_memoire_arbre(&(*racine)->droit);
        free((*racine)->mot);
        free(*racine);
    }
}

//prend en parametre un mot
void mettre_majuscule(char* mot)
{
    int i;
    int k;
    i=0;

    //tant qu'on n'est pas a la fin du mot et que le mot est valide
    while((mot[i]!=FIN_DE_CHAINE)&&(*mot!=FIN_DE_CHAINE))
    {
        //si la lettre est en minuscule
        if((mot[i]>=ASCII_a)&&(mot[i]<=ASCII_z))
        {
            //on la met en majuscule
            mot[i]=mot[i]-(ASCII_a-ASCII_A);
        }

        //sinon si la lettre n'est ni en majuscule ni en minuscule
        else if(!(mot[i]>=ASCII_A)&&(mot[i]<=ASCII_Z))
        {
            //on traite les differents cas

            if((mot[i]=='ë')||(mot[i]=='ê')||(mot[i]=='é')||(mot[i]=='è')||(mot[i]=='Ë')||(mot[i]=='É')||(mot[i]=='È'))
            {
                mot[i]='E';
            }
            else if((mot[i]=='ï')||(mot[i]=='î')||(mot[i]=='Ï')||(mot[i]=='Î'))
            {
                mot[i]='I';
            }
            else if((mot[i]=='â')||(mot[i]=='à')||(mot[i]=='Â'))
            {
                mot[i]='A';
            }
            else if((mot[i]=='ô')||(mot[i]=='Ô'))
            {
                mot[i]='O';
            }
            else if((mot[i]=='û')||(mot[i]=='ù'))
            {
                mot[i]='U';
            }
            else if((mot[i]=='ç')||(mot[i]=='Ç'))
            {
                mot[i]='C';
            }
            else if((mot[i]=='œ')||(mot[i]=='Œ'))
            {
                k=i;
                while(mot[k]!=FIN_DE_CHAINE)
                {
                    k++;
                }
                while(k>=i)
                {
                    mot[k+2]=mot[k+1];
                    k--;
                }
                mot[i]='O';
                mot[i+1]='E';
            }

            //si le caractere est inconnu
            else
            {
                //le mot n'est plus valide
                *mot=FIN_DE_CHAINE;
            }
        }

        //on passe a la lettre suivante
        i++;
    }
}
