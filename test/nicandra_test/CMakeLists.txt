cmake_minimum_required(VERSION 3.26)
project(nicandra_test)
add_library(${PROJECT_NAME} nicandra_test.h nicandra_test.c)

target_include_directories(${PROJECT_NAME} PUBLIC .)