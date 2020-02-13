#pragma once

#include "DetectedObjects.h"
#include "Config.h"
#include <opencv2/dnn.hpp>

class YoloDetector
{
public:
    YoloDetector(Config const& config);
    DetectedObjects detect_objects(cv::Mat const &frame);

public:
    Config config;

private:
    void load_labels(std::string const& path_labels);
    void load_network(std::string const& path_config, std::string const& path_weights);
    void init_layers_names();

private:
    cv::dnn::Net net;
    std::vector<std::string> labels;
    std::vector<std::string> layers_names;
};

