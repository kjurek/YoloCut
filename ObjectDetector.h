#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>


class ObjectDetector
{
public:
    cv::dnn::Net net;
    std::vector<std::string> labels;

    cv::Size size = {224, 224};
    cv::Scalar mean = {0, 0, 0};
    bool swap_channels = true;
    bool crop = false;
    double scale_factor = 1.0 / 255.0;

    ObjectDetector(std::string const& path_config, std::string const& path_weights, std::string const& path_labels);
    bool detect_objects(const cv::Mat &frame,
                        std::unordered_set<std::string> objects,
                        double min_confidence);

private:
    void load_labels(std::string const& path_labels);
    void load_network(std::string const& path_config, std::string const& path_weights);
    void init_layers_names();

private:
    std::vector<std::string> layers_names;
};
