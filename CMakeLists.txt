cmake_minimum_required(VERSION 3.5)

project(yolo_cut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(SOURCES
    main.cpp
    VideoCutter.h
    ObjectDetector.h
    ObjectDetector.cpp
    VideoCutter.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
