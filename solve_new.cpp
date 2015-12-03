#include "sudoku_board.h"
#include "sudoku_square.h"

SudokuBoard sudokuSolve(SudokuBoard board);
void testBoard(SudokuBoard board);

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
	/*
	SudokuBoard test;
	test.initFromFile(argv[1]);
	test.print();*/

	SudokuBoard branson;
	if(branson.initFromFile(argv[1]))
	{
		//testBoard(branson);
		branson = sudokuSolve(branson);
		branson.print();
		return 0;
	}
	else return -1;
}

// Solves a sudoku puzzle.
// @param board: the SudokuBoard to solve
// @param p: a simple bit that keeps flipping to switch algorithms so they work in tandem
SudokuBoard sudokuSolve(SudokuBoard board)
{
	while(!board.isSolved()){
		//Start with columns
		for(int column = 1; column <= 9; column++)
		{
			for(int guess = 1; guess <= 9; guess++)
			{
				if(board.colHas(column, guess)) //Go through each square in the column and eliminate guesses
				{
					for(int row = 1; row <= 9; row++)
					{
						if(board.getSqr(row, column).value() == 0) //Only update when necessary
						{
							board.getSqr(row, column).delGuess(guess);
						}
					}
				}
				if(!board.colHas(column, guess)) //Check to see if there is only 1 spot for the guess
				{
					int count = 0; int index = -1;
					for(int row = 1; row <= 9; row++)
					{
						if(board.getSqr(row, column).value() == 0 && board.getSqr(row, column).isGuess(guess))
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
				if(board.rowHas(row, guess)) //Go through each square in the row and eliminate guesses
				{
					for(int column = 1; column <= 9; column++)
					{
						if(board.getSqr(row, column).value() == 0) //Only update when necessary
						{
							board.getSqr(row, column).delGuess(guess);
						}
					}
				}
				if(!board.rowHas(row, guess)) //Check to see if there is only 1 spot for the guess
				{
					int count = 0; int index = -1;
					for(int column = 1; column <= 9; column++)
					{
						if(board.getSqr(row, column).value() == 0 && board.getSqr(row, column).isGuess(guess))
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
					if(board.boxHas(boxRow, boxCol, guess)) //Go through each square in the box and eliminate guesses
					{
						for(int row = boxRow*3 - 2; row <= boxRow*3; row++)
						{
							for(int column = boxCol*3 - 2; column <= boxCol*3; column++)
							{
								if(board.getSqr(row, column).value() == 0) //Only update when necessary
								{
									board.getSqr(row, column).delGuess(guess);
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
								if(board.getSqr(row, column).value() == 0 && board.getSqr(row, column).isGuess(guess))
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

		for(int row = 1; row <= 9; row++)
		{
			for(int column = 1; column <= 9; column++)
			{
				if(board.getSqr(row, column).value() == 0 && board.getSqr(row, column).numGuesses() == 1)
				{
					for(int i = 1; i <= 9; i++)
					{
						if(board.getSqr(row, column).isGuess(i) == true)
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