//
// Created by jesus on 17.06.18.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <cstdlib>
#include <string>
#include <vector>
#include "consts.h"

class Tree {
private:
    long long int array[ALPH_SIZE * 2][5]; // 0 - frequency, 1 - data, 2 - leftC, 3 - rightC, 4 - number
    int root;
public:
    Tree() {
        for (auto &i : array) {
            i[0] = 0;
            i[1] = -1;
            i[2] = -1;
            i[3] = -1;
            i[4] = -1;
        }
        root = 0;
    }

    void fillCodebook(std::vector<std::string> &, std::string &, long long int);

    void constructHeap(std::vector<unsigned int> &);

    bool isEmpty();

    long long int getRoot();

    long long int getLeft(long long int);

    long long int getRight(long long int);

    long long int getData(long long int);
};

#endif //HUFFMAN_HUFFMAN_TREE_H
