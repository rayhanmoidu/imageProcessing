#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/core.hpp>
#include <utility>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

const GLint WIDTH = 1000, HEIGHT = 500;

int main() {
    glfwInit();
    char* windowTitle = "Isosurface Stuffing";
//    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle, nullptr, nullptr);
    
    
    cv::Mat img = imread("/Users/rayhanmoidu/Documents/starry_night.png", IMREAD_GRAYSCALE);
    cv::Mat grayImg;
    
    cv::imshow("hi", img);
    
    GLFWwindow *window = glfwCreateWindow(img.cols/2, img.rows/2, windowTitle, nullptr, nullptr);

    
    
    
    
//    cvtColor(img, grayImg, CV_BGR2GRAY);
    
    std::cout << img.rows <<" " << img.cols << std::endl;
    
//    imshow("before", img);
    
    std::vector<std::pair<int, int>> vertices;
    
    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j++)
        {
            int pixelValue = (int)img.at<uchar>(j,i);
            if (pixelValue > 170) {
                vertices.push_back(std::pair<int, int>(j, i));
            }
            

            // do something with BGR values...
        }
    }
    
    
    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    
    
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to create GLEW" << std::endl;
        
        return -1;
    }

        
    while (!glfwWindowShouldClose(window)) {
                
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();
        
        glfwPollEvents();
        
        glColor3f(0.5f, 0.5f, 0.5f);
        
        for (int i = 0; i < vertices.size(); i++) {
            glBegin(GL_QUADS);
            
            int x = vertices[i].first;
            int y = vertices[i].second;

            glVertex2f(x-2, y-2);
            glVertex2f(x+2, y-2);
            glVertex2f(x+2, y+2);
            glVertex2f(x-2, y+2);
            glEnd();
        }
        
//        glBegin(GL_QUADS);
//
//        glVertex2f(100, 100);
//        glVertex2f(200, 100);
//        glVertex2f(200, 200);
//        glVertex2f(100, 200);
//        glEnd();



        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


// balanace the quadtree
// quadtree tiling (introduce diagonals to make it into triangles, can either simply use the diagonal or do it like the paper did it)
// skew the quadtree to make it into parallelograms that turn into equilateral triangles
// provably good meshig (probably the most ideal one!)


