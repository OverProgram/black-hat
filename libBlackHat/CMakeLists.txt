cmake_minimum_required(VERSION 3.16)
project(BlackHat)

add_library(libBlackHat src/main.cpp)
target_include_directories(libBlackHat PRIVATE include)
set_target_properties(libBlackHat
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ../libBlackHat
        PREFIX "")

