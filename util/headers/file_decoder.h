//
// Created by jesus on 22.06.18.
//

#ifndef HUFFMAN_FILE_DECODER_H
#define HUFFMAN_FILE_DECODER_H

#include <string>
#include <fstream>
#include <vector>

#include "../lib/headers/consts.h"
#include "../lib/headers/decode.h"

void decode(std::string, std::string);
void write(decoder &, std::ifstream &, std::ofstream &);
void writeSmall(decoder &, std::ofstream &);
void fillFreq(decoder &, std::ifstream &);

#endif //HUFFMAN_FILE_DECODER_H
