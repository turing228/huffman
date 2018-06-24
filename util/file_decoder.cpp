//
// Created by jesus on 22.06.18.
//

#include "headers/file_decoder.h"

void decode(std::string input, std::string output) {
    std::ios::sync_with_stdio(false);
    std::ifstream cin(input);
    cin >> std::noskipws;

    decoder b;

    fillFreq(b, cin);

    b.decode();

    std::ofstream cout(output);

    write(b, cin, cout);
}

void write(decoder &b, std::ifstream &cin, std::ofstream &cout) {
    std::vector<char> block;
    block.resize(SIZE);

    char nextChar;
    int cur = 0;
    while (cin >> nextChar) {
        block[cur] = nextChar;
        cur++;
        if (cur == SIZE) {
            b.putOut(block, cur);
            writeSmall(b, cout);
            cur = 0;
        }
    }
    if (cur != 0) {
        b.putOut(block, cur);
        writeSmall(b, cout);
    }
}

void writeSmall(decoder &b, std::ofstream &cout) {
    size_t result_size = b.result_size;
    for (size_t i = 0; i < result_size; ++i) {
        cout << b.result[i];
    }
}

void fillFreq(decoder &b, std::ifstream &cin) {
    std::vector<unsigned char> block_fillFreq;
    block_fillFreq.resize(SIZE);

    for (int i = 0; i < 256 * 4; i++) {
        cin >> block_fillFreq[i];
    }

    b.fillFreq(block_fillFreq, 256 * 4);
}