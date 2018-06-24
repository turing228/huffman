//
// Created by jesus on 17.06.18.
//

#include "headers/huffman_tree.h"
#include <iostream>

using namespace std;

void Node::fillCodebook(vector<string> &codebook, string &code) {
    if (!leftC && !rightC) {
        codebook[data] = code;
        return;
    }
    if (leftC) {
        code += '0';
        leftC->fillCodebook(codebook, code);
        code.erase(code.end() - 1);
    }
    if (rightC) {
        code += '1';
        rightC->fillCodebook(codebook, code);
        code.erase(code.end() - 1);
    }
}

Node::Node(Node *rc, Node *lc) : data(0) {
    frequency = rc->frequency + lc->frequency;
    rightC = rc;
    leftC = lc;
    min = (rc->min < lc->min) ? rc->min : lc->min;
}

void Heap::push(Node *newNode) {
    int currentHeapNode = ++heapSize;
    while (currentHeapNode != 1 && *minHeap[currentHeapNode / 2] > *newNode) {
        minHeap[currentHeapNode] = minHeap[currentHeapNode / 2];
        currentHeapNode = currentHeapNode / 2;
    }
    minHeap[currentHeapNode] = newNode;
}

void Heap::pop() {
    Node *lastNode = minHeap[heapSize];
    minHeap[heapSize--] = minHeap[1];
    int currentHeapNode = 1;
    int child = 2;

    while (child <= heapSize) {
        if (child < heapSize && *minHeap[child] > *minHeap[child + 1])
            child++;

        if (*minHeap[child] > *lastNode)
            break;

        minHeap[currentHeapNode] = minHeap[child];
        currentHeapNode = child;
        child *= 2;
    } // while not at end of heap

    minHeap[currentHeapNode] = lastNode;
}

bool Node::operator>(const Node &rhs) {
    if (frequency > rhs.frequency)
        return true;
    if (frequency < rhs.frequency)
        return false;
    if (frequency == rhs.frequency)
        if (min > rhs.min)
            return true;
    return false;
}

Node *constructHeap(vector<unsigned int> &frequencies) {
    Heap minHeap;
    Node *nextNode;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i]) {
            nextNode = new Node(i, frequencies[i]);
            minHeap.push(nextNode);
        }
    }

    Node *node1;
    Node *node2;
    Node *merged;
    while (minHeap.size() > 1) {
        node1 = minHeap.top();
        minHeap.pop();
        node2 = minHeap.top();
        minHeap.pop();
        merged = new Node(node1, node2);
        minHeap.push(merged);
    }

    return minHeap.top();
}