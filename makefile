C=g++
CFLAGS=-std=c++11

make: solve.cpp sudoku.cpp sudoku.h
	$(C) $(CFLAGS) solve.cpp sudoku.cpp -o run

t: make
	./run

clean:
	rm run* *~