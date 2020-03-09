#include "CsvOutput.h"

CsvOutput::CsvOutput(std::ostream &out) : out(out), frame_count(0)
{
    out << "frame,label,confidence" << std::endl;
}

void CsvOutput::add(DetectedObjects const &objects)
{
    for (size_t i = 0; i < objects.labels.size(); ++i) {
        out << frame_count << "," << objects.labels[i] << "," << objects.confidences[i] << std::endl;
    }
    ++frame_count;
}
