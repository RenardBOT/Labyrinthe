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
    srand((unsigned)time(NULL)); // random seed 
    int h = 100; // hauteur du labyrinthe
    int l = 100; // 
    Labyrinthe* lab = new Labyrinthe(h,l);
    int k = (h*l)/2;
    lab->genLaby(k);

    lab->affiche();

    int ok = lab->distMin(lab->getTaille()-1,0);

    int b = lab->getBlanches();

    cout << "Asked for k = "<< k << " dots | got k = "<< b << " | delta = " << -(k-b) << "(x" << (double)k/b << ")" << "\n Shortest path length : " << ok << endl;
    
    
    
    return 0;
}
