#pragma once

#include <vector>
#include <string>
#include <opencv2/highgui.hpp>

struct DetectedObjects
{
    std::vector<std::string> labels;
    std::vector<double> confidences;
    std::vector<cv::Rect> positions;
};
