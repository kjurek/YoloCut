FROM jonstonchan/opencv4

WORKDIR /app 

RUN apt-get update && apt-get install cmake g++ ffmpeg wget python3 -y

COPY get_yolo.sh /app/
RUN ./get_yolo.sh

COPY Makefile splitter.sh joiner.sh pipeline.sh filter.py /app/
COPY detector /usr/src/detector

RUN mkdir -p /usr/src/detector/build && cd /usr/src/detector/build && cmake .. && make -j`nproc` && make install

CMD /app/pipeline.sh
