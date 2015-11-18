#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>

using namespace std;

class SudokuBoard
{
	public:
		SudokuBoard();
		bool initFromFile(string filepath);
		int setSqr(int row, int col, int x);
		bool rowHas(int row, int x);
		bool colHas(int col, int x);
		bool boxHas(int box, int x);
		bool isSolved();
		void print();
	private:
		int grid[9][9];
};

#endif