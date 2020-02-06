#include <iostream>
#include <string>

#include "FfmpegVideoCutter.h"
#include "YoloDetector.h"
#include "YoloCut.h"

int main(int argc, char** argv)
{
    // TODO: create args
    std::string input_video = "/home/kjurek/Downloads/skate_vine.mp4";
    std::string output_video = "/home/kjurek/Downloads/skate_vine_processed.mp4";

    YoloDetectorConfig config;
    config.path_config = "/home/kjurek/Workspace/yolo/yolov3.cfg";
    config.path_labels = "/home/kjurek/Workspace/yolo/coco.names";
    config.path_weights = "/home/kjurek/Workspace/yolo/yolov3.weights";

    auto detector = std::make_unique<YoloDetector>(config);
    auto cutter = std::make_unique<FfmpegVideoCutter>(std::cout, input_video, output_video);

    YoloCut yolo_cut(std::move(detector), std::move(cutter));

    return 0;
}
