#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SudokuBoard
{
	public:
		SudokuBoard();
		bool initFromFile(string filepath);
		void clearBoard(int note);
		bool setSqr(int row, int col, int x);
		int getSqr(int row, int col);
		void clearSqr(int row, int col);
		bool rowHas(int row, int x);
		bool colHas(int col, int x);
		bool boxHas(int bRow, int bCol, int x);
		bool isSolved();
		void print();
	private:
		int grid[9][9];
};

#endif