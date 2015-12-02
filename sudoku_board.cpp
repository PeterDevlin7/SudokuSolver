#include "sudoku_board.h"
#include "sudoku_square.h"

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
			this->grid[i][j].clear();
		}
}

bool SudokuBoard::setSqr(int row, int col, int n)
{
	if(n < 0 || n > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid value '" << n << "'\n";
		return false;
	}
	if(row < 1 || row > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid row '" << row << "'\n";
		return false;
	}
	if(col < 1 || col > 9){
		cout << "[ERROR] setSqr: (" << row << ", " << col << ") not updated: Invalid column '" << col << "'\n";
		return false;
	}
	
	this->grid[row-1][col-1].set(n);
	
	if(n == 0){
		for(int k = 0; k < 9; k++)
			this->grid[row-1][col-1].addPossible(k);
	}else{
		for(int k = 0; k < 9; k++)
			this->grid[row-1][col-1].delPossible(k);
		this->grid[row-1][col-1].addPossible(n-1);
	}
	
	return true;
}

SudokuSquare SudokuBoard::getSqr(int row, int col)
{
	SudokuSquare errSqr(-1);
	if(row < 1 || row > 9){
		cout << "[ERROR] getSqr: (" << row << ", " << col << ") not updated: Invalid row '" << row << "'\n";
		return errSqr;
	}
	if(col < 1 || col > 9){
		cout << "[ERROR] getSqr: (" << row << ", " << col << ") not updated: Invalid column '" << col << "'\n";
		return errSqr;
	}
	return this->grid[row-1][col-1];
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
	grid[row-1][col-1].clear();
}

bool SudokuBoard::rowHas(int row, int n)
{
  if(row < 1 || row > 9){
		cout << "[ERROR] rowHas: " << row << ". Invalid row '" << row << "'\n";
		return false;
	}
	for(int i = 0; i < 9; i++){
		if (grid[row-1][i].value() == n)
			return true;
	}
	return false;
}

bool SudokuBoard::colHas(int col, int n)
{
  if(col < 1 || col > 9){
		cout << "[ERROR] colHas: " << col << ". Invalid column '" << col << "'\n";
		return false;
	}
	for(int i = 0; i < 9; i++){
		if (grid[i][col-1].value() == n)
			return true;
	}
	return false;
}

bool SudokuBoard::boxHas(int bRow, int bCol, int n)
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
			if (grid[rows[i]-1][cols[j]-1].value() == n)
			return true;
		}
	}
	return false;
}

bool SudokuBoard::isSolved()
{
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(grid[i][j].value() == 0) return false;
		}
	}
    return true; // Can be more thorough, although I have faith the algorithm will stop when it's solved.
}				 // I agree. It shouldn't be hard to make it better. I'll do that.

void SudokuBoard::print()
{
	cout << "    1   2   3   4   5   6   7   8   9  \n";
	cout << "  #####################################\n";

	for(int i = 0; i < 9; i++){
		cout << i+1 << " # ";

		for(int j = 0; j < 9; j++){
			if(grid[i][j].value() == 0)
				cout << " ";
			else
				cout << grid[i][j].value();

			if(j == 8){
				if((i-1) % 3 == 0)
					cout << " # " << (i == 1 ? i : i-((i+1)/2));
				else
					cout << " #";
			}else if((j+1) % 3 == 0)
				cout << " # ";
			else
				cout << " | ";
		}
		if(i == 8){
			cout << "\n  #####################################\n";
			cout <<   "        1           2           3\n";
		}else if((i+1) % 3 == 0)
			cout << "\n  #####################################\n";
		else
			cout << "\n  #-----------#-----------#-----------#\n";
	}
}

