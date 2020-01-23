#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>

#include "ObjectDetector.h"

struct Config
{
    std::unordered_set<std::string> required_objects;
    double min_confidence;
    float give_up_percent;
};

class VideoCutter
{
public:
    cv::VideoWriter output_video;
    cv::VideoWriter output_video_cut_out;
    Config config;

    VideoCutter(ObjectDetector const& detector_);
    ~VideoCutter();

    void cut_video(std::string const& path_input, std::string const& path_output);

private:
    void load_input_video(std::string const &path_video);
    void init_output_video(std::string const &path_output);
    void release();

    void write_frames(std::vector<cv::Mat> const &frames, cv::VideoWriter &writer);
    std::vector<cv::Mat> read_frames();

    bool should_cut_frames(std::vector<cv::Mat> const &frames);
private:
    ObjectDetector detector;
    cv::VideoCapture input_video;
    unsigned int fps;
};
