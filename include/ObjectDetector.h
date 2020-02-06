#pragma once

#include <vector>
#include <string>
#include <opencv2/highgui.hpp>

struct DetectedObject
{
    std::string label;
    double confidence;
};

class ObjectDetector
{
public:
    virtual std::vector<DetectedObject> detect_objects(cv::Mat const &frame) = 0;
};
