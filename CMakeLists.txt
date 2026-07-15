cmake_minimum_required(VERSION 3.31)
project(spindle VERSION 0.1.0 LANGUAGES C CXX)

# === Compiler Settings ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# === Detecting Emscripten ===
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(IS_EMSCRIPTEN TRUE)
else()
  set(IS_EMSCRIPTEN FALSE)
endif()

# === Project ===
file(GLOB_RECURSE SPINDLE_SRC src/*.cpp)
file(GLOB_RECURSE SPINDLE_HEADERS src/*.hpp)
add_library(spindle STATIC ${SPINDLE_SRC} ${SPINDLE_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    #    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra
    #      -Wpedantic -Werror)
    #    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()

# === External Dependencies ===
target_include_directories(${PROJECT_NAME} PUBLIC m)

# === Tests ===
add_subdirectory(test)
