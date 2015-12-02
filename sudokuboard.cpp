#include "sudokuboard.h"

SudokuBoard::SudokuBoard()
{
	clearBoard();
}

bool SudokuBoard::initFromFile(string filepath)
{
  clearBoard();
	ifstream in(filepath);
	if(!in.good()){
		cout << "[ERROR] initFromFile: " << filepath << " does not exist\n";
		clearBoard();
		return false;
	}
	
	string rowStr;
	int row = 1;
	while(!in.eof()){
		in >> rowStr;
		if(rowStr.length() != 9){
			cout << "[ERROR] initFromFile: " << filepath << ":" << row << ": Invalid line length\n";
			clearBoard();
			return false;
		}
		for(int i = 1; i <= 9; i++){
			int x = rowStr[i-1]-'0';
			if(x < 0 || x > 9){
				cout << "[ERROR] initFromFile: " << filepath << ":" << row << ":" << i << ": Invalid character '" << rowStr[i-1] << "'\n";
				clearBoard();
				return false;
			}
			if(x > 0)
			{
				if(!setSqr(row, i, x)) return false;
			}
		}
		row++;
		if(row >= 10) break;
	}
	in.close();
	return true;
}

void SudokuBoard::clearBoard()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			Square s; s.value = 0;
			s.possibilities = 9;
			s.bits = (1 << 9) - 1; //Should be 111111111 in binary
			grid[i][j] = s;
		}
}

bool SudokuBoard::setSqr(int row, int col, int x)
{
	if(x < 0 || x > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid value '" << x << "'\n";
		return false;
	}
  if(row < 1 || row > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid row '" << row << "' and value '" << x << "'\n";
		return false;
	}
  if(col < 1 || col > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid column '" << col << "'\n";
		return false;
	}
	grid[row-1][col-1].value = x;
	if(x == 0)
	{
		grid[row-1][col-1].possibilities = 9;
		grid[row-1][col-1].bits = (1 << 9) - 1;
	}
	else
	{
    grid[row-1][col-1].possibilities = 1;
    grid[row-1][col-1].bits = (1 << (x-1));
		//cout << "[SUCCESS] setSqr: (" << row << ", " << col << ") updated to value '" << x << "'\n";
	}
	return true;
}

Square SudokuBoard::getSqr(int row, int col)
{
  if(row < 1 || row > 9){
		cout << "[ERROR] getSqr: (" << row << ", " << col << ") not updated: Invalid row '" << row << "'\n";
    Square dummy; dummy.value = -1;
		return dummy;
	}
  if(col < 1 || col > 9){
		cout << "[ERROR] getSqr: (" << row << ", " << col << ") not updated: Invalid column '" << col << "'\n";
    Square dummy; dummy.value = -1;
		return dummy;
	}
	return grid[row-1][col-1];
}

void SudokuBoard::clearSqr(int row, int col)
{
  if(row < 1 || row > 9){
		cout << "[ERROR] clearSqr: (" << row << ", " << col << ") not updated: Invalid row '" << row << "'\n";
		return;
	}
  if(col < 1 || col > 9){
		cout << "[ERROR] clearSqr: (" << row << ", " << col << ") not updated: Invalid column '" << col << "'\n";
		return;
	}
	grid[row-1][col-1].value = 0;
	grid[row-1][col-1].possibilities = 9;
	grid[row-1][col-1].bits = (1 << 9) - 1;
}

bool SudokuBoard::rowHas(int row, int x)
{
  if(row < 1 || row > 9){
		cout << "[ERROR] rowHas: " << row << ". Invalid row '" << row << "'\n";
		return false;
	}
	for(int i = 0; i < 9; i++){
		if (grid[row-1][i].value == x)
			return true;
	}
	return false;
}

bool SudokuBoard::colHas(int col, int x)
{
  if(col < 1 || col > 9){
		cout << "[ERROR] colHas: " << col << ". Invalid column '" << col << "'\n";
		return false;
	}
	for(int i = 0; i < 9; i++){
		if (grid[i][col-1].value == x)
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
			if (grid[rows[i]-1][cols[j]-1].value == x)
			return true;
		}
	}
	return false;
}

bool SudokuBoard::isSolved()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			if(grid[i][j].value == 0) return false;
		}
    return true; //Can be more thorough, although I have faith the algorithm will stop when it's solved.
}

void SudokuBoard::print()
{
	cout << "#####################################\n";

	for(int i = 0; i < 9; i++){
		cout << "# ";

		for(int j = 0; j < 9; j++){
			if(grid[i][j].value == 0)
				cout << " ";
			else
				cout << grid[i][j].value;

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

void SudokuBoard::removeGuess(int row, int col, int guess)
{
	if(grid[row][col].bits & (1 << (guess - 1)) != 0)
	{
		grid[row][col].bits &= ~(1 << (guess - 1));
		grid[row][col].possibilities--;
	}
}
