#pragma once

#include "VideoCutter.h"
#include <iostream>

class FfmpegVideoCutter : public VideoCutter
{
public:
    FfmpegVideoCutter(std::ostream &out,
                      std::string const &path_input,
                      std::string const &path_output);
    virtual void cut(int start, int end) override;

private:
    std::string format_seconds(int seconds) const;

private:
    std::ostream &out;
    std::string path_input;
    std::string path_output;
};
