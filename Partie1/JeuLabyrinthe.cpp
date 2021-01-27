#include <iostream>

#define L 11 // Nombre de COLONNES du tableau
#define M 10 // Nombre de LIGNES du tableau

#define AFF_VIDE '-'  //Caractère représentant les cases vides pour l’affichage
#define AFF_MUR  'X'  //Caractère représentant les murs pour l’affichage
#define AFF_BORD ' '  //Caractère représentant les bords pour l’affichage

char Grille[L*M] = {0};  // Tableau global contenant les caractères servant à afficher le labyrinthe

using namespace std;

//retourne l'identifiant d'une case dont on donne les coordonnées
int getID(int ligne, int colonne)
{
    return(ligne*L + colonne);
}

//retourne la première coordonnée (ligne) d'une case dont on donne l'identifiant
int getLigne(int id)
{
    return(id/L);
}

//retourne la deuxième coordonnée (colonne) d'une case dont on donne l'identifiant
int getColonne(int id)
{
    return(id%L);
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
    for(int i = -1 ; i <= M ; i++)
    {
        for(int j = -1 ; j <= L ; j++)
        {
            if((i == -1) | (j == -1) | (i == M) | (j == L))
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
    
    return 0;
}
