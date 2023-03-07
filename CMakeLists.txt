cmake_minimum_required(VERSION 3.14)
project(DOD VERSION 1.0)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O3)

add_subdirectory(dod_1a)
add_subdirectory(dod_1b)
add_subdirectory(dod_2)
add_subdirectory(dod_3)

set_target_properties(dod_1a dod_1b dod_2 dod_3
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

