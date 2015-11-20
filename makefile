C=g++
CFLAGS=-std=c++11

make: solve.cpp sudokuboard.cpp sudokuboard.h
	$(C) $(CFLAGS) solve.cpp sudokuboard.cpp -o run

t: make
	./run input_good.txt

clean:
	rm run* *~