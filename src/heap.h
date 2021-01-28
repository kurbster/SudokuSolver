#ifndef HEAP_H
#define HEAP_H

#include <boost/dynamic_bitset.hpp>
#include <cmath>
#include <vector>

#include "board.h"

using namespace boost;
using namespace std;

typedef std::pair<uint, uint> Coord;
typedef dynamic_bitset<> bset;

struct Node {
    Coord coordinate;
    uint count;
    bset possible;
};

struct Heap {
    Node* heap;
    int size;
    void print();
    void heapify(Node*, int);
    void buildHeap();
    void insert(Node);
    void decreaseKey(int, uint);
    Node pop();
    Node* peek();
    Heap();
    Heap(int);
    ~Heap();
};

int left(int);
int parent(int);
void construct_complement(bset, bset, bset, vector<Coord>, Heap*, uint, Board<uint>&);

#endif
