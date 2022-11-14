#include "ImageIsosurface.hpp"
#include <cmath>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

ImageIsosurface::ImageIsosurface(int width, int height, float renderThreshold, float grayThreshold, Image img) {
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = renderThreshold;
    grayscaleThreshold = grayThreshold;
    
    cv::Mat imageObject = img.getImage();
    for(int i = 0; i < imageObject.rows; i++) {
        for(int j = 0; j < imageObject.cols; j++) {
            int pixelValue = (int)imageObject.at<uchar>(i, j);
//            if (pixelValue < 100) {
            if (pixelValue > 10 && pixelValue < 60) {
                imageDataPoints.push_back(Point(j, imageObject.rows - i));
            }
        }
    }
}

float ImageIsosurface::signedDistanceFunction(Point p) {
    float smallestDistance = INT_MAX;
    for (int i = 0; i < imageDataPoints.size(); i++) {
        float curDistance = distanceBetweenPoints(imageDataPoints[i], p);
        if (curDistance < smallestDistance) {
            smallestDistance = curDistance;
        }
    }
    return smallestDistance;
}

float ImageIsosurface::distanceBetweenPoints(Point p1, Point p2) {
    float dx = p1.getX() - p2.getX();
    float dy = p1.getY() - p2.getY();
    
    return sqrt(dx*dx + dy*dy);
}

void ImageIsosurface::render() {
    for (int i = 0; i < imageDataPoints.size(); i++) {
        glBegin(GL_QUADS);

        int x = imageDataPoints[i].getX();
        int y = imageDataPoints[i].getY();

        glVertex2f(x-2, y-2);
        glVertex2f(x+2, y-2);
        glVertex2f(x+2, y+2);
        glVertex2f(x-2, y+2);
        glEnd();
    }
}
