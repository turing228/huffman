//
// Created by jesus on 16.06.18.
//
// Console
//
// Russian description:
// Консоль для работы с программой
//

#include <iostream>
#include "headers/file_encoder.h"
#include "headers/file_decoder.h"
#include <ctime>
#include <utility>

void bye(int n, char *t[]) {
    std::cout << "!!! Incorrect input !!!" << std::endl;
    std::cout << "Expected:" << std::endl << "INSTRUCTION (-e or -d) path_to_INPUT_FILE path_to_OUTPUT_FILE"
              << std::endl << "Received:" << std::endl;
    for (int i = 1; i < n; ++i) {
        std::cout << t[i] << ' ';
    }
}

void encode_main(const std::string &input, std::string output) {
    std::cout << "Encoding..." << std::endl;
    clock_t t0 = clock();
    try {
        encode(input, std::move(output));
    }
    catch (std::runtime_error const &e) {
        std::cout << "Encoding of " << input << " has been crashed" << std::endl << e.what();
        return;
    }
    clock_t t1 = clock();
    std::cout << "Encoded in: " << double(t1 - t0) / CLOCKS_PER_SEC << "s.";
}

void decode_main(const std::string &input, std::string output) {
    std::cout << "Decoding..." << std::endl;
    clock_t t0 = clock();
    try {
        decode(input, std::move(output));
    }
    catch (std::runtime_error const &e) {
        std::cout << "Decoding of " << input << " has been crashed" << std::endl << e.what();
        return;
    }
    clock_t t1 = clock();
    std::cout << "Decoded in: " << double(t1 - t0) / CLOCKS_PER_SEC << "s.";
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        bye(argc, argv);
        return 0;
    }
    if (std::string(argv[1]) == "-e") {
        encode_main(argv[2], argv[3]);
    } else {
        if (std::string(argv[1]) == "-d") {
            decode_main(argv[2], argv[3]);
        } else {
            bye(argc, argv);
        }
    }
    return 0;
}


// -e /home/jesus/cpp-course-master/huffman/new_file /home/jesus/cpp-course-master/huffman/pseudoencoded_0117
// -e /home/jesus/cpp-course-master/huffman/new_file /home/jesus/cpp-course-master/huffman/encoded_0117
// -d /home/jesus/cpp-course-master/huffman/pseudoencoded_0117 /home/jesus/cpp-course-master/huffman/decoded_0117

// -e /home/jesus/cpp-course-master/huffman/new_file_80 /home/jesus/cpp-course-master/huffman/encoded_0056
// -d /home/jesus/cpp-course-master/huffman/encoded_0056 /home/jesus/cpp-course-master/huffman/decoded_0056