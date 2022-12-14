#ifndef ImageIsosurface_hpp
#define ImageIsosurface_hpp

#include <stdio.h>
#include "Point.hpp"
#include "Isosurface.hpp"
#include <vector>
#include "Image.hpp"
#include <map>
#include <unordered_set>
#include <utility>
#include <set>

struct pair_hash {
    inline std::size_t operator()(const std::pair<float,float> & v) const {
        int prime = 31;
        int result = 1;
        result = prime * result + v.first;
        result = prime * result + v.second;
        return result;
    }
};

class ImageIsosurface : public Isosurface {
public:
    ImageIsosurface(int, int, int, int, float, float, float, Image);
    float signedDistanceFunction(Point) override;
    float signedDistanceFunctionOptimized(Point);
    void render() override;
private:
    float distanceBetweenPoints(Point, Point);
    Point mapCoordinatesToScreen(Point, float, float);
    
    std::unordered_set<std::pair<float, float>, pair_hash> imageDataPointsSet;
    
    float grayscaleThresholdUpper;
    float grayscaleThresholdLower;
};


#endif /* ImageIsosurface_hpp */
