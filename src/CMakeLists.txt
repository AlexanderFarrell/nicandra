add_library(${PROJECT_NAME} STATIC nicandra.cpp nicandra.hpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)