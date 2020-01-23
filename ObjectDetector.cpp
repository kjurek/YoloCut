#include "ObjectDetector.h"

#include <fstream>
#include <iostream>

ObjectDetector::ObjectDetector(std::string const& path_config, std::string const& path_weights, std::string const& path_labels)
{
    load_network(path_config, path_weights);
    load_labels(path_labels);
    init_layers_names();
}

void ObjectDetector::load_labels(std::string const& path_labels)
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

void ObjectDetector::load_network(std::string const& path_config, std::string const& path_weights)
{
    net = cv::dnn::readNetFromDarknet(path_config, path_weights);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

void ObjectDetector::init_layers_names()
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

bool ObjectDetector::detect_objects(cv::Mat const& frame, std::unordered_set<std::string> objects, double min_confidence)
{
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, scale_factor, size, mean, swap_channels, crop);
    net.setInput(blob);

    std::vector<cv::Mat> outs;
    net.forward(outs, layers_names);

    for (size_t i = 0; i < outs.size(); ++i) {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float *data = (float *) outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point class_id_point;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &class_id_point);

            if (confidence >= min_confidence && objects.count(labels[class_id_point.x])) {
                objects.erase(labels[class_id_point.x]);
            }
            if (objects.empty()) {
                return true;
            }
        }
    }
    return false;
}
