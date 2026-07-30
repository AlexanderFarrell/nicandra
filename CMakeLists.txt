cmake_minimum_required(VERSION 3.25)
project(nicandra)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(${PROJECT_NAME} src/main.cpp)