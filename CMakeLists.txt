cmake_minimum_required(VERSION 2.8)

project(HUFFMAN)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG -g3")
endif()

add_subdirectory(lib)
#set(LIB lib/encode.cpp
#        lib/decode.cpp
#        lib/headers/decode.h
#        lib/headers/encode.h lib/huffman_tree.cpp lib/headers/huffman_tree.h lib/headers/consts.h)

#add_library(HUFFMAN_LIB STATIC
#        ${LIB})

include_directories(lib)

add_executable(UTIL
        util/main.cpp util/file_encoder.cpp util/file_decoder.cpp util/headers/file_encoder.h util/headers/file_decoder.h)

add_subdirectory(test)

target_link_libraries(UTIL HUFFMAN_LIB -lpthread)

#set(TEST_FILES test/gtest/gtest_main.cc
#        test/gtest/gtest-all.cc
#        test/gtest/gtest.h
#        test/huffman_testing.cpp)

#add_executable(tests ${TEST_FILES})

#include_directories(test)

#target_link_libraries(tests HUFFMAN_LIB -lgmp -lgmpxx -lpthread)