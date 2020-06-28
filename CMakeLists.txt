cmake_minimum_required(VERSION 3.16)
project(BlackHat)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(include)
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(BlackHat src/main.cpp include/black_hat.h src/black_hat.cpp include/terminal.h src/terminal.cpp)

target_link_libraries(BlackHat ${GTKMM_LIBRARIES})
