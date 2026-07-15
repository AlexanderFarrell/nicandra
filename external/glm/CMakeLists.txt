add_subdirectory(glm)
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
