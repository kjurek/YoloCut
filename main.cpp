#include <iostream>
#include <string>

#include "VideoCutter.h"

int main(int argc, char** argv)
{
    // TODO: create args
    std::string labels = "/home/kjurek/Workspace/yolo/coco.names";
    std::string config = "/home/kjurek/Workspace/yolo/yolov3.cfg";
    std::string weights = "/home/kjurek/Workspace/yolo/yolov3.weights";
    std::string input_video = "/home/kjurek/Downloads/skate_vine.mp4";
    std::string output_video = "/home/kjurek/Downloads/skate_vine_processed.mp4";

    ObjectDetector detector(config, weights, labels);
    VideoCutter cutter(detector);
    cutter.config.required_objects = {"skateboard", "person"};
    cutter.config.min_confidence = 0.5; // min model confidence on detection
    cutter.config.give_up_percent = 0.3; // if object is not detected after n% frames in fps size of frames cut it out
    cutter.cut_video(input_video, output_video);

    return 0;
}
