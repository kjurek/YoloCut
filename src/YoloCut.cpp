#include "YoloCut.h"

#include <fstream>
#include <iostream>
#include <opencv2/imgproc.hpp>

YoloCut::YoloCut(std::unique_ptr<ObjectDetector> detector, std::unique_ptr<VideoCutter> cutter)
    :   detector(std::move(detector)), cutter(std::move(cutter))
{ }

YoloCut::~YoloCut()
{
    release();
}

void YoloCut::cut_video(std::string const& path_input)
{
    load_input_video(path_input);

    unsigned int frames_processed = 0;
    for (;;) {
        auto frames = read_frames();
        if (frames.empty()) {
            break;
        }

        // TODO: implement

        frames_processed += frames.size();
        std::cout << "Processed frames: " << frames_processed << std::endl;
    }

    release();
}

void YoloCut::load_input_video(std::string const& path_video)
{
    input_video.open(path_video);
    fps = static_cast<unsigned int>(input_video.get(cv::CAP_PROP_FPS));
}

void YoloCut::release()
{
    input_video.release();
}

std::vector<cv::Mat> YoloCut::read_frames()
{
    std::vector<cv::Mat> frames;
    frames.reserve(fps);
    for (unsigned int i = 0; i < fps; ++i) {
        cv::Mat frame;

        input_video >> frame;
        if (frame.empty()) {
            break;
        }
        frames.push_back(frame);
    }
    return frames;
}

bool YoloCut::should_cut_frames(std::vector<cv::Mat> const &frames)
{
    unsigned int end = config.give_up_percent * frames.size();
    for (unsigned int i = 0; i < end; ++i) {
        auto detected_objects = detector->detect_objects(frames[i]);
        // TODO: implement
    }
    return true;
}
