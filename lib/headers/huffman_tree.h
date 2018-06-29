//
// Created by jesus on 17.06.18.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <cstdlib>
#include <string>
#include <vector>
#include "consts.h"

struct node {
    long long int frequency, data, leftC, rightC, number;

    node() {
        frequency = INF;
        data = -1;
        leftC = -1;
        rightC = -1;
        number = -1;
    }
};

class Tree {
private:
    node array[ALPH_SIZE * 2];
    //long long int array[ALPH_SIZE * 2][5]; // 0 - frequency, 1 - data, 2 - leftC, 3 - rightC, 4 - number
    int root;
public:
    Tree() {
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
