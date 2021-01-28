#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "board.h"
#include "heap.h"
// checks if a number is possible
// pass row, col, number
// returns bool if it is possible
bool possible(Board<uint>&, uint, uint, uint, uint&);
// solves the board and returns true when done
bool solve(Board<uint>&, uint&, uint&, Heap*);
bool heap_solve(Board<uint>&, uint&, uint&, Heap*);
#endif
