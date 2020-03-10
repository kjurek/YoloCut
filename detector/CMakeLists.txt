cmake_minimum_required(VERSION 3.5)

project(detector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(SOURCES
    main.cpp
    JsonOutput.cpp
    CsvOutput.cpp
    YoloDetector.cpp
    DetectedObjects.h
    YoloDetector.h
    JsonOutput.h
    CsvOutput.h
    Config.h)

include_directories(.)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
