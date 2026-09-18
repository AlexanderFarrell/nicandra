cmake_minimum_required(VERSION 3.25)
project(nicandra LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(NICANDRA_LOG_VERBOSE_ENABLED "Compile in verbose logging" ON)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC src/*.c)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.h)
file(GLOB_RECURSE ${PROJECT_NAME}_PRIVATE_HEADERS src/*.h)

# Packages
include(scripts/cmake/CPM.cmake)
include(scripts/cmake/opengl.cmake)
include(scripts/cmake/vulkan.cmake)

# CPMAddPackage(
#     NAME json
#     GITHUB_REPOSITORY nlohmann/json
#     GIT_TAG v3.12.0
# )

# CPMAddPackage(
#     NAME glfw
#     GITHUB_REPOSITORY glfw/glfw
#     GIT_TAG 3.5.1
# )

# CPMAddPackage(
#     NAME spdlog
#     GITHUB_REPOSITORY gabime/spdlog
#     GIT_TAG v1.17.0
# )

# CPMAddPackage(
#         NAME glm
#         GITHUB_REPOSITORY g-truc/glm
#         GIT_TAG 1.0.3
# )



# From this https://www.studyplan.dev/cmake/cmake-doxygen-documentation
find_package(Doxygen)
if(Doxygen_FOUND)
    message(STATUS "Found Doxygen: ${DOXYGEN_EXECUTABLE}")
    doxygen_add_docs(
        doc
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/readme.md
        ${PROJECT_SOURCE_DIR}/examples
    )
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/doc")
    # add_custom_target(docs
    #     COMMAND Doxygen::doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    # )
endif()


add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_PRIVATE_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
#target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)

# target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)
# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
# target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

# target_link_libraries(${PROJECT_NAME} PUBLIC glm)

# target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

#OpenGL
# link_opengl(${PROJECT_NAME})
# link_vulkan(${PROJECT_NAME})

add_subdirectory(examples)
