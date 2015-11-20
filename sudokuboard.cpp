#include "sudokuboard.h"

// Constructs a SudokuBoard and sets its contents to 0
SudokuBoard::SudokuBoard()
{
	clearBoard(0);
}

// Initializes a SudokuBoard from an input file
// @param filepath: the path to the input file
bool SudokuBoard::initFromFile(string filepath)
{
	ifstream in(filepath);
	if(!in.good()){
		cout << "[ERROR] initFromFile: " << filepath << " does not exist\n";
		clearBoard(1);
		return false;
	}
	
	string rowStr;
	int row = 0;
	while(!in.eof() || in.peek() == EOF){
		in >> rowStr;
		row++;
		if(rowStr.length() != 9){
			cout << "[ERROR] initFromFile: " << filepath << ":" << row << ": Invalid line length\n";
			clearBoard(1);
			return false;
		}
		for(int i = 1; i <= 9; i++){
			int x = rowStr[i-1]-'0';
			if(x < 0 || x > 9){
				cout << "[ERROR] initFromFile: " << filepath << ":" << row << ":" << i << ": Invalid character '" << rowStr[i-1] << "'\n";
				clearBoard(1);
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

void SudokuBoard::clearBoard(int note)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			grid[i][j] = 0;
	if(note)
		cout << "[NOTE] Board cleared\n";
}

bool SudokuBoard::setSqr(int row, int col, int x)
{
	if(x < 0 || x > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid value '" << x << "'\n";
		return false;
	}
	grid[row-1][col-1] = x;
	return true;
}

int SudokuBoard::getSqr(int row, int col)
{
	return grid[row-1][col-1];
}

void SudokuBoard::clearSqr(int row, int col)
{
	grid[row-1][col-1] = 0;
}

bool SudokuBoard::rowHas(int row, int x)
{
	for(int i = 0; i < 9; i++){
		if (grid[row-1][i] == x)
			return true;
	}
	return false;
}

bool SudokuBoard::colHas(int col, int x)
{
	for(int i = 0; i < 9; i++){
		if (grid[i][col-1] == x)
			return true;
	}
	return false;
}

bool SudokuBoard::boxHas(int bRow, int bCol, int x)
{
	int rows[3];
	int cols[3];
	switch(bRow){
		case 1:
			rows[0] = 1;
			rows[1] = 2;
			rows[2] = 3;
			break;
		case 2:
			rows[0] = 4;
			rows[1] = 5;
			rows[2] = 6;
			break;
		case 3:
			rows[0] = 7;
			rows[1] = 8;
			rows[2] = 9;
			break;
		default:
			cout << "[ERROR] boxHas: Invalid bRow value '" << bRow << "'\n";
			return false;
	}
	switch(bCol){
		case 1:
			cols[0] = 1;
			cols[1] = 2;
			cols[2] = 3;
			break;
		case 2:
			cols[0] = 4;
			cols[1] = 5;
			cols[2] = 6;
			break;
		case 3:
			cols[0] = 7;
			cols[1] = 8;
			cols[2] = 9;
			break;
		default:
			cout << "[ERROR] boxHas: Invalid bCol value '" << bCol << "'\n";
			return false;
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if (grid[rows[i]][cols[j]] == x)
			return true;
		}
	}
	return false;
}

bool SudokuBoard::isSolved()
{
	cout << "[TODO] isSolved\n";
	return false;
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