#include "ImageIsosurface.hpp"
#include <cmath>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>

using namespace std;

Point ImageIsosurface::mapCoordinatesToScreen(Point p, float widthRatio, float heightRatio) {
    float newX = p.getX() * (widthRatio);
    float newY = p.getY() * (heightRatio);
    return Point(newX, newY);
}

ImageIsosurface::ImageIsosurface(int width, int height, int rawWidth, int rawHeight, float renderThreshold, float grayThresholdLower, float grayThresholdUpper, Image img) {
    screenWidth = width;
    screenHeight = height;
    renderingThreshold = renderThreshold;
    grayscaleThresholdLower = grayThresholdLower;
    grayscaleThresholdUpper = grayThresholdUpper;
    
    cout <<"hi" << width << " " << height << endl;
    
    cv::Mat imageObject = img.getImage();
    for(int i = 0; i < imageObject.rows; i++) {
        for(int j = 0; j < imageObject.cols; j++) {
            int pixelValue = (int)imageObject.at<uchar>(i, j);
            if (pixelValue > grayThresholdLower && pixelValue < grayThresholdUpper) {
                Point newPoint = mapCoordinatesToScreen(Point(j, imageObject.rows - i), (float(rawWidth) / float(imageObject.cols)), (float(rawHeight) / float(imageObject.rows)));
//                cout << newPoint.getX() <<" " << newPoint.getY() << endl;
                imageDataPoints.push_back(newPoint);
                imageDataPointsSet.insert(pair<float, float>(newPoint.getX(), newPoint.getY()));
            }
        }
    }
}

float ImageIsosurface::signedDistanceFunctionOptimized(Point p) {
    float smallestDistance = INT_MAX;
    for (int i = 0; i < imageDataPoints.size(); i++) {
        float curDistance = distanceBetweenPoints(imageDataPoints[i], p);
        if (curDistance < smallestDistance) {
            smallestDistance = curDistance;
        }
    }
    return smallestDistance;
}

float ImageIsosurface::signedDistanceFunction(Point p) {
    float curX = p.getX();
    float curY = p.getY();
    float offset = 0;
    float distance = INT_MAX;
    while (1) {
        bool didFind = false;
        float count = -offset;
        while (count <= offset) {
            Point testPoint1(curX + count, curY + offset);
            Point testPoint2(curX + count, curY - offset);

            if (imageDataPointsSet.count(pair<float, float>(testPoint1.getX(), testPoint1.getY()))) {
                didFind = true;
                if (distanceBetweenPoints(testPoint1, p) < distance) {
                    distance = distanceBetweenPoints(testPoint1, p);
                }
            }

            if (imageDataPointsSet.count(pair<float, float>(testPoint2.getX(), testPoint2.getY()))) {
                didFind = true;
                if (distanceBetweenPoints(testPoint2, p) < distance) {
                    distance = distanceBetweenPoints(testPoint2, p);
                }
            }
            count +=1;
        }

        count = -offset;
        while (count <= offset) {
            Point testPoint1(curX + offset, curY + count);
            Point testPoint2(curX - offset, curY + count);

            if (imageDataPointsSet.count(pair<float, float>(testPoint1.getX(), testPoint1.getY()))) {
                didFind = true;
                if (distanceBetweenPoints(testPoint1, p) < distance) {
                    distance = distanceBetweenPoints(testPoint1, p);
                }
            }

            if (imageDataPointsSet.count(pair<float, float>(testPoint2.getX(), testPoint2.getY()))) {
                didFind = true;
                if (distanceBetweenPoints(testPoint2, p) < distance) {
                    distance = distanceBetweenPoints(testPoint2, p);
                }
            }
            count +=1;
        }

        if (didFind) break;
//        if (curX + offset > screenWidth && curX - offset < 0 && curY + offset > screenHeight && curY - offset < 0) break;
        offset +=1;
    }
    if (distance==INT_MAX) cout <<"ERROR ERROR"<<endl;
    return distance;
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

        glVertex2f(x-1, y-1);
        glVertex2f(x+1, y-1);
        glVertex2f(x+1, y+1);
        glVertex2f(x-1, y+1);
        glEnd();
    }
}
