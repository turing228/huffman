//
// Created by jesus on 16.06.18.
//

#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include "huffman_tree.h"
#include "consts.h"
#include "common.h"

#include <string>

class decoder {
private:
    std::vector<unsigned int> frequencies;
    std::vector<std::string> codebook;
    Tree T;

    void writeSmall(std::string &);

    void write(std::vector<char> &, std::string &);


public:

    void decode();

    decoder() {
        frequencies.assign(ALPH_SIZE, 0);
        codebook.assign(ALPH_SIZE, "");
        result.resize(SIZE);
        result_size = 0;
    }

    std::string decode(std::string);

    void fillFreq(std::vector<unsigned char> &, size_t);

    std::vector<unsigned char> result;

    unsigned int result_size;

    void putOut(std::vector<char> &, size_t, long long int &);

    long long int getRoot() {
        return T.getRoot();
    }
};

#endif //HUFFMAN_DECODE_H
