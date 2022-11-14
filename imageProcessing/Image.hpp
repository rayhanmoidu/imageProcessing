//
//  Image.hpp
//  imageProcessing
//
//  Created by Rayhan Moidu on 2022-11-13.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>
#include <opencv2/core.hpp>
#include <utility>
#include <string>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class Image {
public:
    Image(std::string);
    cv::Mat getImage();
    
private:
    std::string imagePath;
    cv::Mat image;
};

#endif /* Image_hpp */
