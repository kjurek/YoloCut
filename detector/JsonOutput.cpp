#include "JsonOutput.h"

JsonOutput::JsonOutput(std::ostream &out) : out(out), frame_count(0)
{
    out << "[";
}

JsonOutput::~JsonOutput()
{
    out << "]";
}

void JsonOutput::add(DetectedObjects const &objects)
{
    if (frame_count > 0) {
        out << ",";
    }
    out << "[";
    for (size_t i = 0; i < objects.labels.size(); ++i) {
        if (i > 0) {
            out << ",";
        }

        out << "{"
            << "\"label\":" << '"' << objects.labels[i] << '"' << ","
            << "\"confidence\":" << objects.confidences[i] << ","
            << "\"x\":" << objects.positions[i].x << ","
            << "\"y\":" << objects.positions[i].y << ","
            << "\"width\":" << objects.positions[i].width << ","
            << "\"height\":" << objects.positions[i].height << "}";
    }
    out << "]";
    ++frame_count;
}
