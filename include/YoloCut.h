#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>

#include "ObjectDetector.h"
#include "VideoCutter.h"

struct Config
{
    std::unordered_set<std::string> required_objects;
    double min_confidence;
    float give_up_percent;
};

class YoloCut
{
public:
    Config config;

    YoloCut(std::unique_ptr<ObjectDetector> detector, std::unique_ptr<VideoCutter> cutter);
    ~YoloCut();

    void cut_video(std::string const& path_input);

private:
    void load_input_video(std::string const &path_video);
    void init_output_video(std::string const &path_output);
    void release();

    std::vector<cv::Mat> read_frames();

    bool should_cut_frames(std::vector<cv::Mat> const &frames);
private:
    std::unique_ptr<ObjectDetector> detector;
    std::unique_ptr<VideoCutter> cutter;
    cv::VideoCapture input_video;
    unsigned int fps;
};
