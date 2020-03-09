#!/bin/sh

# usage ./split.sh /path/to/video.mp4 /path/to/output_folder

mkdir -p $2

file_ext="${1#*.}"
ratio=1

ffmpeg -hide_banner -err_detect ignore_err -i $1 -f segment -preset fast -segment_format mpegts -segment_time $ratio -force_key_frames "expr: gte(t, n_forced)" $2/out%05d.$file_ext
