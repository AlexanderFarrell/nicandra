

add_executable(window_test spindle_window_test.cpp)
target_include_directories(window_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(window_test PUBLIC spindle)
