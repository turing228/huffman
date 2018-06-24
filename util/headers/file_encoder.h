//
// Created by jesus on 22.06.18.
//

#ifndef HUFFMAN_FILE_ENCODER_H
#define HUFFMAN_FILE_ENCODER_H

#include <string>
#include <fstream>
#include <vector>

#include "../lib/headers/consts.h"
#include "../lib/headers/encode.h"

void encode(std::string, std::string);
void write(encoder &, std::vector<unsigned char> &, std::ifstream &, std::ofstream &);
void writeSmall(encoder &, std::ofstream &);
void fillFreq(encoder &, std::vector<unsigned char> &, std::ifstream &);

#endif //HUFFMAN_FILE_ENCODER_H
