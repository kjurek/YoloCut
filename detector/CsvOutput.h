#pragma once

#include <string>
#include <vector>
#include <ostream>

#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>

#include "YoloDetector.h"

class CsvOutput
{
public:
    CsvOutput(std::ostream &out);

    void add(DetectedObjects const &objects);

private:
    std::ostream &out;

    unsigned frame_count;
};
