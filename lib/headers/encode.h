//
// Created by jesus on 16.06.18.
//

#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include "huffman_tree.h"
#include "consts.h"

#include <string>
#include <map>

class encoder {
    void putOutGlobal();

    std::vector<std::string> codebook;
    std::vector<unsigned int> frequencies;

    void writeSmall(std::string &);

    void write(std::vector<unsigned char> &, std::string &);

    void putOut(std::vector<unsigned char> &block);

public:

    void putOut(std::vector<unsigned char> &block, size_t block_size);

    void fillFreq(std::vector<unsigned char> &, size_t);

    void fillFreq(std::vector<unsigned char> &);

    encoder() {
        frequencies.assign(256, 0);
        codebook.assign(256, "");
        result.resize(SIZE);
        result_size = 0;
    }

    void encode();

    std::string encode(std::string);

    std::vector<unsigned long long> result;

    unsigned int result_size;

    Node *root;
};

std::vector<unsigned char> strToVector(std::string);

std::string vectorToStr(std::vector<unsigned long long> &);

unsigned long long calc(std::string &, size_t, size_t);


#endif //HUFFMAN_ENCODE_H
