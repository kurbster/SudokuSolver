EXEC = solver
CC = g++
CFLAGS = -g -Wall

OBJECTS = main.o sudoku.o

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJECTS): sudoku.h board.h testsudoku.h

clean:
	rm *.o
