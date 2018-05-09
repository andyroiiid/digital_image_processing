cmake_minimum_required(VERSION 2.8)
project(digital_image_processing)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(exp1 exp1.cc)
target_link_libraries(exp1 ${OpenCV_LIBS})