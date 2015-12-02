#include "sudoku_square.h"

SudokuSquare::SudokuSquare(int val)
{
	this->clear();
	this->val = val;
}

void SudokuSquare::set(int n)
{
	this->val = n;
}

int SudokuSquare::value()
{
	return this->val;
}

void SudokuSquare::addGuess(int n)
{
	this->guess[n-1] = true;
}

void SudokuSquare::delGuess(int n)
{
	this->guess[n-1] = false;
}

bool SudokuSquare::isGuess(int n)
{
	return this->guess[n-1];
}

int SudokuSquare::numGuesses()
{
	int num = 0;
	for(int i = 0; i < 9; i++){
		if(this->guess[i]) num++;
	}
	return num;
}


void SudokuSquare::clear()
{
	for(int i = 0; i < 9; i++)
		this->guess[i] = true;
	this->val = 0;
}