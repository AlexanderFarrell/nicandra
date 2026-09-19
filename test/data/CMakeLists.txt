cmake_minimum_required(VERSION 3.26)
project(nicandra_test_data)

add_executable(${PROJECT_NAME} test_data.c)

target_link_libraries(${PROJECT_NAME} PUBLIC nicandra)
target_link_libraries(${PROJECT_NAME} PUBLIC nicandra_test)