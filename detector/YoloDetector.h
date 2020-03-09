#pragma once

#include "DetectedObjects.h"
#include "Config.h"
#include <opencv2/dnn.hpp>

class YoloDetector
{
public:
    Config config;

    YoloDetector(Config const& config);
    DetectedObjects detect_objects(cv::Mat const &frame);

private:
    void load_labels(std::string const& path_labels);
    void load_network(std::string const& path_config, std::string const& path_weights);
    void init_layers_names();

    cv::dnn::Net net;
    std::vector<std::string> labels;
    std::vector<std::string> layers_names;
};

