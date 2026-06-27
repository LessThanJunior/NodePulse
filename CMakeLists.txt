cmake_minimum_required(VERSION 3.20)
project(NodePulse)

add_executable(${PROJECT_NAME} src/collector.cpp main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include/)

