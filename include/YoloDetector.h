#pragma once

#include "ObjectDetector.h"

#include <opencv2/dnn.hpp>

struct YoloDetectorConfig
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

class YoloDetector : public ObjectDetector
{
public:
    YoloDetector(YoloDetectorConfig const& config);
    virtual std::vector<DetectedObject> detect_objects(cv::Mat const &frame) override;

public:
    YoloDetectorConfig config;

private:
    void load_labels(std::string const& path_labels);
    void load_network(std::string const& path_config, std::string const& path_weights);
    void init_layers_names();

private:
    cv::dnn::Net net;
    std::vector<std::string> labels;
    std::vector<std::string> layers_names;
};
