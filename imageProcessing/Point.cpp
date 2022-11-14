#include "Point.hpp"

Point::Point(int pointX, int pointY) {
    x = pointX;
    y = pointY;
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

void Point::setX(int xVal) {
    x = xVal;
}

void Point::setY(int yVal) {
    y = yVal;
}

bool Point::operator == (Point &obj) {
    return obj.x == x && obj.y == y;
}

int getCanvasCoordinate(int coordinateToTransform) {
    return coordinateToTransform*2;
}
