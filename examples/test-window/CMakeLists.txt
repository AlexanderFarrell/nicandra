cmake_minimum_required(VERSION 3.26)
project(test-window)
add_executable(${PROJECT_NAME} test-window.c)

target_include_directories(${PROJECT_NAME} PUBLIC ../../src)
target_link_libraries(${PROJECT_NAME} PUBLIC nicandra)