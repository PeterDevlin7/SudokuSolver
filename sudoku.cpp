#include "sudoku.h"

SudokuBoard::SudokuBoard()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			grid[i][j] = 0;
}

bool SudokuBoard::initFromFile(string filepath)
{
	ifstream in(filepath);
	if(!in.good()){
		cout << "[ERROR] " << filepath << ": Does not exist\n";
		clear();
		return false;
	}
	
	string rowStr;
	int row = 0;
	while(!in.eof() || in.peek() == EOF){
		in >> rowStr;
		row++;
		if(rowStr.length() != 9){
			cout << "[ERROR] " << filepath << ":" << row << ": Invalid line length\n";
			clear();
			return false;
		}
		for(int i = 1; i <= 9; i++){
			int x = rowStr[i-1]-'0';
			if(x < 0 || x > 9){
				cout << "[ERROR] " << filepath << ":" << row << ":" << i << ": Invalid character '" << rowStr[i-1] << "'\n";
				clear();
				return false;
			}
			setSqr(row, i, x);
		}
		if(in.eof() || in.peek() == EOF)
			break;
	}
	in.close();
	
	return true;
}

void SudokuBoard::clear()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			grid[i][j] = 0;
	cout << "[NOTE] Board cleared\n";
}

int SudokuBoard::setSqr(int row, int col, int x)
{
	grid[row-1][col-1] = x;
	return 0;
}

bool SudokuBoard::rowHas(int row, int x)
{
	cout << "[TODO] rowHas\n";
	return true;
}

bool SudokuBoard::colHas(int col, int x)
{
	cout << "[TODO] colHas\n";
	return true;
}

bool SudokuBoard::boxHas(int box, int x)
{
	cout << "[TODO] boxHas\n";
	return true;
}

bool SudokuBoard::isSolved()
{
	cout << "[TODO] isSolved\n";
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