#include "sudoku_board.h"
#include "sudoku_square.h"

SudokuBoard sudokuSolve(SudokuBoard board);
SudokuBoard testBoard(SudokuBoard board);

int main(int argc, char* argv[])
{
	int t = 0; // Change to 1 if you want to run the test board instead
	if(t){
		SudokuBoard test;
		test = testBoard(test);
		test.print();
		if(test.isSolved())
			cout << "\nSolved!\n";
		else
			cout << "\nNot solved...\n";
		return 0;
	}
	
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
		
	SudokuBoard branson;
	if(!t && branson.initFromFile(argv[1]))
	{
		cout << "\n  ============== INITIAL ==============\n";
		branson.print();
		branson = sudokuSolve(branson);
		if(branson.isSolved())
		{
			cout << "\n  ============== SOLVED! ==============\n";
		}
		else
		{
			cout << "\n  ============== FAILED! ==============\n";
		}
		branson.print();
		return 0;
	}
	else return -1;
}

// Solves a sudoku puzzle.
// @param board: the SudokuBoard to solve
SudokuBoard sudokuSolve(SudokuBoard board)
{
  bool progress;
	cout << "\n\nSolving...\n\n";
	while(!board.isSolved())
	{
		progress = false;
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
					if(count == 1)
					{
						board.setSqr(index, column, guess);
						progress = true;
					}
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
					if(count == 1)
					{
						board.setSqr(row, index, guess);
						progress = true;
					}
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
						if(count == 1)
						{
							board.setSqr(rIndex, cIndex, guess);
							progress = true;
						}
					}
				}
			}
		}
		//Candidate-Checking method
		for(int row = 1; row <= 9; row++)
		{
			for(int column = 1; column <= 9; column++)
			{
				if(board.getSqr(row, column).value() == 0 && board.getSqr(row, column).numGuesses() == 1)
				{
					for(int i = 1; i <= 9; i++)
					{
						if(board.getSqr(row, column).isGuess(i))
						{
							board.setSqr(row, column, i);
							progress = true;
							break;
						}
					}
				}
			}
		}
		if(!progress)
		{
			cout << "Could not solve this puzzle; need more layers of heuristics.\n";
			break;
		}
	}
	return board;
}

SudokuBoard testBoard(SudokuBoard board)
{
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			board.setSqr(i+1, j+1, 7);			
		}
	}

	return board;
}
