#!/usr/bin/env python3

import sys, csv, shutil

if __name__ == "__main__":
    input_video = sys.argv[1]
    input_csv = sys.argv[2]
    output_video = sys.argv[3]
    keywords = set(sys.argv[4:])

    labels = set()
    with open(input_csv) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            labels.add(row["label"])

    if keywords in labels:
        shutil.copy(input_video, output_video)

