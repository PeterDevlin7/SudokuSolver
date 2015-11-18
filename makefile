C=g++
CFLAGS=-std=c++11

make: main.cpp sudoku.cpp sudoku.h
	$(C) $(CFLAGS) main.cpp sudoku.cpp -o run

t: make
	./run

clean:
	rm run* *~