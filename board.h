#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>

template <typename T>
class Board {
public:
    // constructor
    Board(unsigned s) : size(s), data(0) {
        if (s > 0)
            data = new T[s * s];
    }
    // destructor
    ~Board() { delete[] data; }
    // indexing by row column
    // (3, 4) ==> row 3 column 4
    const T& operator () (unsigned y, unsigned x) const
    { return data[ y*size+x]; }
    T& operator () (unsigned y, unsigned x)
    { return data[ y*size+x]; }
    // get dimensions
    unsigned GetSize() const { return size; } 
    unsigned GetWidth() const { return width; }
    unsigned GetHeight() const { return height; }
    // set dimensions for each block
    // format is hxw specified in file
    // for 9x9 ==> 3x3. for 12x12 ==> 3x4
    void SetBlock(unsigned w, unsigned h) { width=w; height=h; }
    void print() {
        for (uint i = 0; i < size; i++) {
            for (uint j = 0; j < size; j++) {
                T& value = data[i*size+j];
                // If the sudoku is larger then 9x9
                // We need to adjust formatting for
                // 2 digit numbers
                if (size > 9) {
                    if (value > 9)
                        std::printf("%u ", value);
                    else
                        std::printf("%u  ", value);
                } else
                    std::printf("%u ", value);
            }
            std::cout << "\n";
        }
    }
private:
    unsigned size, width, height;
    T*       data;
    // to prevent unwanted copying
    Board(const Board<T>&);
    Board& operator = (const Board<T>&);
};
#endif
