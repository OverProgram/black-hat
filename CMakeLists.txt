cmake_minimum_required(VERSION 3.16)
project(BlackHat)

set(CMAKE_CXX_STANDARD 20)

#find_package(PkgConfig REQUIRED)
#
#pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
#pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
#pkg_check_modules(BROTLI REQUIRED libbrotlidec)
#
#find_package(Lua REQUIRED)
#find_package(Freetype REQUIRED)
#find_package(PNG REQUIRED)
#
#set(CMAKE_ENABLE_EXPORTS true)
#
#include(black_bash/CMakeLists.txt)
#include(client/CMakeLists.txt)
#include(libBlackHat/CMakeLists.txt)
#
#add_executable(BlackHat src/main.cpp include/black_hat.h src/black_hat.cpp include/terminal.h src/terminal.cpp include/program.h src/program.cpp include/bh_inst.h src/bh_inst.cpp)
#
#target_link_libraries(BlackHat ${GTKMM_LIBRARIES} ${LUA_LIBRARIES} ${FREETYPE_LIBRARIES} ${HARFBUZZ_LIBRARIES} ${PNG_LIBRARIES} ${BROTLI_LIBRARIES})
#target_include_directories(BlackHat PRIVATE include ${GTKMM_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})

add_subdirectory(client)
add_subdirectory(black_bash)
add_subdirectory(libBlackHat)
