#pragma once

#include <opencv2/dnn.hpp>
#include <string>

struct Config
{
    cv::Size size = {224, 224};
    cv::Scalar mean = {0, 0, 0};
    bool swap_channels = true;
    bool crop = false;
    double scale_factor = 1.0 / 255.0;
    double min_confidence = 0.5;

    std::string path_config;
    std::string path_weights;
    std::string path_labels;
};
