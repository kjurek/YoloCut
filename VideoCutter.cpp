#include "VideoCutter.h"

#include <fstream>
#include <iostream>
#include <opencv2/imgproc.hpp>

VideoCutter::VideoCutter(ObjectDetector const& detector_) : detector(detector_) {}

VideoCutter::~VideoCutter()
{
    release();
}

void VideoCutter::cut_video(std::string const& path_input, std::string const& path_output)
{
    load_input_video(path_input);
    init_output_video(path_output);

    unsigned int frames_processed = 0;
    for (;;) {
        auto frames = read_frames();
        if (frames.empty()) {
            break;
        }

        if (should_cut_frames(frames)) {
            write_frames(frames, output_video_cut_out);
        } else {
            write_frames(frames, output_video);
        }
        frames_processed += frames.size();
        std::cout << "Processed frames: " << frames_processed << std::endl;
    }

    release();
}

void VideoCutter::load_input_video(std::string const& path_video)
{
    input_video.open(path_video);
    fps = static_cast<unsigned int>(input_video.get(cv::CAP_PROP_FPS));
}

void VideoCutter::init_output_video(std::string const& path_output)
{
    std::string path_output_cut_out = path_output;
    auto it = path_output_cut_out.find(".");
    path_output_cut_out.replace(it, 1, "_cutout.");
    cv::Size size(input_video.get(cv::CAP_PROP_FRAME_WIDTH),
                  input_video.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fourcc = input_video.get(cv::CAP_PROP_FOURCC);
    output_video.open(path_output, fourcc, fps, size);
    output_video_cut_out.open(path_output_cut_out, fourcc, fps, size);
}

void VideoCutter::release()
{
    input_video.release();
    output_video.release();
    output_video_cut_out.release();
}

void VideoCutter::write_frames(std::vector<cv::Mat> const &frames, cv::VideoWriter &writer)
{
    for (auto &frame : frames) {
        cv::Mat detectedFrame;
        frame.convertTo(detectedFrame, CV_8U);
        writer.write(frame);
    }
}

std::vector<cv::Mat> VideoCutter::read_frames()
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

bool VideoCutter::should_cut_frames(std::vector<cv::Mat> const &frames)
{
    unsigned int end = config.give_up_percent * frames.size();
    for (unsigned int i = 0; i < end; ++i) {
        if (detector.detect_objects(frames[i], config.required_objects, config.min_confidence)) {
            return false;
        }
    }
    return true;
}
