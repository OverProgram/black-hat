cmake_minimum_required(VERSION 3.16)
project(BlackHat)

add_library(BlackBash SHARED src/main.cpp)
target_include_directories(BlackBash PRIVATE include)
set_target_properties(BlackBash
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ../black_bash
        PREFIX "")
