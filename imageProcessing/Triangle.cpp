#include "Triangle.hpp"
#include "Point.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Triangle::Triangle(Point triangleP1, Point triangleP2, Point triangleP3, float dim) {
    p1 = triangleP1;
    p2 = triangleP2;
    p3 = triangleP3;
    dimension = dim;
    setColors();
}

void Triangle::setColors() {
    colorkey1 = (float)(int(dimension*100) % 100) / 100;
    colorkey2 = (float)(int(dimension*100) % 100) / 100;
    colorkey3 = (float)(int(dimension*100) % 100) / 100;
}

void Triangle::render() {
    glColor3f(colorkey1, colorkey2, colorkey3);

    glBegin(GL_TRIANGLES);
    glVertex2f(p1.getX(), p1.getY());
    glVertex2f(p2.getX(), p2.getY());
    glVertex2f(p3.getX(), p3.getY());
    glEnd();
}

vector<Point> Triangle::getPoints() {
    vector<Point> points = vector<Point>();
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

bool Triangle::operator == (Triangle &obj) {
    bool pointsMatch1 = (p1==obj.p1) || (p1==obj.p2) || (p1==obj.p3);
    bool pointsMatch2 = (p2==obj.p1) || (p2==obj.p2) || (p2==obj.p3);
    bool pointsMatch3 = (p3==obj.p1) || (p3==obj.p2) || (p3==obj.p3);

    return (pointsMatch1 && pointsMatch2 && pointsMatch3);
}
