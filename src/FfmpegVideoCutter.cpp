#include "FfmpegVideoCutter.h"

#include <cmath>
#include <sstream>
#include <iomanip>

FfmpegVideoCutter::FfmpegVideoCutter(std::ostream &out,
                                     std::string const &path_input,
                                     std::string const &path_output)
    : out(out), path_input(path_input), path_output(path_output)
{}

void FfmpegVideoCutter::cut(int start, int end)
{
    out << "ffmpeg -i " << path_input
        << " -ss " << format_seconds(start)
        << " -t " << format_seconds(end)
        << " -c copy " << path_output << std::endl;
}

std::string FfmpegVideoCutter::format_seconds(int seconds) const
{
    int hh = floor(seconds / 3600.0);
    int mm = floor(fmod(seconds, 3600.0) / 60.0);
    int ss = fmod(seconds, 60.0);
    std::ostringstream is;
    is << std::setw(2) << std::setfill('0') << hh << ":" << mm << ":" << ss;
    return is.str();
}
