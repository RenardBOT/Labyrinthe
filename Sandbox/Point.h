#include <iostream>
using namespace std;

class Point
{
    private:
        int x;
        int y;
    public:
        Point(int x, int y);
        int getX();
        void printPoint();
};