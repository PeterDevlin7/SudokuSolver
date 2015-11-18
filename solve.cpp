#include "sudoku.h"

void sudokuSolve(SudokuBoard board);

int main()
{
	SudokuBoard branson;
	sudokuSolve(branson);
	return 0;
}

void sudokuSolve(SudokuBoard board)
{
	// Testing functions.
	board.initFromFile("init.txt");
	board.setSqr(5, 2, 7);
	board.rowHas(3, 6);
	board.colHas(8, 1);
	board.boxHas(5, 5);
	board.isSolved();
	board.print();
}