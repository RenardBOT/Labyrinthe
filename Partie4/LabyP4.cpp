/*
LA COMMANDE POUR COMPILER EST :
gcc -Wall LabyP4.cpp -o Labyrinthe.exe
*/


#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
#include "Labyrinthe.cpp"

int main()
{
    srand((unsigned)time(NULL));
    Labyrinthe* lab = new Labyrinthe(10,10);
    lab->genLaby(50);

    lab->affiche();

    int ok = lab->distMin(lab->getTaille()-1,0);

    cout << "\nDistance entre depart et arrivee : " << ok << endl;
    
    
    
    return 0;
}
