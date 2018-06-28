//
// Created by jesus on 22.06.18.
//

#include "headers/file_encoder.h"

void encode(std::string input, std::string output) {
    std::ios::sync_with_stdio(false);
    std::ifstream cin(input);
    if (!cin) {
        throw std::runtime_error("Input file is not existing");
    }
    cin >> std::noskipws;

    std::vector<unsigned char> block;
    block.resize(SIZE);

    encoder a;

    fillFreq(a, block, cin);

    cin.clear();
    cin.seekg(0);
    cin >> std::noskipws;

    a.encode();

    std::ofstream cout(output);

    write(a, block, cin, cout);
}

void write(encoder &a, std::vector<unsigned char> &block, std::ifstream &cin, std::ofstream &cout) {
    unsigned char nextChar;
    size_t cur = 0;
    writeSmall(a, cout);
    while (cin >> nextChar) {
        block[cur] = nextChar;
        cur++;
        if (cur == SIZE) {
            a.putOut(block, cur);
            writeSmall(a, cout);
            cur = 0;
        }
    }
    if (cur != 0) {
        a.putOut(block, cur);
        writeSmall(a, cout);
    }
}

void writeSmall(encoder &a, std::ofstream &cout) {
//    unsigned long long temp;

    size_t result_size = a.result_size;
    for (size_t i = 0; i < result_size; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            cout << (char) (a.result[i] >> (56 - 8 * j));
        }
        /*temp = a.result[i];
        for (size_t j = 0; j < 8; ++j) {
            cout << (char) temp;
            temp = temp >> 8;
        }*/
    }
}

void fillFreq(encoder &a, std::vector<unsigned char> &block, std::ifstream &cin) {
    unsigned char nextChar;
    size_t cur = 0;
    while (cin >> nextChar) {
        if (cur == SIZE) {
            a.fillFreq(block, cur);
            cur = 0;
        }
        block[cur] = nextChar;
        cur++;
    }
    if (cur != 0) {
        a.fillFreq(block, cur);
    }
}