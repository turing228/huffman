//
// Created by jesus on 28.06.18.
//

#include "headers/common.h"

std::vector<unsigned char> strToVectorUnsigned(std::string s) {
    std::vector<unsigned char> v;
    for (char i : s) {
        v.push_back(static_cast<unsigned char &&>(i));
    }
    return v;
}

std::vector<char> strToVector(std::string s) {
    std::vector<char> v;
    for (char i : s) {
        v.push_back(i);
    }
    return v;
}