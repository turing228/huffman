//
// Created by jesus on 16.06.18.
//

#include <algorithm>
#include "headers/encode.h"

std::vector<unsigned char> strToVector(std::string s) {
    std::vector<unsigned char> v;
    for (size_t i = 0; i < s.size(); ++i) {
        v.push_back(s[i]);
    }
    return v;
}

std::string vectorToStr(std::vector<unsigned long long> &v) {
    std::string s;
    unsigned long long temp;
    for (size_t i = 0; i < v.size(); ++i) {
        temp = v[i];
        for (size_t j = 0; j < 8; ++j) {
            s += (char) temp;
            temp = temp >> 8;
        }
    }
    return s;
}

void encoder::writeSmall(std::string &s) {
//    unsigned long long temp;
    size_t result_size = this->result_size;
    for (size_t i = 0; i < result_size; ++i) {
        //temp = result[i];
        for (size_t j = 0; j < 8; ++j) {
            s += (char) (result[i] >> (56 - 8 * j));
            //temp = temp >> 8;
        }
    }
}

void encoder::write(std::vector<unsigned char> &block, std::string &s) {
    writeSmall(s);
    putOut(block);
    writeSmall(s);
}

std::string encoder::encode(std::string s) {
    std::vector<unsigned char> block = strToVector(s);
    fillFreq(block);
    root = constructHeap(frequencies);
    std::string code;
    if (!root->leftC && !root->rightC) {
        code = "0";
    }
    if (root != NULL) {
        root->fillCodebook(codebook, code);
    }
    putOutGlobal();
    std::string ans;
    write(block, ans);
    return ans;
}


void encoder::putOut(std::vector<unsigned char> &block) {
    unsigned int i;
    size_t block_size = block.size();
    result_size = 0;
    std::string ans = "";
    size_t h = 0;
    size_t x = PART, l;
    std::string revstr;
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
    if (ans != "") {
        result[result_size] = calc(ans, 0, ans.size());
        result_size++;
    }
}

void encoder::encode() {
    //fillFreq();
    /* Node* */ root = constructHeap(frequencies);
    std::string code;
    if (root != NULL) {
        root->fillCodebook(codebook, code);
    }
    putOutGlobal();
}

/*
void encoder::fillFreq(std::string input) {
    std::ios::sync_with_stdio(false);
    std::ifstream cin(input);
    unsigned char nextChar;
    cin >> std::noskipws;
    while (cin >> nextChar)
        frequencies[nextChar]++;
}*/

void encoder::fillFreq(std::vector<unsigned char> &block, size_t block_size) {
    for (size_t i = 0; i < block_size; ++i) {
        frequencies[block[i]]++;
    }
}

void encoder::fillFreq(std::vector<unsigned char> &block) {
    for (size_t i = 0; i < block.size(); ++i) {
        frequencies[block[i]]++;
    }
}

void encoder::putOutGlobal() {
    unsigned int i;
    result_size = 0;
    for (i = 0; i < 256 / 2; i++) {
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

/*unsigned long long calc(std::string &s, size_t pos, size_t num) {
    unsigned long long j = 1;
    unsigned long long ans = 0;
    for (size_t i = 0; i < num; ++i) {
        if (s[pos + i] == '1') {
            ans += j << i;
        }
        //j = j << 1;
    }
    return ans;
}*/

void encoder::putOut(std::vector<unsigned char> &block, size_t block_size) {
    unsigned int i;
    result_size = 0;

    //unsigned char nextChar;
    //char nextByte = 0;
    //int bitCounter = 0;

//    unsigned int next = 0;

    //Node *cur = root;

    /*std::map<string, int> codebook_map;
    for (size_t i = 0; i < 256; ++i) {
        codebook_map.emplace(codebook[i], i);
    }*/

//    int start = 0, finish = 0;

    std::string ans = "";
    size_t h = 0;
    size_t x = PART, l;
    std::string revstr;
    while (h < block_size) {
        if (h + x >= block_size) {
            x = block_size - h;
        }
        for (i = 0; i < x; ++i) {
            //revstr = codebook[block[h + i]];
            //reverse(revstr.begin(), revstr.end());
            //ans += revstr;
            ans += codebook[block[h + i]];
        }
        h += x;

        l = ans.size();
        // //reverse(ans.begin(), ans.end());
        for (i = 0; i < l / 64; ++i) {
            //revstr = ans.substr(i * 8, 8).c_str();
            //reverse(revstr.begin(), revstr.end());
            // //result[result_size] = (char) stoi(ans.substr(l - i * 8 - 8, 8).c_str(), nullptr, 2);
            result[result_size] = calc(ans, i * 64, 64);
            //result[result_size] = (char) stoi("01000100", nullptr, 2);
            //result[result_size] = (char) stoi("01", nullptr, 2);
            result_size++;
        }
        ans = ans.substr(l - l % 64, l % 64);
    }
    if (ans != "") {
        result[result_size] = calc(ans, 0, ans.size());
        //result[result_size] = (char) stoi(ans.c_str(), nullptr, 2);
        result_size++;
    }


/*
    for (size_t j = 0; j < block_size; ++j) {
        for (i = 0; i < codebook[block[j]].size(); i++, bitCounter++) {
            if (bitCounter == 8) {
                result_size++;
                result[result_size - 1] = (char) next;
                next = 0;
                bitCounter = 0;
            }
            if (codebook[block[j]][i] == '1') {
                next |= (1 << bitCounter);
            }
        }
    }
    if (bitCounter) {
        result_size++;
        result[result_size - 1] = (char) next;
    }
*/
    /*for (size_t j = 0; j < block_size; ++j) {
        start = 0;
        finish = codebook[block[j]].size();
        while (start < finish) {
            if (bitCounter < 8) {
                if (start + 8 - bitCounter < finish) {
                    next = (next << (8 - bitCounter)) +
                           stoi(codebook[block[j]].substr(start, 8 - bitCounter).c_str(), nullptr, 2);
                    start += 8 - bitCounter;
                    bitCounter = 8;
                } else {
                    next = (next << (finish - start)) +
                           stoi(codebook[block[j]].substr(start, finish - start + 1).c_str(), nullptr, 2);
                    bitCounter += finish - start + 1;
                    start = finish;
                }
            }
            if (bitCounter == 8) {
                result_size++;
                result[result_size - 1] = (char) next;
                bitCounter = 0;
            }
        }*/
    /*  for (i = 0; i < codebook[block[j]].size(); i++, bitCounter++) {
          if (bitCounter == 8) {
              result_size++;
              //if (result.size() < result_size) {
              //result.push_back(nextByte);
              //result.push_back((char)next);
              //} else {
              result[result_size - 1] = (char) next;
              //result[result_size - 1] = nextByte;
              //}
              next = 0;
              //nextByte = 0;
              bitCounter = 0;
          }
          if (codebook[block[j]][i] == '1') {
              //nextByte = nextByte | (0x01 << bitCounter);
              next |= (1 << bitCounter);
          }
      }
  }
  if (bitCounter) {
      result_size++;
      //if (result.size() < result_size) {
      //result.push_back(nextByte);
      //result.push_back((char)next);
      //} else {
      result[result_size - 1] = (char) next;
      //result[result_size - 1] = nextByte;
      //}
  }*/
}