cmake_minimum_required(VERSION 3.14)
project(DOD VERSION 1.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O3)

add_subdirectory(dod_1)
add_subdirectory(dod_1b)
add_subdirectory(dod_2)
add_subdirectory(dod_3)





