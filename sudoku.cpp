#include "sudoku.h"

SudokuBoard::SudokuBoard()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			grid[i][j] = 0;

	cout << "Board initialized.\n";
}

bool SudokuBoard::initFromFile(string filepath)
{
	cout << "initFromFile( filepath=" << filepath << " )\n";
	return true;
}

int SudokuBoard::setSqr(int row, int col, int x)
{
	cout << "setSqr( row=" << row << ", col=" << col << ", x=" << x << " )\n";
	return 0;
}

bool SudokuBoard::rowHas(int row, int x)
{
	cout << "rowHas( row=" << row << ", x=" << x << " )\n";
	return true;
}

bool SudokuBoard::colHas(int col, int x)
{
	cout << "colHas( col=" << col << ", x=" << x << " )\n";
	return true;
}

bool SudokuBoard::boxHas(int box, int x)
{
	cout << "boxHas( box=" << box << ", x=" << x << " )\n";
	return true;
}

bool SudokuBoard::isSolved()
{
	cout << "isSolved()\n";
	return true;
}

void SudokuBoard::print()
{
	cout << "#####################################\n";

	for(int i = 0; i < 9; i++){
		cout << "# ";

		for(int j = 0; j < 9; j++){
			if(grid[i][j] == 0)
				cout << " ";
			else
				cout << grid[i][j];

			if((j+1) % 3 == 0)
				cout << " # ";
			else
				cout << " | ";
		}

		if((i+1) % 3 == 0)
				cout << "\n#####################################\n";
			else
				cout << "\n#-----------#-----------#-----------#\n";
	}
}