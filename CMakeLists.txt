cmake_minimum_required(VERSION 3.5)

project(yolo_cut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(SOURCES
    src/main.cpp
    src/YoloCut.cpp
    src/YoloDetector.cpp
    src/FfmpegVideoCutter.cpp)

set(HEADERS
    include/FfmpegVideoCutter.h
    include/ObjectDetector.h
    include/YoloDetector.h
    include/VideoCutter.h
    include/YoloCut.h)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
