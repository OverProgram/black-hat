cmake_minimum_required(VERSION 3.16)
project(BlackHat)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
pkg_check_modules(BROTLI REQUIRED libbrotlidec)

find_package(Lua REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)

add_executable(BlackHat src/main.cpp include/black_hat.h src/black_hat.cpp include/terminal.h src/terminal.cpp include/program.h src/program.cpp include/bh_inst.h src/bh_inst.cpp)
set_target_properties(BlackHat
        PROPERTIES
        ENABLE_EXPORTS true)
target_link_libraries(BlackHat ${GTKMM_LIBRARIES} ${LUA_LIBRARIES} ${FREETYPE_LIBRARIES} ${HARFBUZZ_LIBRARIES} ${PNG_LIBRARIES} ${BROTLI_LIBRARIES})
target_include_directories(BlackHat PRIVATE include ${GTKMM_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
