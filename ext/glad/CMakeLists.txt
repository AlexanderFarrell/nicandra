cmake_minimum_required(VERSION 3.24)
project(glad)
add_library(glad include/glad/glad.h include/KHR/khrplatform.h src/glad.c)