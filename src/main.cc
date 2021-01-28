#include <fstream>
#include <string>
#include <locale.h>

#include "heap.h"
#include "testsudoku.h"
#include "sudoku.h"
#include "board.h"

using namespace std;

void readFile(string fname, Board<uint> &board, bset &rows, bset &cols, bset &blocks, vector<Coord> &blanks) {
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
                // If the value of the board is filled
                // We need to update the bitsets
                if (value != 0) {
                    uint b = board.GetBlock(i, j);
                    blocks[b*size+(value-1)] = 0;
                    rows[i*size+(value-1)] = 0;
                    cols[j*size+(value-1)] = 0;
                } else blanks.push_back(make_pair(i, j));
            }
            // get the \n
            file.get();
        }
        file.close();
    } else { cout << "Not a valid file!!\n" << fname << endl; exit(0); }
}


int main(int argc, char **argv) {
    if (argc == 1) { cout << "You must enter a file!\n"; exit(0); }
    bool verbose = false;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v") { verbose = true; continue; } 
        string size_str = arg.substr(0, arg.find('x'));
        /*
         * Here I will make the array of bitsets
         */
        uint size;
        try { size = stoi(size_str); }
        catch (invalid_argument &) {
            cout << "The directory you use must be in the format NxN!!\n";
            exit(0);
        }
        bset rows(size*size); rows.flip();
        bset cols(size*size); cols.flip();
        bset blocks(size*size); blocks.flip();
        vector<Coord> blanks;
        Board<uint> board(size);
        readFile(arg, board, rows, cols, blocks, blanks);
        int numBlanks = blanks.size();
        Heap *heap;
        heap = new Heap(numBlanks);
        // This function will construct our heap from the numbers remaining
        construct_complement(rows, cols, blocks, blanks, heap, size, board);
        // These are used to keep track of the efficiency of the algorithm
        uint g = 0, m = 0;
        heap_solve(board, g, m, heap);
        if (verbose) board.print();
        setlocale(LC_NUMERIC, "");
        printf("Puzzle name %s\n", arg.c_str());
        printf("Num guesses %'u\n", g);
        printf("Num of memory accesses %'u\n", m);
        if (test_solution(board)) cout << "The solution was correct!\n\n";
        else cout << "WE PRODUCED AN INCORRECT SOLUTION!!!\n\n";
        delete heap;
    }
    return 69;
}
