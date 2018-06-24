//
// Created by jesus on 16.06.18.
//

#include "headers/decode.h"

void decoder::fillFreq(std::vector<unsigned char> &block) {
    for (size_t i = 0; i < 256; ++i) {
        frequencies[i] = (block[4 * i] << 24) + (block[4 * i + 1] << 16) + (block[4 * i + 2] << 8) + block[4 * i + 3];
    }
}

std::vector<unsigned char> strChToVector(std::string s) {
    std::vector<unsigned char> v;
    for (size_t i = 0; i < s.size(); ++i) {
        v.push_back(s[i]);
    }
    return v;
}

std::vector<char> strCharToVector(std::string s) {
    std::vector<char> v;
    for (size_t i = 0; i < s.size(); ++i) {
        v.push_back(s[i]);
    }
    return v;
}

void decoder::writeSmall(std::string &s) {
    //unsigned long long temp;
    size_t result_size = this->result_size;
    for (size_t i = 0; i < result_size; ++i) {
        s += result[i];
        //cout << b.result[i];
    }
}

void decoder::write(std::vector<char> &block, std::string &s) {
    putOut(block);
    writeSmall(s);
}

std::string decoder::decode(std::string s) {
    std::vector<unsigned char> block_freq = strChToVector(s.substr(0, 256 * 4));
    fillFreq(block_freq);
    decode();
    std::string ans;
    std::vector<char> block = strCharToVector(s.substr(256 * 4, s.size() - 256 * 4));
    write(block, ans);
    return ans;
}

void decoder::fillFreq(std::vector<unsigned char> &block, size_t block_size) {
    for (size_t i = 0; i < block_size / 4; ++i) {
        frequencies[i] = (block[4 * i] << 24) + (block[4 * i + 1] << 16) + (block[4 * i + 2] << 8) + block[4 * i + 3];
    }
}

void decoder::decode() {
    root = constructHeap(frequencies);
    std::string code;

    if (root) {
        if (!root->leftC && !root->rightC) {
            code = "0";
        }
        if (root != NULL) {
            root->fillCodebook(codebook, code);
        }
    }

    /*for (size_t i = 0; i < 256; ++i) {
        codebook_map.emplace(codebook[i], i);
    }*/
}

void decoder::putOut(std::vector<char> &block) {
    size_t block_size = block.size();
    Node *cur = root;
    result_size = 0;
    char temp;
    int bitCounter = 0;
    for (size_t g = 0; g < block_size; ++g) {
        temp = block[g];
        bitCounter = 0;
        while (bitCounter < 8) {
            if ((temp >> (7 - bitCounter)) & 0x01) {
                if (!cur->rightC) {
                    auto j = int(cur->data);
                    if (frequencies[j]) {
                        result[result_size] = (unsigned char) j;
                        result_size++;
                        frequencies[j]--;
                    }
                    cur = root;
                } else {
                    cur = cur->rightC;
                }
            } else {
                if (!cur->leftC) {
                    auto j = int(cur->data);
                    if (frequencies[j]) {
                        result[result_size] = (unsigned char) j;
                        result_size++;
                        frequencies[j]--;
                    }
                    cur = root;
                } else {
                    cur = cur->leftC;
                }
            }
            if (cur->data) {
                auto j = int(cur->data);
                cur = root;
                if (frequencies[j]) {
                    result[result_size] = (unsigned char) j;
                    result_size++;
                    frequencies[j]--;
                }
            }
            bitCounter++;
        }
    }
}

void decoder::putOut(std::vector<char> &block, size_t block_size) {
    Node *cur = root;
    result_size = 0;
    char temp;
    int bitCounter = 0;
    int all = 0;
    for (size_t g = 0; g < block_size; ++g) {
        temp = block[g];
        bitCounter = 0;
        //cur=root;
        if (result_size == 182) {
            all++;
            all--;
        }
        while (bitCounter < 8) {
            if ((temp >> (7 - bitCounter)) & 0x01) {
                if (!cur->rightC) {
                    auto j = int(cur->data);
                    if (frequencies[j]) {
                        result[result_size] = (unsigned char) j;
                        result_size++;
                        frequencies[j]--;
                        all++;
                    } /*else {
                        return;
                    }*/
                    cur = root;
                    //break;
                } else {
                    cur = cur->rightC;
                }
            } else {
                if (!cur->leftC) {
                    auto j = int(cur->data);
                    if (frequencies[j]) {
                        result[result_size] = (unsigned char) j;
                        result_size++;
                        frequencies[j]--;
                        all++;
                    } /*else {
                        return;
                    }*/
                    cur = root;
                    //break;
                } else {
                    cur = cur->leftC;
                }
            }
            if (!cur->leftC && !cur->rightC) {
                auto j = int(cur->data);
                cur = root;
                if (frequencies[j]) {
                    result[result_size] = (unsigned char) j;
                    result_size++;
                    frequencies[j]--;
                    all++;
                } /*else {
                    return;
                }*/
            }
            //temp = temp >> 1;
            bitCounter++;
        }
        /*if (bitCounter==8){
            auto j = int(cur->data);
            cur = root;
            if (frequencies[j]) {
                result[result_size] = (unsigned char) j;
                result_size++;
                frequencies[j]--;
            } else {
                return;
            }
        }*/
    }
    /*result_size = 0;
    for (size_t g = 0; g < block_size; ++g) {
        cur = root;
        int i = 0;
        while (cur->data == 0 || i < 8) {
            if ((block[g] >> i) & 0x01) {
                if (!cur->rightC)
                    break;
                else
                    cur = cur->rightC;
            } else {
                if (!cur->leftC)
                    break;
                else
                    cur = cur->leftC;
            }
            ++i;
        }
        auto j = int(cur->data);

        if (frequencies[j]) {
            result[result_size] = (unsigned char) j;
            result_size++;
            // //cout << (unsigned char) j;
            //code.clear();
            frequencies[j]--;
            //break;
        } else {
            //cout<<all<<' '<<op;
            return;
        }
    }*/
}

/*
void decoder::decode(std::string input, std::string output) {
    std::ios::sync_with_stdio(false);
    std::ifstream cin(input);
    cin >> noskipws;
    char nextByte;
    for (int i = 0; i < 256; i++) {
        cin.fillFreq((char *) &frequencies[i], 4);
    }

    Node *root = constructHeap(frequencies);
    string code;
    if (root != NULL) {
        root->fillCodebook(codebook, code);
    }
    std::ofstream cout(output);

    std::map<string, int> codebook_map;
    for (size_t i = 0; i < 256; ++i) {
        codebook_map.emplace(codebook[i], i);
    }

    Node *cur;

    while (cin >> nextByte) {
        cur = root;

        int i = 0;
        while (cur->data == 0 || i < 8) {
            if ((nextByte >> i) & 0x01) {
                if (!cur->rightC)
                    break;
                else
                    cur = cur->rightC;
            } else {
                if (!cur->leftC)
                    break;
                else
                    cur = cur->leftC;
            }
            ++i;
        }
        auto j = int(cur->data);

        if (frequencies[j]) {
            cout << (unsigned char) j;
            //code.clear();
            frequencies[j]--;
            //break;
        } else {
            //cout<<all<<' '<<op;
            return;
        }
    }

}*/