/*
NOM : EVAN PETIT
LA COMMANDE POUR COMPILER EST :
g++ -Wall Labyrinthe.cpp -o Labyrinthe.exe
POUR EXECUTER ./labyrinthe

Le sujet ne demandait pas de mettre en place des tests pour la partie 4B, je ne l'ai donc pas fait.

CONTRIBUTION PERSONNELLE :
Elle consiste à générer un labyrinthe en utilisant un algorithme plus poussé que celui utilisé précédement.
Elle utilise des notions de backtracking, et permet de générer des labyrinthes parfait (connexe, un seul chemin vers la sortie)
La méthode permettant de le générer est contenue dans la fonction genLabyBack(), bien commentée.
Distmin fonctionne aussi dans ces labyrinthes.


POUR TESTER LA CONTRIBUTION PERSONNELLE, COLLER DANS LE MAIN :
int lignes = <valeur> // nombre de colonnes (un mur + une cellule = une colonne)
int colonnes = <valeur> // nombre de lignes  (un mur + une cellule = une ligne)
Labyrinthe* lab = new Labyrinthe(lignes, colonnes);
lab->genLabyBack();
lab->affiche();
*/

#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include <ctime>
using namespace std;

class Labyrinthe
{
    private:
        vector<char> grille;
        int lig;
        int col;

    public:
        Labyrinthe(int nLignes, int nColonnes);
        Labyrinthe(char data[]);
        ~Labyrinthe();
        int getLongueur();
        int getLargeur();
        int getTaille();
        int getID(int ligne, int colonne);
        int getLigne(int id);
        int getCol(int id);
        void modifie(int ligne, int colonne, char x);
        void modifie(int id, char x);
        char lit(int ligne, int colonne);
        char lit(int id);
        int getBlanches();
        int getRandBlanche();
        void affiche();
        bool connexe();
        void genLaby(int nb);
        void genLabyBack();
        int distMin(int id1, int id2);
        vector<int> voisinsVides(int id);
};

Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
    this->lig = nLignes;
    this->col = nColonnes;
    this->grille.resize(lig * col, 0);
}

Labyrinthe::Labyrinthe(char data[])
{
    this->lig = (int)data[0];
    this->col = (int)data[1];
    cout << "Lignes : " << this->lig << endl
         << "Colonnes : " << this->col << endl;
    int length = this->lig * this->col;
    this->grille.resize(length);
    for (int i = 0; i < length; i++)
    {
        this->grille[i] = (int)data[i + 2];
    }
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
    return this->col * this->lig;
}

int Labyrinthe::getID(int ligne, int colonne)
{
    return this->col * ligne + colonne;
}

int Labyrinthe::getLigne(int id)
{
    return id / this->col;
}

int Labyrinthe::getCol(int id)
{
    return id % this->col;
}

void Labyrinthe::modifie(int ligne, int colonne, char x)
{
    this->grille[getID(ligne, colonne)] = x;
}

void Labyrinthe::modifie(int id, char x)
{
    this->grille[id] = x;
}

char Labyrinthe::lit(int ligne, int colonne)
{
    return this->grille[getID(ligne, colonne)];
}

char Labyrinthe::lit(int id)
{
    return this->grille[id];
}

