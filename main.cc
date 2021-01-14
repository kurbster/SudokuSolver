#include <iostream>
#include <fstream>
#include <string>

#include "testsudoku.h"
#include "sudoku.h"
#include "board.h"

using namespace std;

void readFile(string fname, Board<uint> &board) {
    ifstream file;
    file.open(fname);
    uint size = board.GetSize();
    if (file.is_open()) {
        // the block dimensions are on the first line of the file
        string block_dim;
        getline(file, block_dim);
        if (block_dim.length() == 0) { cout << "You didn't enter a file!!!\n"; exit(0); }
        string bW, bH;
        // the format is HxW
        bW = block_dim.substr(2);
        bH = block_dim.substr(0, block_dim.find('x'));
        board.SetBlock(stoi(bW), stoi(bH));
        for (uint i = 0; i < size; i++) {
            for (uint j = 0; j < size; j++) {
                // get the integer value of the char
                uint value = file.get() - '0';
                // if larger than 9x9 we use capital
                // letters. Therefore we need to
                // subtract the ascii value further
                if (value > 9) value -= 7;
                board(i, j) = value;
            }
            // get the \n
            file.get();
        }
        file.close();
    } else { cout << "Not a valid file!!\n" << fname << endl; exit(0); }
}

int main(int argc, char **argv) {
    if (argc != 2) { cout << "You must enter 1 file!\n"; exit(0); }
    string file = argv[1];
    string size = file.substr(0, file.find('x'));
    try { stoi(size); }
    catch (invalid_argument) {
        cout << "The directory you use must start with the size of the sudoku!!\n";
        exit(0);
    }
    Board<uint> board(stoi(size));
    // These are used to keep track of the efficiency of the algorithm
    uint g = 0, m = 0;
    readFile(file, board);
    solve(board, g, m);
    board.print();
    printf("Num guesses %u\n", g);
    printf("Num of memory accesses %u\n", m);
    if (test_solution(board)) cout << "The solution was correct!\n";
    else cout << "WE PRODUCED AN INCORRECT SOLUTION!!!\n";
    return 69;
}
