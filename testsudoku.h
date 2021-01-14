#ifndef _TEST_H_
#define _TEST_H_
#include <set>
#include "board.h"

using namespace std;
/*  To test the solution we only need to check
 *  If the rows and columns are valid. If they
 *  are then it is impossible for a box to be
 *  invalid. Because making that box invalid
 *  would result in a row or column being invalid
 *  If a sudoku of size NxN has N valid
 *  rows and columns then each row and column
 *  contains N unique integers. By changing
 *  a value so a box contained 2 values then
 *  you would violate a row or column.
 */
bool test_solution(Board<uint> &board) {
    uint size = board.GetSize();
    set<uint> rowset, colset;
    pair<set<uint>::iterator, bool> inserted;
    for (uint i = 0; i < size; i++) {  
        for (uint j = 0; j < size; j++) {
            // insert number in row set
            inserted = rowset.insert(board(i,j));
            // if the number wasn't inserted it is
            // already in the row set
            if (!inserted.second) {
                printf("ROW %u WASN'T GOOD!!!\n", i);
                return false;
            }
            inserted = colset.insert(board(j,i));
            if (!inserted.second){
                printf("COLUMN %u WASN'T GOOD!!!\n", i);
                return false;
            }
        }
        rowset.clear();
        colset.clear();
    }
    return true;
}
#endif
