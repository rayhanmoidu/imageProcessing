#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include "Point.hpp"
#include <vector>

using namespace std;

class Triangle {
public:
    Triangle(Point, Point, Point, float);
    
    void render();

    vector<Point> getPoints();
    
    bool operator == (Triangle &obj);
    
private:
    void setColors();
    
    Point p1;
    Point p2;
    Point p3;
    float colorkey1;
    float colorkey2;
    float colorkey3;
    float dimension=0;
};

#endif /* Triangle_hpp */
