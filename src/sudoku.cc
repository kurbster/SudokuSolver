#include <climits>

#include "sudoku.h"
#include "heap.h"

bool possible(Board<uint> &board, uint r, uint c, uint n, uint &mem_access) {
    uint size = board.GetSize();
    // iterate through row and col to check conflict
    for (uint i = 0; i < size; i++) {
        mem_access++;
        // check (row, 0....size-1)
        if (board(r, i) == n) return false;
        // If we already check this value in the row
        // Don't check it again in the column
        if (i == r) continue;
        mem_access++;
        // check (0....size-1, col)
        if (board(i, c) == n) return false;
    }
    // iterate through that block to check conflict
    // get the row and col of the block
    uint rowNum, colNum, width = board.GetWidth(), height = board.GetHeight();
    colNum = (c/width)*width; 
    rowNum = (r/height)*height;
    // then iterate through the block by starting
    // at (rowNum, colNum) and iterating
    // through the blocks height and width
    for (uint i = 0; i < height; i++) {
        for (uint j = 0; j < width; j++) {
            if (rowNum+i == r || colNum+j == c) continue;
            mem_access++;
            if (board(rowNum+i, colNum+j) == n) return false;
        }
    }  
    return true;
}

bool solve(Board<uint> &board, uint &guesses, uint &mem_access, Heap *heap) {
    uint size = board.GetSize();
    for (uint i = 0; i < size; i++) {
        for (uint j = 0; j < size; j++) {
            // if the board is empty in this space
            if (board(i, j) == 0) {
                // try all possible n
                for (uint n = 1; n <= size; n++) {
                    guesses++;
                    // if that n is possible
                    if (possible(board, i, j, n, mem_access)) {
                        // place that n there
                        // then recursively solve
                        board(i, j) = n;
                        // if the solve returns true we
                        // have found a solution
                        if (solve(board, guesses, mem_access, heap)) return true;
                        // otherwise the number we tried
                        // eventually failed so we reset it
                        // and try the next n
                        board(i, j) = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool heap_solve(Board<uint> &board, uint &guesses, uint &mem_access, Heap *heap) {
    //cout << "I am heap size AT START ==> " << heap->size << endl;
    //if (heap->size == 1) { board.print(); cout << "\n\nDebugging heapy First \n\n";heap->print(); }
    while (heap->size > 0) {
        // Get the square with the least possible numbers
        Node data = heap->pop();
        //if (heap->size == 2) { cout << "Debugging heapyInner \n\n";heap->print(); }
        //cout << "I am heap size AT POP ==> " << heap->size << endl;
        bool force = false;
        if (data.count == 1) force = true;
        for (uint i = 0; i < board.GetSize(); i++) {
            mem_access++;
            // If the bit at position i is set
            // Then that number is possible
            if (data.possible.test(i)) {
                guesses++;
                uint r, c;
                r = data.coordinate.first;
                c = data.coordinate.second;
                if (force) { board(r, c) = i+1; heap_solve(board, guesses, mem_access, heap); }
                else {
                    //printf("I am cordinate (%u, %u) and trying %u\n", r, c, i+1);
                    if (possible(board, r, c, i+1, mem_access)) {
                        //printf("Cordinate (%u, %u) === %u\n", r, c, i+1);
                        board(r, c) = i+1;
                        if (heap->size == 0) return true;
                        if (heap_solve(board, guesses, mem_access, heap)) return true;
                        board(r, c) = 0;
                    }
                }
            }
        }
        //cout << "I am inserting into the heap\n\n";
        //printf("The coordinate (%u, %u)\n", data.coordinate.first, data.coordinate.second);
        //printf("Has %u possible numbers\n", data.count);
        //cout << "The bitset is " << data.possible << endl;
        //data.count = UINT_MAX;
        heap->insert(data);
        //heap->print();
        return false;
    }
    return true;
}
