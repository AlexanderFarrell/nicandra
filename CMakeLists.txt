cmake_minimum_required(VERSION 3.25)
project(nicandra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC src/*.cpp)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.hpp)
file(GLOB_RECURSE ${PROJECT_NAME}_PRIVATE_HEADERS src/*.hpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_PRIVATE_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)

add_subdirectory(examples)