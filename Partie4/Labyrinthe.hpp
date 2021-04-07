#include <vector>
#include <string>
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