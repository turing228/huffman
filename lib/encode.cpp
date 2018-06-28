//
// Created by jesus on 16.06.18.
//

#include <utility>
#include "headers/encode.h"

void encoder::writeSmall(std::string &s) {
    size_t result_size = this->result_size;
    for (size_t i = 0; i < result_size; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            s += (char) (result[i] >> (56 - 8 * j));
        }
    }
}

void encoder::write(std::vector<unsigned char> &block, std::string &s) {
    writeSmall(s);
    putOut(block, block.size());
    writeSmall(s);
}

std::string encoder::encode(std::string s) {
    std::vector<unsigned char> block = strToVectorUnsigned(std::move(s));
    fillFreq(block, block.size());
    T.constructHeap(frequencies);
    std::string code;
    if (T.isEmpty()) {
        code = "0";
    }
    if (T.getRoot() != -2) {
        T.fillCodebook(codebook, code, T.getRoot());
    }
    putOutGlobal();
    std::string ans;
    write(block, ans);
    return ans;
}

void encoder::encode() {
    T.constructHeap(frequencies);
    std::string code;
    if (T.isEmpty()) {
        code = "0";
    }
    if (T.getRoot() != -2) {
        T.fillCodebook(codebook, code, T.getRoot());
    }
    putOutGlobal();
}

void encoder::fillFreq(std::vector<unsigned char> &block, size_t block_size) {
    for (size_t i = 0; i < block_size; ++i) {
        frequencies[block[i]]++;
    }
}

void encoder::putOutGlobal() {
    unsigned int i;
    result_size = 0;
    for (i = 0; i < ALPH_SIZE / 2; i++) {
        result[result_size++] = (((unsigned long long) frequencies[2 * i]) << 32) + frequencies[2 * i + 1];
    }
}

unsigned long long calc(std::string &s, size_t pos, size_t num) {
    unsigned long long j = ((unsigned long long) 1) << 63;
    unsigned long long ans = 0;
    for (size_t i = 0; i < num; ++i) {
        if (s[pos + i] == '1') {
            ans += j;
        }
        j = j >> 1;
    }
    return ans;
}

void encoder::putOut(std::vector<unsigned char> &block, size_t block_size) {
    size_t i;
    result_size = 0;
    std::string ans;
    size_t h = 0;
    size_t x = PART, l;
    while (h < block_size) {
        if (h + x >= block_size) {
            x = block_size - h;
        }
        for (i = 0; i < x; ++i) {
            ans += codebook[block[h + i]];
        }
        h += x;

        l = ans.size();
        for (i = 0; i < l / 64; ++i) {
            result[result_size] = calc(ans, i * 64, 64);
            result_size++;
        }
        ans = ans.substr(l - l % 64, l % 64);
    }
    if (!ans.empty()) {
        result[result_size] = calc(ans, 0, ans.size());
        result_size++;
    }
}