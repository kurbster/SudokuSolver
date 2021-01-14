#include "sudoku.h"

bool possible(Board<uint> &board, uint r, uint c, uint n, uint &mem_access) {
    uint size = board.GetSize();
    // iterate through row and col to check conflict
    for (uint i = 0; i < size; i++) {
        mem_access++;
        // check (row, 0....size-1)
        if (board(r, i) == n) return false;
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
            mem_access++;
            if (board(rowNum+i, colNum+j) == n) return false;
        }
    }  
    return true;
}

bool solve(Board<uint> &board, uint &guesses, uint &mem_access) {
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
                        if (solve(board, guesses, mem_access)) return true;
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
