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
<<<<<<< HEAD
    srand((unsigned)time(NULL));
    int h = 100;
    int l = 100;
=======
    srand((unsigned)time(NULL)); // random seed 
    int h = 100; // hauteur du labyrinthe
    int l = 100; // 
>>>>>>> cb41abf2fa83a62d79cec4948448f9476ac22f17
    Labyrinthe* lab = new Labyrinthe(h,l);
    int k = (h*l)/2;
    lab->genLaby(k);

    lab->affiche();

    int ok = lab->distMin(lab->getTaille()-1,0);

    int b = lab->getBlanches();

    cout << "Asked for k = "<< k << " dots | got k = "<< b << " | delta = " << -(k-b) << "(x" << (double)k/b << ")" << "\n Shortest path length : " << ok << endl;
    
    
    
    return 0;
}
