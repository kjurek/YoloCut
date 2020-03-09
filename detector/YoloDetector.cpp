#include "YoloDetector.h"

#include <fstream>
#include <iostream>

YoloDetector::YoloDetector(Config const &config) : config(config)
{
    load_network(config.path_config, config.path_weights);
    load_labels(config.path_labels);
    init_layers_names();
}

void YoloDetector::load_labels(std::string const &path_labels)
{
    labels.clear();
    std::ifstream file_labels(path_labels);
    if (!file_labels) {
        throw "Unable to open labels file: " + path_labels;
    }

    std::string label;
    while (std::getline(file_labels, label)) {
        labels.push_back(label);
    }
}

void YoloDetector::load_network(std::string const &path_config, std::string const &path_weights)
{
    net = cv::dnn::readNetFromDarknet(path_config, path_weights);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

void YoloDetector::init_layers_names()
{
    //Get the indices of the output layers, i.e. the layers with unconnected outputs
    std::vector<int> output_layers = net.getUnconnectedOutLayers();

    //get the names of all the layers in the network
    std::vector<std::string> names = net.getLayerNames();

    // Get the names of the output layers in names
    layers_names.resize(output_layers.size());
    for (size_t i = 0; i < output_layers.size(); ++i) {
        layers_names[i] = names[output_layers[i] - 1];
    }
}

DetectedObjects YoloDetector::detect_objects(cv::Mat const &frame)
{
    cv::Mat blob;
    cv::dnn::blobFromImage(frame,
                           blob,
                           config.scale_factor,
                           config.size,
                           config.mean,
                           config.swap_channels,
                           config.crop);
    net.setInput(blob);

    std::vector<cv::Mat> outs;
    net.forward(outs, layers_names);

    DetectedObjects result;
    for (size_t i = 0; i < outs.size(); ++i) {
        float *data = (float *) outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point class_id_point;
            double confidence;
            minMaxLoc(scores, 0, &confidence, 0, &class_id_point);

            if (confidence >= config.min_confidence) {
                result.labels.push_back(labels[class_id_point.x]);
                result.confidences.push_back(confidence);
            }
        }
    }
    return result;
}
