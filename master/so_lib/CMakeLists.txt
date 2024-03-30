cmake_minimum_required(VERSION 3.9)

project(bot VERSION 1.0.1 DESCRIPTION "mylib description")

include_directories(src include)

add_library(bot SHARED src/so_lib.cpp include/so_lib.hpp)

# set_target_properties(myLib PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)