#include <iostream>
#include <string>

#include "YoloDetector.h"
#include "JsonOutput.h"

int main(int argc, char** argv)
{
    // TODO: create args
    std::string input_video_path = "/home/kjurek/run.mp4";

    Config config;
    config.path_config = "/home/kjurek/Workspace/yolo/yolov3.cfg";
    config.path_labels = "/home/kjurek/Workspace/yolo/coco.names";
    config.path_weights = "/home/kjurek/Workspace/yolo/yolov3.weights";

    auto detector = YoloDetector(config);
    auto output = JsonOutput(std::cout);

    cv::VideoCapture input_video(input_video_path);

    cv::Mat frame;
    for (input_video >> frame; !frame.empty(); input_video >> frame) {
        DetectedObjects objects = detector.detect_objects(frame);
        output.add(objects);
    }
    input_video.release();

    return 0;
}
