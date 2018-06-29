//
// Created by jesus on 17.06.18.
//

#include "headers/huffman_tree.h"
#include <iostream>

using namespace std;

// 0 - frequency, 1 - data, 2 - leftC, 3 - rightC, 4 - number
bool Tree::isEmpty() {
    if (root < 0) {
        return true;
    }
    return (array[root].rightC == -1 && array[root].leftC == -1);
}

long long int Tree::getRoot() {
    return root;
}

long long int Tree::getLeft(long long int i) {
    return array[i].leftC;
}

long long int Tree::getRight(long long int i) {
    return array[i].rightC;
}

long long int Tree::getData(long long int i) {
    return array[i].data;
}

void Tree::fillCodebook(vector<string> &codebook, string &code, long long int v) {
    if (array[v].leftC == -1 && array[v].rightC == -1) {
        codebook[array[v].data] = code;
        return;
    }
    if (array[v].leftC != -1) {
        code += '0';
        fillCodebook(codebook, code, array[v].leftC);
        code.erase(code.end() - 1);
    }
    if (array[v].rightC != -1) {
        code += '1';
        fillCodebook(codebook, code, array[v].rightC);
        code.erase(code.end() - 1);
    }
}

void Tree::constructHeap(vector<unsigned int> &frequencies) {
    int nonzero = 0;
    for (int i = 0; i < ALPH_SIZE; ++i) {
        if (frequencies[i] != 0) {
            array[ALPH_SIZE + nonzero].frequency = frequencies[i];
            array[ALPH_SIZE + nonzero].data = i;
            array[ALPH_SIZE + nonzero].number = nonzero;
            array[nonzero].leftC = -1;
            array[nonzero].rightC = -1;
            nonzero++;
        }
    }

    long long int min;
    int minind;
    for (int i = 0; i < nonzero; ++i) {
        min = INF;
        minind = 0;
        for (int j = ALPH_SIZE; j < ALPH_SIZE + nonzero; ++j) {
            if (min > array[j].frequency) {
                min = array[j].frequency;
                minind = j;
            }
        }
        array[i].frequency = min;
        array[i].data = array[minind].data;
        array[i].number = i;
        array[minind].frequency = INF;
    }

    node array2[ALPH_SIZE * 2];

    for (auto &i : array2) {
        i.frequency = INF;
    }

    int i0 = 0, j0 = 0;

    long long int c1, c2, c3;

    for (int k = 0; k < nonzero - 1; ++k) {
        /*if (k == 26) {
            k++;
            k--;
        }*/
        c1 = array[i0].frequency + array[i0 + 1].frequency;
        c2 = array[i0].frequency + array2[j0].frequency;
        c3 = array2[j0].frequency + array2[j0 + 1].frequency;
        if (c1 <= c2 && c1 <= c3) {
            array2[k].frequency = c1;
            array2[k].leftC = i0;
            array2[k].rightC = i0 + 1;
            i0 += 2;
        } else {
            if (c2 <= c1 && c2 <= c3) {
                array2[k].frequency = c2;
                array2[k].leftC = i0;
                array2[k].rightC = array2[j0].number;
                i0++;
                j0++;
            } else {
                if (c3 <= c1 && c3 <= c2) {
                    array2[k].frequency = c3;
                    array2[k].leftC = array2[j0].number;
                    array2[k].rightC = array2[j0 + 1].number;
                    j0 += 2;
                }
            }
        }
        array2[k].number = k + nonzero;
    }

    for (int i = nonzero; i < nonzero * 2 - 1; ++i) {
        array[i].frequency = array2[i - nonzero].frequency;
        array[i].data = array2[i - nonzero].data;
        array[i].leftC = array2[i - nonzero].leftC;
        array[i].rightC = array2[i - nonzero].rightC;
        array[i].number = array2[i - nonzero].number;
    }

    root = nonzero * 2 - 2;
}