#ifndef ImageIsosurface_hpp
#define ImageIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"
#include <vector>
#include "Image.hpp"

class ImageIsosurface : public Isosurface {
public:
    ImageIsosurface(int, int, float, float, Image);
    float signedDistanceFunction(Point) override;
    void render() override;
private:
    float distanceBetweenPoints(Point, Point);
    std::vector<Point> imageDataPoints;
    float grayscaleThreshold;
};


#endif /* ImageIsosurface_hpp */
