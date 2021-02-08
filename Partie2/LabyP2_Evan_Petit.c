/*
LA COMMANDE POUR COMPILER EST :
gcc -Wall JeuLabyrinthe.c -o JeuLabyrinthe.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int NB_COLONNES = 25; // Nombre de COLONNES du tableau
int NB_LIGNES = 25; // Nombre de LIGNES du tableau

char AFF_VIDE = '-';  //Caractère représentant les cases vides pour l’affichage
char AFF_MUR = 'X';  //Caractère représentant les murs pour l’affichage
char AFF_BORD = ' ';  //Caractère représentant les bords pour l’affichage

char* Grille=NULL;  // Tableau global contenant les caractères servant à afficher le labyrinthe

int* Pile = NULL;
int Sommet = -1;

// # GESTION DE LA PILE

// Empile un entier
void push(int x)
{
    Sommet++;
    Pile[Sommet] = x;
}

// Dépile un entier et le retourne
int pop()
{
    int buff = Pile[Sommet];
    Pile[Sommet] = 0;
    Sommet--;
    return buff;
}

// Afficher la pile
void affichePile()
{
    if(Sommet > -1)
        for(int i = 0 ; i <= Sommet ; i++)
            printf("|  %d  |\n",Pile[i]);
    else
        printf("Pile vide\n");
}


// # GESTION DE LA GRILLE

//retourne l'identifiant d'une case dont on donne les coordonnées
int getID(int ligne, int colonne)
{
    return(ligne*NB_COLONNES + colonne);
}

//retourne la première coordonnée (ligne) d'une case dont on donne l'identifiant
int getLigne(int id)
{
    return(id/NB_COLONNES);
}

//retourne la deuxième coordonnée (colonne) d'une case dont on donne l'identifiant
int getCol(int id)
{
    return(id%NB_COLONNES);
}

//place la valeur x dans le case de coordonnée (i,j)
void modifie(int ligne, int colonne, char x)
{
    Grille[getID(ligne,colonne)]=x;
}

//retourne la valeur de la case de coordonnées (i,j)
char lit(int ligne, int colonne)
{
    return Grille[getID(ligne,colonne)];
}

// Retourne la taille de la grille
int getTaille()
{
    return NB_COLONNES*NB_LIGNES;
}

// Retourne le nombre de cases blanches
int getBlanches()
{
    // Compte le nombre de cases blanches dans la grille
    int blanches = 0;
    for(int i = 0 ; i < NB_LIGNES ; i++)
    {
        for(int j = 0 ; j < NB_COLONNES ; j++)
        {
            if (lit(i,j) == 0)
            {
                blanches++;
            }
        }
    }
    return blanches;
}

// Retourne l'id d'une case blanche aléatoire
int getRandBlanche()
{
    int flag = 0;
    int id = -1;
    int duree = 0;
    while(flag == 0 && duree < 1000000)
        {
            id = (rand() % ((NB_COLONNES * NB_LIGNES)-2)+1);
            if(Grille[id] == 0) flag = 1;
            duree++;
        }
    
    return id;

    /*int j = 0;
    int taille = getBlanches();
    int blanches[taille] ;
    for(int i = 0 ; i<(NB_COLONNES*NB_LIGNES) ; i++)
    {
        if (Grille[i] == 0)
        {
            blanches[j] = i;
            j++;
        }   
        
    }

    int id = (rand() % ((taille-2)+1));
    return blanches[id];*/
}

// Marque une case dont on passe l'id en paramètre (vaut 2 dans grille et est empilée)
void marque(int id)
{
    modifie(getLigne(id),getCol(id),2);
    push(id);
}

// Détermine si toutes les cases blanches sont connectées
int connexe()
{
    // ## DEBUT SEQUENCE
    int id = 0;

    if(getBlanches() == 0) 
        printf("ATTENTION - IL N'Y A AUCUNE CASE BLANCHE!"); 
    else
    {
        int flag = 0;
        while((id < NB_COLONNES*NB_LIGNES) && (flag == 0))
        {
            if(Grille[id] == 0)
            {
                flag = 1;
            }
            else id++;
        }
        marque(id);
    }

    while(Sommet >= 0)
    {    
        id = pop();
        int idCol = getCol(id);
        int idLig = getLigne(id);
        
        if((idLig > 0) && (lit(idLig - 1 , idCol) == 0)) marque(getID(idLig - 1 , idCol));// Haut
        if((idLig < NB_LIGNES - 1) && (lit(idLig + 1 , idCol) == 0)) marque(getID(idLig + 1 , idCol));// Bas
        if((idCol > 0) && (lit(idLig , idCol - 1) == 0)) marque(getID(idLig , idCol - 1));// Gauche
        if((idCol < NB_COLONNES - 1) && (lit(idLig , idCol + 1) == 0)) marque(getID(idLig , idCol + 1));// Droite
    }

    int marques = 0 ;
    for(int i = 0 ; i < NB_LIGNES ; i++)
    {
        for(int j = 0 ; j < NB_COLONNES ; j++)
        {
            if(lit(i,j) == 2)
            {
                modifie(i,j,0);
                marques++;
            }
        }
    }

    
    // Drapeau. 0 si non connexe, 1 si connexe, 2 si erreur (plus de marquées que de blanches).
    int flag = 0;
    if(marques == getBlanches()) flag = 1;
    if(marques > getBlanches()) flag = 2;

    return flag;
    
}


void genLaby(int k)
{
    int duree = 1000000;
    int flag = 0;
    int i = 0;
    int id = -1;
    double marge = 0.1; // marge d'erreur que l'on s'autorise

    while((i < duree) && (flag == 0))
    {
        int id = getRandBlanche();
        Grille[id] = 1;
        if(connexe() == 0)
            Grille[id] = 0;
        if((getBlanches() >= ((1-marge/2)*k) && (getBlanches() <= ((1+marge/2))*k)))
            {
                flag = 1;
            }
        i++;
    }
    printf("Nombre d'operations = %d\n",i);
    if(i>=duree)
    {
        printf("NOMBRE D'OPERATIONS DEPASSE! SORTIE DU PROGRAMME");
        exit(0);
    }
}

//affiche la grille
void affiche()
{
    char vide = AFF_VIDE; // On récupère le #define contenant le caractère vide
    char mur = AFF_MUR; // On récupère le #define contenant le caractère mur
    char bord = AFF_BORD; // On récupère le #define contenant le caractère bord
    char marque = 'o';

    // Affichage caractère par caractère en bouclant sur le tableau
    for(int i = -1 ; i <= NB_LIGNES ; i++)
    {
        for(int j = -1 ; j <= NB_COLONNES ; j++)
        {
            if((i == -1) | (j == -1) | (i == NB_LIGNES) | (j == NB_COLONNES))
                printf("%c",bord);

            else
            {
                if(lit(i,j) == 0) 
                    printf("%c",vide);

                if(lit(i,j) == 1)
                    printf("%c",mur);

                if(lit(i,j) == 2)
                    printf("%c",marque);
            }
        }
        printf("\n");
    }
}

int main()
{
    system("cls");
    Grille = (char*)calloc(NB_LIGNES*NB_COLONNES,sizeof(char));
    Pile = (int*)calloc(NB_LIGNES*NB_COLONNES,sizeof(int));

    int taille = 350;

    srand((unsigned)time(NULL));
    genLaby(taille);
    affiche();

    printf("Cases blanches : %d  |  lambda = %d\nConnexite (1 oui | 0 non) : %d",getBlanches(),taille,connexe());

    free(Grille);
    free(Pile);

    return 0;
}
