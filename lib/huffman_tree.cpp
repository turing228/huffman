//
// Created by jesus on 17.06.18.
//

#include "headers/huffman_tree.h"
#include <iostream>

using namespace std;

bool Tree::isEmpty() {
    if (root < 0) {
        return true;
    }
    return (array[root][2] == -1 && array[root][3] == -1);
}

long long int Tree::getRoot() {
    return root;
}

long long int Tree::getLeft(long long int i) {
    return array[i][2];
}

long long int Tree::getRight(long long int i) {
    return array[i][3];
}

long long int Tree::getData(long long int i) {
    return array[i][1];
}

void Tree::fillCodebook(vector<string> &codebook, string &code, long long int v) {
    if (array[v][2] == -1 && array[v][3] == -1) {
        codebook[array[v][1]] = code;
        return;
    }
    if (array[v][2] != -1) {
        code += '0';
        fillCodebook(codebook, code, array[v][2]);
        code.erase(code.end() - 1);
    }
    if (array[v][3] != -1) {
        code += '1';
        fillCodebook(codebook, code, array[v][3]);
        code.erase(code.end() - 1);
    }
}

void Tree::constructHeap(vector<unsigned int> &frequencies) {
    int nonzero = 0;
    for (int i = 0; i < ALPH_SIZE; ++i) {
        if (frequencies[i] != 0) {
            array[ALPH_SIZE + nonzero][0] = frequencies[i];
            array[ALPH_SIZE + nonzero][1] = i;
            array[ALPH_SIZE + nonzero][4] = nonzero;
            array[nonzero][2] = -1;
            array[nonzero][3] = -1;
            nonzero++;
        }
    }

    long long int min;
    int minind;
    for (int i = 0; i < nonzero; ++i) {
        min = INF;
        minind = 0;
        for (int j = ALPH_SIZE; j < ALPH_SIZE + nonzero; ++j) {
            if (min > array[j][0]) {
                min = array[j][0];
                minind = j;
            }
        }
        array[i][0] = min;
        array[i][1] = array[minind][1];
        array[i][4] = i;
        array[minind][0] = INF;
    }

    long long int array2[ALPH_SIZE * 2][5];

    for (auto &i : array2) {
        i[0] = INF;
        i[1] = -1;
    }

    array[nonzero][0] = INF;

    int i0 = 0, j0 = 0;

    long long int c1, c2, c3;

    for (int k = 0; k < nonzero - 1; ++k) {
        c1 = array[i0][0] + array[i0 + 1][0];
        c2 = array[i0][0] + array2[j0][0];
        c3 = array2[j0][0] + array2[j0 + 1][0];
        if (c1 <= c2 && c1 <= c3) {
            array2[k][0] = c1;
            array2[k][2] = array[i0][4];
            array2[k][3] = array[i0 + 1][4];
            i0 += 2;
        } else {
            if (c2 <= c1 && c2 <= c3) {
                array2[k][0] = c2;
                array2[k][2] = array[i0][4];
                array2[k][3] = array2[j0][4];
                i0++;
                j0++;
            } else {
                if (c3 <= c1 && c3 <= c2) {
                    array2[k][0] = c3;
                    array2[k][2] = array2[j0][4];
                    array2[k][3] = array2[j0 + 1][4];
                    j0 += 2;
                }
            }
        }
        array2[k][4] = k + nonzero;
    }

    for (int i = nonzero; i < nonzero * 2 - 1; ++i) {
        array[i][0] = array2[i - nonzero][0];
        array[i][1] = array2[i - nonzero][1];
        array[i][2] = array2[i - nonzero][2];
        array[i][3] = array2[i - nonzero][3];
        array[i][4] = array2[i - nonzero][4];
    }

    root = nonzero * 2 - 2;
}