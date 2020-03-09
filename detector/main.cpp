#include <iostream>
#include <string>

#include "YoloDetector.h"
#include "CsvOutput.h"

int main(int argc, char** argv)
{
    if (argc != 5) {
        std::cout << "usage: ./detector input_video.mp4 yolo.cfg yolo.labels yolo.weights";
        return EXIT_FAILURE;
    }

    std::string input_video_path = argv[1];

    Config config;
    config.path_config = argv[2];
    config.path_labels = argv[3];
    config.path_weights = argv[4];

    auto detector = YoloDetector(config);
    auto output = CsvOutput(std::cout);

    cv::VideoCapture input_video(input_video_path);

    cv::Mat frame;
    for (input_video >> frame; !frame.empty(); input_video >> frame) {
        DetectedObjects objects = detector.detect_objects(frame);
        output.add(objects);
    }
    input_video.release();

    return EXIT_SUCCESS;
}
