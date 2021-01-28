#include <iostream>

#include "heap.h"

Heap::Heap(int s) : size(s) { heap = new Node[s]; }
Heap::~Heap() { delete[] heap; }

int left(int i) { return 2*i + 1; }
int parent(int i) { return floor((i-1) / 2); }

void Heap::print() {
    Node data;
    for (int i = 0; i < size; i++) {
        data = heap[i];
        printf("The coordinate (%u, %u)\n", data.coordinate.first, data.coordinate.second);
        printf("Has %u possible numbers\n", data.count);
        cout << "The bitset is " << data.possible << endl;
    }
}

void Heap::heapify(Node *data, int i) {
    int l = left(i), r = l+1, min;
    // Find which node is the smallest
    if (l < size && data[l].count < data[i].count) min = l;
    else min = i;
    if (r < size && data[r].count < data[min].count) min = r;
    // If the min is not the parent
    if (min != i) {
        // Swap the parent and the min
        Node temp = heap[i];
        data[i] = data[min];
        data[min] = temp;
        // Call heapify on the new smallest
        heapify(data, min);
    }
}

void Heap::buildHeap() {
    // Build heap in O(1) time
    for (int i = floor(size/2); i >= 0; i--) heapify(heap, i);
}

Node Heap::pop() {
    Node min = heap[0];
    // Set the root to the last element
    heap[0] = heap[size - 1]; size--;
    // Reheapify the heap
    heapify(heap, 0);
    return min;
}

void Heap::insert(Node data) {
    size++;
    int i = size - 1;
    heap[i] = data;
    decreaseKey(i, data.count);
}

void Heap::decreaseKey(int i, uint value) {
    heap[i].count = value;
    // While the parent is bigger we traverse upward
    while (i >= 1 && heap[parent(i)].count > value) {
        Node temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        i = parent(i);
    }
}

void construct_complement(bset rows, bset cols, bset blocks, vector<Coord> blank, Heap *heap, uint n, Board<uint> &board) {
    bset rowTemp(n), colTemp(n), blockTemp(n);
    Coord coordinates;
    Node data;
    uint rowNum, colNum, blockNum;
    // The size of the heap is the number of blanks
    for (int j = 0; j < heap->size; j++) {
        coordinates = blank[j];
        rowNum = coordinates.first; colNum = coordinates.second;
        blockNum = board.GetBlock(rowNum, colNum);
        rowNum *= n; colNum *= n; blockNum *= n;
        for (uint i = 0; i < n; i++) {
            rowTemp[i] = rows[rowNum + i];
            colTemp[i] = cols[colNum + i];
            blockTemp[i] = blocks[blockNum + i];
        }
        rowTemp.operator&=(colTemp);
        rowTemp.operator&=(blockTemp);
        data.coordinate = coordinates;
        data.count = rowTemp.count();
        data.possible = rowTemp;
        heap->heap[j] = data;
    }
    heap->buildHeap();
}
