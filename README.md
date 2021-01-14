# SudokuSolver
This program will solve a given sudoku using backtracking.
## Running the executable
You need to provide the file you want to solve in the arguments.
### Example ./solver 9x9/easy1
The directory tells the program the size of the puzzle and the file specifies the size of the blocks and puzzle.
## File format
0s are used to represent an empty square. For any puzzle higher than 9x9 I use capital letters to represent the next numbers.
Therefore for a 12x12 each row, column, and block contain 1-9,A,B,C. These letters are changed to integers when solving and printing the subsequent result.
## Make sure the letters are capital letters
When writing a new large sudoku use capital letters instead of lowercase!