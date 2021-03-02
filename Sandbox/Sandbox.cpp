/*
LA COMMANDE POUR COMPILER EST :
gcc -Wall LabyP3.cpp -o JeuLabyrinthe.exe
*/

#include <iostream>
#include <vector>
using namespace std;
#include "Point.cpp"



int main()
{

    
    
    Point* toto = new Point(2,3);

    cout << toto->getX() << endl;
    
    return 0;
}
