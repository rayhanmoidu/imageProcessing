#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point {
public:
    Point(int pointX = 0, int pointY = 0);
    bool operator == (Point &obj);
    
    //getters
    float getX();
    float getY();
    
    //setters
    void setX(int);
    void setY(int);

protected:
    int getCanvasCoordinate(int);
    
    float x;
    float y;
};

#endif
