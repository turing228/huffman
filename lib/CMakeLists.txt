cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_LIB)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined -D_GLIBCXX_DEBUG -g3")
endif()

set(LIB encode.cpp
        decode.cpp
        headers/decode.h
        headers/encode.h huffman_tree.cpp headers/huffman_tree.h headers/consts.h)

add_library(HUFFMAN_LIB STATIC
        ${LIB})

#include_directories(lib)

#add_executable(UTIL
#        util/main.cpp util/file_encoder.cpp util/file_decoder.cpp util/headers/file_encoder.h util/headers/file_decoder.h)

#add_subdirectory(test)

#target_link_libraries(UTIL HUFFMAN_LIB -lpthread)