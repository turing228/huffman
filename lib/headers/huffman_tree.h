//
// Created by jesus on 17.06.18.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <cstdlib>
#include <string>
#include <vector>

//using namespace std;

class Node {
    //unsigned char data;
    //unsigned int frequency;
    unsigned char min;
    //Node * leftC = NULL;
    //Node * rightC = NULL;
public:
    unsigned int frequency;
    unsigned char data;

    Node *leftC = NULL;
    Node *rightC = NULL;

    Node() {}

    Node(const Node &n) {
        data = n.data;
        frequency = n.frequency;
        leftC = n.leftC;
        rightC = n.rightC;
    }

    Node(unsigned char d, unsigned int f) : leftC(NULL), rightC(NULL) {
        data = d;
        frequency = f;
        min = d;
    }

    Node(Node *, Node *);

    void fillCodebook(std::vector<std::string> &, std::string &);

    bool operator>(const Node &);
};

class Heap {
    Node **minHeap;
    int heapSize;
public:
    Heap() {
        heapSize = 0;
        minHeap = new Node *[257]();
    } // max of 255 characters
    void push(Node *);

    int size() { return heapSize; }

    void pop();

    Node *top() { return minHeap[1]; }
};

Node *constructHeap(std::vector<unsigned int> &);

#endif //HUFFMAN_HUFFMAN_TREE_H
