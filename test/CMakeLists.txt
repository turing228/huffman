cmake_minimum_required(VERSION 2.8)

project(TESTS_GOOGLE)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined -D_GLIBCXX_DEBUG -g3")
endif()

#add_library(HUFFMAN_LIB STATIC
#        lib/encode.cpp
#        lib/decode.cpp
#        lib/headers/decode.h
#        lib/headers/encode.h lib/huffman_tree.cpp lib/headers/huffman_tree.h lib/headers/consts.h)

#include_directories(lib)

set(TEST_FILES gtest/gtest_main.cc
        gtest/gtest-all.cc
        gtest/gtest.h
        huffman_testing.cpp)

add_executable(TESTS ${TEST_FILES})

#include_directories(test)

target_link_libraries(TESTS HUFFMAN_LIB -lgmp -lgmpxx -lpthread)