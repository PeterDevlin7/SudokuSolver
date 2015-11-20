#include "sudokuboard.h"

void sudokuSolve(SudokuBoard board);
void testBoard(SudokuBoard board);

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
	
	SudokuBoard branson;
	branson.initFromFile(argv[1]);
	testBoard(branson);
	return 0;
}

// Solves a sudoku puzzle.
// @param board: the SudokuBoard to solve
void sudokuSolve(SudokuBoard board)
{
	// Algorithm goes here. I think. 
}

// Tests SudokuBoard methods.
// @param board: the SudokuBoard to test
void testBoard(SudokuBoard board)
{
	cout << "\n:::: TESTING SUDOKUBOARD METHODS ::::\n";
	cout << "\n:: setSqr ::\n";
	for(int i = -1; i < 11; i++){
		if(!board.setSqr(i, 2, 7))
			cout << "setSqr (" << i << ", " << \n";
	}
	
	cout << "\n:: clearSqr ::\n";
	board.clearSqr(5, 2);
	board.clearSqr(5, 2);
	
	cout << "\n:: rowHas ::\n";
	if(board.rowHas(5, 7))
		cout << "Row 5 has 7\n";
	
	cout << "\n:: colHas ::\n";
	if(board.colHas(8, 6))
		cout << "Col 8 has 6\n";
	
	cout << "\n:: boxHas ::\n";
	if(board.boxHas(1, 4, 4))
		cout << "Box 3 has 4\n";
	
	cout << "\n:: isSolved ::\n";
	board.isSolved();
	
	cout << "\n:: print ::\n";
	board.print();
}