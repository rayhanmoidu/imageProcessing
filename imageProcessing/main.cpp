#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/core.hpp>
#include <utility>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Image.hpp"
#include "Canvas.hpp"
#include <string>
#include "ImageIsosurface.hpp"
#include "Quadtree.hpp"

using namespace std;

const string imagePath = "/Users/rayhanmoidu/Documents/jaleel_test.JPG";
const float imageRenderingThreshold = 0.2;
const float grayscaleThreshold = 1;

int main() {
    glfwInit();
    char* windowTitle = "Image Processing";
    
    Image image = Image(imagePath);
    cv::Mat imageObject = image.getImage();
    
    cv::imshow("hi", imageObject);
    
    int imgRawWidth = ( imageObject.cols / 2 );
    int imgRawHeight = ( imageObject.rows / 2 );
    int windowDimension = std::max(imgRawWidth, imgRawHeight);
    
    Canvas canvas(windowDimension, windowDimension, windowTitle);
    GLFWwindow *window = canvas.getWindow();
    
    
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return -1;
    }
    
    ImageIsosurface isosurface(canvas.getWidth(), canvas.getHeight(), imageRenderingThreshold, grayscaleThreshold, image);
    
    std::vector<std::pair<float, float>> vertices;
    
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
    
    Quadtree quadtree(canvas.getWidth(), canvas.getHeight(), 20, isosurface);

        
    while (!glfwWindowShouldClose(window)) {
        
        canvas.initCanvas();
        
        isosurface.render();
        quadtree.render();

        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}


// balanace the quadtree
// quadtree tiling (introduce diagonals to make it into triangles, can either simply use the diagonal or do it like the paper did it)
// skew the quadtree to make it into parallelograms that turn into equilateral triangles
// provably good meshig (probably the most ideal one!)


