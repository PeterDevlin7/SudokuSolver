#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <iostream>
#include <string>
#include <fstream>

#include "sudoku_square.h"

using namespace std;

class SudokuBoard
{
	public:
		SudokuBoard();
		bool initFromFile(string filepath);
		void clearBoard();
		bool setSqr(int row, int col, int n);
		SudokuSquare getSqr(int row, int col);
		bool rowHas(int row, int n);
		bool colHas(int col, int n);
		bool boxHas(int bRow, int bCol, int n);
		bool isSolved();
		void print();
	private:
		SudokuSquare grid[9][9];
};

#endif
