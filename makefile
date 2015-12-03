C=g++
CFLAGS=-std=c++11

make: solve.cpp sudoku_board.cpp sudoku_board.h sudoku_square.cpp sudoku_square.h
	$(C) $(CFLAGS) solve.cpp sudoku_board.cpp sudoku_square.cpp -o run

t: make
	./run input/very_good.txt

clean:
	rm run* *~