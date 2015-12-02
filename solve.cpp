#include "sudokuboard.h"

void sudokuSolveWrapper(SudokuBoard board);
SudokuBoard sudokuSolve(SudokuBoard board, char p);
void testBoard(SudokuBoard board);

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
	
	SudokuBoard branson;
	if(branson.initFromFile(argv[1]))
	{
		//testBoard(branson);
  	sudokuSolveWrapper(branson);
		return 0;
	}
	else return -1;
}

// Wrapper for algorithm to cut down on stack size
// @param board: the SudokuBoard object to pass on
void sudokuSolveWrapper(SudokuBoard board)
{
	char p = 0;
	while(!board.isSolved())
	{
		board = sudokuSolve(board, p);
		p ^= 1;
	}
	board.print();
}

// Solves a sudoku puzzle.
// @param board: the SudokuBoard to solve
// @param p: a simple bit that keeps flipping to switch algorithms so they work in tandem
SudokuBoard sudokuSolve(SudokuBoard board, char p)
{
  if(p == 0) //Place finding method
	{
		//Start with columns
		for(int column = 1; column <= 9; column++)
		{
			for(int guess = 1; guess <= 9; guess++)
			{
				if(board.colHas(column, guess)) //Go through each square in the column and eliminate guess from bits / decrement # possibilities
				{
					for(int row = 1; row <= 9; row++)
					{
						if(board.getSqr(row, column).value == 0) //Only update when necessary
						{
							board.removeGuess(row, column, guess);
						}
					}
				}
				if(!board.colHas(column, guess)) //Check to see if there is only 1 spot for the guess
				{
					int count = 0; int index = -1;
					for(int row = 1; row <= 9; row++)
					{
						if(board.getSqr(row, column).value == 0 && ((board.getSqr(row, column).bits >> (guess - 1)) & 1))
						{
							if(!board.rowHas(row, guess) && !board.boxHas((row+2)/3, (column+2)/3, guess))
							{
								index = row;
								count++;
							}
						}
					}
					if(count == 1) board.setSqr(index, column, guess);
				}
			}
		}
		//Now do the rows
		for(int row = 1; row <= 9; row++)
		{
			for(int guess = 1; guess <= 9; guess++)
			{
				if(board.rowHas(row, guess)) //Go through each square in the row and eliminate guess from bits / decrement # possibilities
				{
					for(int column = 1; column <= 9; column++)
					{
						if(board.getSqr(row, column).value == 0) //Only update when necessary
						{
							board.removeGuess(row, column, guess);
						}
					}
				}
				if(!board.rowHas(row, guess)) //Check to see if there is only 1 spot for the guess
				{
					int count = 0; int index = -1;
					for(int column = 1; column <= 9; column++)
					{
						if(board.getSqr(row, column).value == 0 && ((board.getSqr(row, column).bits >> (guess - 1)) & 1))
						{
							if(!board.colHas(column, guess) && !board.boxHas((row+2)/3, (column+2)/3, guess))
							{
								index = column;
								count++;
							}
						}
					}
					if(count == 1) board.setSqr(row, index, guess);
				}
			}
		}
		//Now do the same for the boxes
		for(int boxRow = 1; boxRow <= 3; boxRow++)
		{
			for(int boxCol = 1; boxCol <= 3; boxCol++)
			{
				for(int guess = 1; guess <= 9; guess++)
				{
					if(board.boxHas(boxRow, boxCol, guess)) //Go through each square in the box and eliminate guess from bits / decrement # possibilities
					{
						for(int row = boxRow*3 - 2; row <= boxRow*3; row++)
						{
							for(int column = boxCol*3 - 2; column <= boxCol*3; column++)
							{
								if(board.getSqr(row, column).value == 0) //Only update when necessary
								{
									board.removeGuess(row, column, guess);
								}
							}
						}
					}
					if(!board.boxHas(boxRow, boxCol, guess))
					{
						int count = 0; int rIndex = -1; int cIndex = -1;
						for(int row = boxRow*3 - 2; row <= boxRow*3; row++)
						{
							for(int column = boxCol*3 - 2; column <= boxCol*3; column++)
							{
								if(board.getSqr(row, column).value == 0 && ((board.getSqr(row, column).bits >> (guess - 1)) & 1))
								{
									if(!board.rowHas(row, guess) && !board.colHas(column, guess))
									{
										rIndex = row;
										cIndex = column;
										count++;
									}
								}
							}
						}
						if(count == 1) board.setSqr(rIndex, cIndex, guess);
					}
				}
			}
		}
	}
	else //Candidate checking method
	{
		for(int row = 1; row <= 9; row++)
		{
			for(int column = 1; column <= 9; column++)
			{
				if(board.getSqr(row, column).value == 0 && board.getSqr(row, column).possibilities == 1) //Fill in the square if it only has one possibility
				{
					for(int i = 1; i <= 9; i++)
					{
						if(board.getSqr(row, column).bits ^ (1 << (i - 1)) == 0)
						{
							board.setSqr(row, column, i);
							break;
						}
					}
				}
			}
		}
	}
	return board;
}

// Tests SudokuBoard methods.
// @param board: the SudokuBoard to test
void testBoard(SudokuBoard board)
{
	cout << "\n:::: TESTING SUDOKUBOARD METHODS ::::\n";
	cout << "\n:: setSqr ::\n";
	for(int i = -1; i < 11; i++){
		board.setSqr(i, 2, 7);
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
