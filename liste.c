/*
BERLIN Alexandre
Premiere annee
groupe AA
encadrant : Mme Longo
projet : PUISSANCE MOT

fichier : liste.c

fonctions permettants la creation et le traitement d'une liste de lettres
*/

#include "liste.h"

//ne prend aucun parametre
char tirage_lettre()
{
    int i;          //compteur
    char tab[ALPHABET];    //tableau de caracteres

    for(i=0;i<ALPHABET;i++)
    {
        tab[i]=i+ASCII_A;
    }//on remplit le tableau avec chacune des lettres de l'alphabet

    i=(rand()%ALPHABET);//fonction retournant un chiffre entre 0 et 25
    return(tab[i]); //retourne le caractere a la i eme position du tableau
}

//prend une liste de lettre en parametre
void init(pliste* debut)
{
    *debut=NULL;
}

//prend le debut de la liste en parametre
pliste creerVD(pliste debut)
{
    pliste nouveau=(pliste)malloc(sizeof(struct liste));//allocation d'une zone memoire pointee par nouveau
    if(nouveau==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction creerVD");
        return(NULL);
    }
    nouveau->lettre=tirage_lettre();//on rentre un caractere dans l'element cree
    nouveau->suivant=debut;//on l'insere au debut
    return(nouveau);//on renvoie nouveau
}

//prend une liste de lettre en parametre
void ajoutdebut(pliste* debut)
{
    *debut=creerVD(*debut);
}

//prend le debut de la liste en parametre
void remplissage(pliste* debut,int l)
{
    int i;
    init(debut);//on initialise debut a NULL
    for(i=0;i<l;i++)
    {
        ajoutdebut(debut);//on ajoute un element au debut de la liste B fois
    }
}

//procedure d'affichage de la liste
void affichage_liste_lettres(pliste debut)//prend le debut de la liste en parametre
{
    pliste courant;//creation d'un pointeur de type pliste
    courant=debut;//on initialise courant a debut
    while(courant!=NULL)//tant qu'on est pas a la fin de la liste
    {
        printf("%c ",courant->lettre);//on affiche le caractere pointe par courant
        courant=courant->suivant;//on passe a l'element suivant
    }
}

//prend le debut de la liste et le caractere recherche
int supprimer(pliste* debut,int lettre)
{
    pliste courant,supp;
    pliste precedent=NULL;//creation et initialisation d'un pointeur de type pliste a NULL
    int test;//variable booleenne

    courant=*debut;
    test=FAUX;//test vaut faux
    while((courant!=NULL)&&(test==FAUX))
    {
        if(courant->lettre==lettre)//si on trouve la lettre
        {
            test=VRAI;//test vaut vrai
        }
        else//sinon on passe a l'element suivant
        {
            precedent=courant;
            courant=courant->suivant;
        }
    }
    if(courant==*debut)//si courant est reste au debut
    {
        supp=*debut;
        lettre=(*debut)->lettre;//on recupere la lettre du debut de la liste
        *debut=(*debut)->suivant;//l'element suivant devient le debut de la liste
        free(supp);//on supprime l'element
    }
    else if(courant==NULL)//sinon si courant est a la fin de la liste
    {
        printf("\nlettre non trouvee!");//on a pas trouve le caractere recherche
        lettre=FIN_DE_CHAINE;//on modifie lettre avec un caractere special
    }
    else//sinon pour les autres valeurs de courant
    {
        supp=precedent->suivant;
        lettre=courant->lettre;
        precedent->suivant=courant->suivant;
        free(supp);
    }
    return(lettre);//on retourne la lettre de l'element supprimer
}

//prend le debut de la liste
void liberer_memoire_liste(pliste* debut)
{
    pliste supp;
    while(*debut != NULL)//tant qu'il y a des elements dans la liste
    {
        supp=*debut;
        *debut=(*debut)->suivant;
        free(supp);//on les supprimes
    }
}

//prend en parametre une liste de lettres
int longueur_liste(pliste debut)
{
    pliste courant;
    int nb_lettres;

    //determination du nombre de lettres dans la liste
    courant=debut;
    nb_lettres=0;
    while(courant!=NULL)
    {
        nb_lettres++;
        courant=courant->suivant;
    }
    //on retourne le nombre de lettres
    return(nb_lettres);
}

//prend en parametres deux liste de lettres
int listes_vides(pliste debut1, pliste debut2)
{
    int test;
    //on part du principe que les listes ne sont pas vides
    //test vaut faux
    test=FAUX;

    //soit une des deux listes est vide
    if((debut1==NULL)&&(debut2!=NULL))
    {
        //test vaut vrai
        test=VRAI;
        printf("\n\nLe joueur 1 n'a plus de lettres.");
    }
    if((debut1!=NULL)&&(debut2==NULL))
    {
        //test vaut vrai
        test=VRAI;
        printf("\n\nLe joueur 2 n'a plus de lettres.");
    }

    //soit les deux listes sont vides
    else if((debut1==NULL)&&(debut2==NULL))
    {
        //test vaut vrai
        test=VRAI;
        printf("\n\nLes deux joueurs n'ont plus de lettres.");
    }

    //on renvoie vrai ou faux
    return(test);
}

//prend en parametres une liste de lettre et un caractere
void ajouter_fin(pliste* debut,char l)
{
    //on cree le nouvel element a ajouter dans la liste
    pliste courant;
    pliste nouveau=(pliste)malloc(sizeof(struct liste));
    nouveau->lettre=l;
    nouveau->suivant=NULL;

    courant=*debut;
    //si la liste n'est pas vide
    if(courant!=NULL)
    {
        //on ajoute le nouvel element a la fin de la liste
        while(courant->suivant!=NULL)
        {
            courant=courant->suivant;
        }
        courant->suivant=nouveau;
    }
    //si la liste est vide
    else
    {
        //on ajoute le nouvel element au debut de la liste
        *debut=nouveau;
    }
}

//prend en parametre un fichier
pliste saisie_chaine(FILE* fichier)
{
    int c;
    pliste saisie;

    //on initialise une liste de lettre
    init(&saisie);

    //tant que l'utilisateur tape entree
    c=fgetc(fichier);
    while(c==ASCII_ENTREE)
    {
        //on lui demande de saisir un caractere
        c=fgetc(fichier);
    }

    //tant que l'utilisateur ne tape pas entree
    //et qu'on n'est pas a la fin du fichier
    while((c!=ASCII_ENTREE)&&(c!=EOF))
    {
        //on ajoute le caractere saisie dans la liste de lettres
        ajouter_fin(&saisie,c);
        c=fgetc(fichier);
    }
    //on retourne la saisie de l'utilisateur
    return(saisie);
}

//prend en parametre une liste de lettres
char* tableau_caracteres(pliste saisie)
{
    int i;
    pliste courant;

    //on cree un mot dont la taille est celle de la saisie
    //plus 1 car on devra rajouter le caractere de fin de chaine
    char* mot;
    mot=malloc(longueur_liste(saisie)+1);

    if(mot==NULL)
    {
        fprintf(stderr,"\nErreur d'allocation memoire dans la fonction tableau_caracteres");
        return(NULL);
    }

    //on remplit le mot avec les caracteres de la saisie
    i=0;
    courant=saisie;
    while(courant!=NULL)
    {
        mot[i]=courant->lettre;
        courant=courant->suivant;
        i++;
    }

    //on efface la saisie
    liberer_memoire_liste(&saisie);

    //on rajoute le caractere de fin de chaine a la fin du mot
    mot[i]=FIN_DE_CHAINE;

    //on renvoie le mot
    return(mot);
}
