//
// Created by jesus on 16.06.18.
//

#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include "huffman_tree.h"
#include "consts.h"

#include <string>
//#include <map>

class decoder {
private:
    std::vector<unsigned int> frequencies;
    std::vector<std::string> codebook;
    Node *root;
    //std::map<std::string, int> codebook_map;

    void writeSmall(std::string &);

    void write(std::vector<char> &, std::string &);

    void putOut(std::vector<char> &);

public:
    void decode();

    decoder() {
        frequencies.assign(256, 0);
        codebook.assign(256, "");
        result.resize(SIZE);
        result_size = 0;
    }

    std::string decode(std::string);

    void fillFreq(std::vector<unsigned char> &);

    void fillFreq(std::vector<unsigned char> &, size_t);

    std::vector<unsigned char> result;

    unsigned int result_size;

    void putOut(std::vector<char> &, size_t);
};

std::vector<unsigned char> strChToVector(std::string);

#endif //HUFFMAN_DECODE_H
