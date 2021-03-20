#include <stack>
#include <vector>
#include <Windows.h>
#include <queue>

#include "Labyrinthe.h"

Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
    this->lig = nLignes;
    this->col = nColonnes;
    this->grille.resize(lig*col,0);
}

Labyrinthe::Labyrinthe(char data[])
{

}

Labyrinthe::~Labyrinthe()
{
    this->grille.clear();
}

int Labyrinthe::getLongueur()
{
    return this->lig;
}

int Labyrinthe::getLargeur()
{
    return this->col;
}

int Labyrinthe::getTaille()
{
    return this->col*this->lig;
}

int Labyrinthe::getID(int ligne, int colonne)
{
    return this->col*ligne+colonne;
}

int Labyrinthe::getLigne(int id)
{
    return id/this->col;
}

int Labyrinthe::getCol(int id)
{
    return id%this->col;
}

void Labyrinthe::modifie(int ligne, int colonne, char x)
{
    this->grille[getID(ligne,colonne)] = x;
}

void Labyrinthe::modifie(int id, char x)
{
    this->grille[id] = x;
}

char Labyrinthe::lit(int ligne, int colonne)
{
    return this->grille[getID(ligne,colonne)];
}

char Labyrinthe::lit(int id)
{
    return this->grille[id];
}

int Labyrinthe::getBlanches()
{
    // Compte le nombre de cases blanches dans la grille
    int blanches = 0;
    for(int i = 0 ; i < this->lig ; i++)
    {
        for(int j = 0 ; j < this->col ; j++)
        {
            if (lit(i,j) == 0)
            {
                blanches++;
            }
        }
    }
    return blanches;
}

int Labyrinthe::getRandBlanche()
{
    int flag = 0;
    int id = -1;
    int duree = 0;
    while(flag == 0 && duree < 1000000)
        {
            id = (rand() % ((this->col * this->lig)-2)+1);
            if(this->lit(id) == 0) flag = 1;
            duree++;
        }
    
    return id;
}

void Labyrinthe::affiche()
{
    string res = "";
    char vide = '.';
    char mur = 'X'; 
    char bord = 'O';

    // Affichage caractère par caractère en bouclant sur le tableau
    for(int i = -1 ; i <= lig ; i++)
    {
        for(int j = -1 ; j <= col ; j++)
        {
            if((i == -1) | (j == -1) | (i == lig) | (j == col))
                res = res+bord;

            else
            {
                if(lit(i,j) == 0) 
                    res=res+vide;

                if(lit(i,j) == 1)
                    res=res+mur;

                if(lit(i,j) > 1)
                    res=res+to_string((int)lit(i,j)-2).back();
            }
        }
        res = res+'\n';
    }
    res[this->col+3]=' ';
    res[res.size()-(this->col+5)]=' ';
    cout << res << endl;
}

bool Labyrinthe::connexe()
{
    // ## DEBUT SEQUENCE
    int id = 0;
    stack <int> pile;

    if(getBlanches() == 0) 
        printf("ATTENTION - IL N'Y A AUCUNE CASE BLANCHE!"); 
    else
    {
        int flag = 0;
        while((id < this->lig*this->col) && (flag == 0))
        {
            if(this->lit(id) == 0)
            {
                flag = 1;
            }
            else id++;
        }
        this->modifie(id,2);
        pile.push(id);
    }


    while(!(pile.empty()))
    {   
        id = pile.top();
        pile.pop();
        int idCol = getCol(id);
        int idLig = getLigne(id);
        
        if((idLig > 0) && (lit(idLig - 1 , idCol) == 0)) // Haut
        {
            this->modifie(idLig-1,idCol,2);
            pile.push(getID(idLig-1,idCol));
        }

        if((idLig < this->lig - 1) && (lit(idLig + 1 , idCol) == 0)) // Bas
        {
            this->modifie(idLig+1,idCol,2);
            pile.push(getID(idLig+1,idCol));
        }

        if((idCol > 0) && (lit(idLig , idCol - 1) == 0)) // Gauche
        {
            this->modifie(idLig,idCol-1,2);
            pile.push(getID(idLig,idCol-1));
        }

        if((idCol < this->col - 1) && (lit(idLig , idCol + 1) == 0)) // Droite
        {
            this->modifie(idLig,idCol+1,2);
            pile.push(getID(idLig,idCol+1));
        }
    }

    int marques = 0 ;
    for(int i = 0 ; i < this->getTaille(); i++)
    {
        if(lit(i) == 2)
        {
            modifie(i,0);
            marques++;
        }
    }

    
    // Drapeau. 0 si non connexe, 1 si connexe, 2 si erreur (plus de marquées que de blanches).
    bool flag = false;
    if(marques == getBlanches()) flag = true;

    return flag;
    
}

void Labyrinthe::genLaby(int nb)
{
    int duree = 1000000;
    int flag = 0;
    int i = 0;
    double marge = 0.1; // marge d'erreur que l'on s'autorise
    int k = nb; // taille souhaitée

    while((i < duree) && (flag == 0))
    {
        int id = getRandBlanche();
        this->modifie(id,1);
        if(connexe() == 0)
            this->modifie(id,0);
        if((getBlanches() >= ((1-marge/2)*k) && (getBlanches() <= ((1+marge/2))*k)))
            {
                flag = 1;
            }
        i++;
    }
    printf("Amount of operations = %d\n",i);

    if(i>=duree)
    {
        printf("NOMBRE D'OPERATIONS DEPASSE! SORTIE DU PROGRAMME");
        exit(0);
    }
}

int Labyrinthe::distMin(int id1, int id2)
{
    queue<int> file;
    int res = 1;
    int id; 
    boolean flag = false;
    vector<int> compte;
    compte.resize(this->getTaille());

    if( (lit(id1) == 1) || (lit(id2) == 1) )
        res = -1;
    else
    {
        file.push(id1);
        compte[id1] = res;

        while(!(file.empty()) && (flag == false))
        {
            id = file.front();
            file.pop();

            if(id == id2)
            {
                res = compte[id];
                flag = true;
            }

            int idCol = getCol(id);
            int idLig = getLigne(id);

            if((idLig > 0) && (lit(idLig - 1 , idCol) == 0) && ( compte[getID(idLig-1,idCol)] == 0 ) ) // Haut
            {
                file.push(getID(idLig-1,idCol));
                compte[getID(idLig-1,idCol)] = compte[id]+1;
            }

            if((idLig < this->lig - 1) && (lit(idLig + 1 , idCol) == 0) && ( compte[getID(idLig+1,idCol)] == 0 )) // Bas
            {
                file.push(getID(idLig+1,idCol));
                compte[getID(idLig+1,idCol)] = compte[id]+1;
            }

            if((idCol > 0) && (lit(idLig , idCol - 1) == 0) && ( compte[getID(idLig,idCol-1)] == 0 )) // Gauche
            {
                file.push(getID(idLig,idCol-1));
                compte[getID(idLig,idCol-1)] = compte[id]+1;
            }

            if((idCol < this->col - 1) && (lit(idLig , idCol + 1) == 0) && ( compte[getID(idLig,idCol+1)] == 0 )) // Droite
            {
                file.push(getID(idLig,idCol+1));
                compte[getID(idLig,idCol+1)] = compte[id]+1;
            }

        }
    }

    return res;

}