int Labyrinthe::getBlanches()
{
    // Compte le nombre de cases blanches dans la grille
    int blanches = 0;
    for (int i = 0; i < this->lig; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            if (lit(i, j) == 0)
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
    while (flag == 0 && duree < 1000000)
    {
        id = (rand() % ((this->col * this->lig) - 2) + 1);
        if (this->lit(id) == 0)
            flag = 1;
        duree++;
    }

    return id;
}

void Labyrinthe::affiche()
{
    string res = "";
    char vide = '.';
    char mur = 'X';
    char bord = 'X';
    char marque = '@';

    // Affichage caractère par caractère en bouclant sur le tableau
    for (int i = -1; i <= lig; i++)
    {
        for (int j = -1; j <= col; j++)
        {
            if ((i == -1) | (j == -1) | (i == lig) | (j == col))
                res = res + bord;

            else
            {
                if (lit(i, j) == 0)
                    res = res + vide;

                if (lit(i, j) == 1)
                    res = res + mur;

                if (lit(i, j) == 2)
                    res = res + marque;

                if (lit(i, j) == 3)
                    res = res + 'A';

                if (lit(i, j) == 4)
                    res = res + 'B';
            }
        }
        res = res + '\n';
    }
    
    //res[this->col + 3] = vide;
    //res[res.size() - (this->col + 5)] = vide;
    
    cout << res << endl;
}

bool Labyrinthe::connexe()
{
    // ## DEBUT SEQUENCE
    int id = 0;
    stack<int> pile;

    if (getBlanches() == 0)
        printf("ATTENTION - IL N'Y A AUCUNE CASE BLANCHE!");
    else
    {
        int flag = 0;
        while ((id < this->lig * this->col) && (flag == 0))
        {
            if (this->lit(id) == 0)
            {
                flag = 1;
            }
            else
                id++;
        }
        this->modifie(id, 2);
        pile.push(id);
    }

    while (!(pile.empty()))
    {
        id = pile.top();
        pile.pop();
        int idCol = getCol(id);
        int idLig = getLigne(id);

        if ((idLig > 0) && (lit(idLig - 1, idCol) == 0)) // Haut
        {
            this->modifie(idLig - 1, idCol, 2);
            pile.push(getID(idLig - 1, idCol));
        }

        if ((idLig < this->lig - 1) && (lit(idLig + 1, idCol) == 0)) // Bas
        {
            this->modifie(idLig + 1, idCol, 2);
            pile.push(getID(idLig + 1, idCol));
        }

        if ((idCol > 0) && (lit(idLig, idCol - 1) == 0)) // Gauche
        {
            this->modifie(idLig, idCol - 1, 2);
            pile.push(getID(idLig, idCol - 1));
        }

        if ((idCol < this->col - 1) && (lit(idLig, idCol + 1) == 0)) // Droite
        {
            this->modifie(idLig, idCol + 1, 2);
            pile.push(getID(idLig, idCol + 1));
        }
    }

    int marques = 0;
    for (int i = 0; i < this->getTaille(); i++)
    {
        if (lit(i) == 2)
        {
            modifie(i, 0);
            marques++;
        }
    }

    // Drapeau. 0 si non connexe, 1 si connexe, 2 si erreur (plus de marquées que de blanches).
    bool flag = false;
    if (marques == getBlanches())
        flag = true;

    return flag;
}

void Labyrinthe::genLaby(int nb)
{
    int duree = 1000000;
    int flag = 0;
    int i = 0;
    double marge = 0.1; // marge d'erreur que l'on s'autorise
    int k = nb;         // taille souhaitée

    while ((i < duree) && (flag == 0))
    {
        int id = getRandBlanche();
        this->modifie(id, 1);
        if (connexe() == 0)
            this->modifie(id, 0);
        if ((getBlanches() >= ((1 - marge / 2) * k) && (getBlanches() <= ((1 + marge / 2)) * k)))
        {
            flag = 1;
        }
        i++;
    }
    printf("Amount of operations = %d\n", i);

    if (i >= duree)
    {
        printf("NOMBRE D'OPERATIONS DEPASSE! SORTIE DU PROGRAMME");
        exit(0);
    }
}

void Labyrinthe::genLabyBack()
{
    // On ajuste correctement la taille du labyrinthe on le remplit d'un quadrillage de murs. 
    // L'algorithme consiste à casser ces murs jusqu'à obtenir le labyrinthe souhaité.
    this->lig = this->lig * 2 - 1;
    this->col = this->col * 2 - 1;
    int lig = this->lig;
    int col = this->col;
    this->grille.resize(lig*col);

    for (int l = 0; l < lig; l++)
        for (int c = 0; c < col; c++)
            if (l % 2 == 0 && c % 2 == 0) modifie(getID(l, c), 0); 
            else modifie(getID(l, c), 1);   
    
    // On ajoute la première case à la pile et on la marque
    stack<int> pile;    // La pile qui va servir à mettre en place le backtracking
    pile.push(0);
    modifie(0,2);

    // Tant que la pile n'est pas vide, le labyrinthe n'est pas terminé.
    while(!pile.empty())
    {
        // On pop la pile pour traiter la cellule au sommet. Celle cellule est appelée "current"
        int current = pile.top();
        pile.pop();

        // On vérifie si la case a des voisins non visités. 
        // Si ce n'est pas le cas, on l'abandonne et on passe à la prochaine cellule de la pile -> BACKTRACK
        vector<int> voisins = voisinsVides(current);
        if(!voisins.empty())
        {
            // On push current à la pile pour la retraiter plus tard, car elle possède peut-être encore des voisins non visités.
            pile.push(current);

            // On prend un voisin non visité aléatoirement Celle cellule est appelée "next"
            int next = voisins[rand()%voisins.size()];

            // On retire le mur entre les deux
            modifie( (getLigne(current)+getLigne(next))/2 , (getCol(current)+getCol(next))/2 , 0 );

            // On marque next comme visitée et on l'ajoute à la pile pour traiter ses voisins (si elle en a)
            modifie(next,2);
            pile.push(next);
        }
    }

    // On affiche les cellules marquées.
    for (int l = 0; l < lig; l++)
        for (int c = 0; c < col; c++)
            if (lit(l,c) == 2) modifie(getID(l, c), 0);
}

// Méthode pour la génération backtracking. Elle rend un vecteur contenant toutes les cellules voisines vides et non visitées
vector<int> Labyrinthe::voisinsVides(int id){
    vector<int> v;
    int idLig = getLigne(id);
    int idCol = getCol(id);


    if ((idLig > 0) && (lit(idLig - 2, idCol) == 0)) // Haut
    {
        v.push_back(getID(idLig - 2, idCol));
    }

    if ((idLig < this->lig - 1) && (lit(idLig + 2, idCol) == 0)) // Bas
    {
        v.push_back(getID(idLig + 2, idCol));
    }

    if ((idCol > 0) && (lit(idLig, idCol - 2) == 0)) // Gauche
    {
        v.push_back(getID(idLig, idCol - 2));
    }

    if ((idCol < this->col - 1) && (lit(idLig, idCol + 2) == 0)) // Droite
    {
        v.push_back(getID(idLig, idCol + 2));
    }

    return v;

}




int Labyrinthe::distMin(int id1, int id2)
{
    queue<int> file;
    int res = 0;
    int id;
    bool flag = false;
    vector<int> compte;
    compte.resize(this->getTaille());

    if ((lit(id1) == 1) || (lit(id2) == 1))
        res = -1;
    else
    {
        file.push(id1);
        compte[id1] = res;

        while (!(file.empty()) && (flag == false))
        {
            id = file.front();
            file.pop();

            if (id == id2)
            {
                res = compte[id];
                flag = true;
            }

            int idCol = getCol(id);
            int idLig = getLigne(id);

            if ((idLig > 0) && (lit(idLig - 1, idCol) == 0) && (compte[getID(idLig - 1, idCol)] == 0)) // Haut
            {
                file.push(getID(idLig - 1, idCol));
                compte[getID(idLig - 1, idCol)] = compte[id] + 1;
            }

            if ((idCol < this->col - 1) && (lit(idLig, idCol + 1) == 0) && (compte[getID(idLig, idCol + 1)] == 0)) // Droite
            {
                file.push(getID(idLig, idCol + 1));
                compte[getID(idLig, idCol + 1)] = compte[id] + 1;
            }

            if ((idLig < this->lig - 1) && (lit(idLig + 1, idCol) == 0) && (compte[getID(idLig + 1, idCol)] == 0)) // Bas
            {
                file.push(getID(idLig + 1, idCol));
                compte[getID(idLig + 1, idCol)] = compte[id] + 1;
            }

            if ((idCol > 0) && (lit(idLig, idCol - 1) == 0) && (compte[getID(idLig, idCol - 1)] == 0)) // Gauche
            {
                file.push(getID(idLig, idCol - 1));
                compte[getID(idLig, idCol - 1)] = compte[id] + 1;
            }

            
        }
    }
    return res;
}

int main(int argc, const char * argv[])
{
    srand((unsigned)time(NULL));

    // CHANGER LE CODE DANS CE BLOC
    // ---------------

    Labyrinthe* lab2 = new Labyrinthe(10,10);
    lab2->genLaby(50);
    lab2->affiche();

    // ---------------

    return 0;
}