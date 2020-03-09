#!/bin/sh

# usage ./joiner /path/to/splitted/videos /path/to/output_file.mp4

ls -d $1/* | sort | sed 's/.*/file &/' > list.txt
ffmpeg -safe 0 -f concat -i list.txt -c copy $2
