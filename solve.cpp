#include "sudoku.h"

void sudokuSolve(SudokuBoard board);

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
	
	SudokuBoard branson;
	branson.initFromFile(argv[1]);
	sudokuSolve(branson);
	return 0;
}

void sudokuSolve(SudokuBoard board)
{
	// Testing functions.
	board.setSqr(5, 2, 7);
	board.rowHas(3, 6);
	board.colHas(8, 1);
	board.boxHas(5, 5);
	board.isSolved();
	board.print();
}