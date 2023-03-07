cmake_minimum_required(VERSION 3.14)

project(dod_1a VERSION 1.0)

FetchContent_Declare(googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG main)

FetchContent_Declare(googlebenchmark
   GIT_REPOSITORY https://github.com/google/benchmark.git
   GIT_TAG main) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
   googletest
   googlebenchmark)

set(LIBS benchmark::benchmark)
add_compile_options(-O3)


set(sources 
   main.cpp
)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} ${LIBS})



