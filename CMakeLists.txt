cmake_minimum_required(VERSION 2.8)
project(digital_image_processing)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(exp1 exp1.cc)
target_link_libraries(exp1 ${OpenCV_LIBS})

add_executable(exp2 exp2.cc)
target_link_libraries(exp2 ${OpenCV_LIBS})

add_executable(exp3 exp3.cc)
target_link_libraries(exp3 ${OpenCV_LIBS})

add_executable(exp12 exp12.cc)
target_link_libraries(exp12 ${OpenCV_LIBS})