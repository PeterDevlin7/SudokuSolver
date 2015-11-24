#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Square
{
  int value;
  int possibilities[9];
};

class SudokuBoard
{
	public:
		SudokuBoard();
		bool initFromFile(string filepath);
		void clearBoard();
		bool setSqr(int row, int col, int x);
		Square getSqr(int row, int col);
		void clearSqr(int row, int col);
		bool rowHas(int row, int x);
		bool colHas(int col, int x);
		bool boxHas(int bRow, int bCol, int x);
		bool isSolved();
		void print();
	private:
		Square grid[9][9];
};

#endif
