#include <iostream>
#define COL 4
#define LIG 3
char grille[COL*LIG] = {0};

using namespace std;

int getID(int ligne, int colonne){
    return(ligne*COL + colonne);
}

int getLigne(int id){
    return(id/COL);
}

int getColonne(int id){
    return(id%COL);
}

void modifie(int ligne, int colonne, char x){
    grille[getID(ligne,colonne)]=x;
}

char lit(int ligne, int colonne){
    return grille[getID(ligne,colonne)];
}

int main(){
    printf("id %d :  (%d  %d)\n", getID(1,2) , getLigne(6), getColonne(6));
    printf("Case 2,3 : %d\n", lit(2,3));
    modifie(2,3,1);
    printf("Case 2,3 apres modif : %d\n", lit(2,3));
    return 0;
}
