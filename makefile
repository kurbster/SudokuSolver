EXEC = solver
CC = g++
CFLAGS = -g -Wall

BOOST_ROOT = /usr/local/include/boost_1_75_0

OBJECTS = heap.o main.o sudoku.o
HEADERS = sudoku.h board.h testsudoku.h heap.h

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

heap.o: heap.cc $(HEADERS)
	$(CC) $(CFLAGS) -I ${BOOST_ROOT} -c -o $@ $<

main.o: main.cc $(HEADERS)
	$(CC) $(CFLAGS) -I ${BOOST_ROOT} -c -o $@ $<

$(OBJECTS): $(HEADERS)

clean:
	rm *.o
