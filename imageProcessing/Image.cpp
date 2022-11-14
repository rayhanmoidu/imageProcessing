//
//  Image.cpp
//  imageProcessing
//
//  Created by Rayhan Moidu on 2022-11-13.
//

#include "Image.hpp"

Image::Image(std::string path) {
    imagePath = path;
    image = imread(path, cv::IMREAD_GRAYSCALE);
}

cv::Mat Image::getImage() {
    return image;
}
