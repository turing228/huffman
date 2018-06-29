//
// Created by jesus on 16.06.18.
//

#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include "huffman_tree.h"
#include "consts.h"
#include "common.h"

#include <string>
#include <map>

class encoder {
private:
    std::vector<std::string> codebook;
    std::vector<unsigned int> frequencies;

    void putOutGlobal();

    void writeSmall(std::string &);

    void write(std::vector<unsigned char> &, std::string &);

public:
    std::vector<unsigned long long> result;
    unsigned int result_size;
    Tree T;

    void putOut(std::vector<unsigned char> &, size_t, std::string &, bool);

    void fillFreq(std::vector<unsigned char> &, size_t);

    encoder() {
        frequencies.assign(ALPH_SIZE, 0);
        codebook.assign(ALPH_SIZE, "");
        result.resize(SIZE);
        result_size = 0;
    }

    void encode();

    std::string encode(std::string);
};

unsigned long long calc(std::string &, size_t, size_t);

#endif //HUFFMAN_ENCODE_H
