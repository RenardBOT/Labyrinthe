#include "Point.h"




Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Point::getX()
{
    return x;
}

void Point::printPoint()
{
    cout << "Coordonnees - X = " << x << " - Y = " << y << endl;
}