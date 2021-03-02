/*
LA COMMANDE POUR COMPILER EST :
gcc -Wall LabyP1_Evan_Petit.c -o LabyP1.exe
*/

#include <stdio.h>
#include <stdlib.h>

int NB_COLONNES = 6; // Nombre de COLONNES du tableau
int NB_LIGNES = 4; // Nombre de LIGNES du tableau

char AFF_VIDE = '-';  //Caractère représentant les cases vides pour l’affichage
char AFF_MUR = 'X';  //Caractère représentant les murs pour l’affichage
char AFF_BORD = ' ';  //Caractère représentant les bords pour l’affichage

char* Grille=NULL;  // Tableau global contenant les caractères servant à afficher le labyrinthe

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

//affiche la grille
void affiche()
{
    char vide = AFF_VIDE; // On récupère le #define contenant le caractère vide
    char mur = AFF_MUR; // On récupère le #define contenant le caractère mur
    char bord = AFF_BORD; // On récupère le #define contenant le caractère bord

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
            }
        }
        printf("\n");
    }
}

int main()
{
    Grille = (char*)calloc(NB_LIGNES*NB_COLONNES,sizeof(char));
    modifie(1,1,1);
    modifie(1,2,1);
    modifie(2,9,1);
    modifie(3,10,1);
    modifie(5,2,1);
    modifie(5,3,1);
    modifie(7,8,1);
    modifie(8,8,1);
    modifie(9,8,1);
    modifie(10,8,1);
    affiche();

    free(Grille);
    
    return 0;
}
