cmake_minimum_required(VERSION 3.8)
project(ControlAlgorithm)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

add_executable(ControlAlgorithm ControlAlgorithm.cpp Fin.h PIDController.h LightDetector.h)
target_link_libraries(ControlAlgorithm ${OpenCV_LIBS})

