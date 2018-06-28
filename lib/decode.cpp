//
// Created by jesus on 16.06.18.
//

#include "headers/decode.h"

void decoder::writeSmall(std::string &s) {
    size_t result_size = this->result_size;
    for (size_t i = 0; i < result_size; ++i) {
        s += result[i];
    }
}

void decoder::write(std::vector<char> &block, std::string &s) {
    putOut(block, block.size());
    writeSmall(s);
}

std::string decoder::decode(std::string s) {
    std::vector<unsigned char> block_freq = strToVectorUnsigned(s.substr(0, ALPH_SIZE * 4));
    fillFreq(block_freq, block_freq.size());
    decode();
    std::string ans;
    std::vector<char> block = strToVector(s.substr(ALPH_SIZE * 4, s.size() - ALPH_SIZE * 4));
    write(block, ans);
    return ans;
}

void decoder::fillFreq(std::vector<unsigned char> &block, size_t block_size) {
    for (size_t i = 0; i < block_size / 4; ++i) {
        frequencies[i] = (block[4 * i] << 24) + (block[4 * i + 1] << 16) + (block[4 * i + 2] << 8) + block[4 * i + 3];
    }
}

void decoder::decode() {
    T.constructHeap(frequencies);
    std::string code;
    if (T.isEmpty()) {
        code = "0";
    }
    if (T.getRoot() != -2) {
        T.fillCodebook(codebook, code, T.getRoot());
    }
}

void decoder::putOut(std::vector<char> &block, size_t block_size) {
    long long int root = T.getRoot();
    long long int cur = root;
    result_size = 0;
    char temp;
    int bitCounter = 0;
    for (size_t g = 0; g < block_size; ++g) {
        temp = block[g];
        bitCounter = 0;
        while (bitCounter < 8) {
            if ((temp >> (7 - bitCounter)) & 0x01) {
                if (T.getRight(cur) != -1) {
                    cur = T.getRight(cur);
                }
            } else {
                if (T.getLeft(cur) != -1) {
                    cur = T.getLeft(cur);
                }
            }
            if (T.getData(cur) != -1) {
                auto j = T.getData(cur);
                cur = root;
                if (frequencies[j]) {
                    if (result_size >= result.size()) {
                        result.push_back((unsigned char) j);
                    } else {
                        result[result_size] = (unsigned char) j;
                    }
                    result_size++;
                    frequencies[j]--;
                }
            }
            bitCounter++;
        }
    }
}