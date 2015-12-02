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

void SudokuSquare::addPossible(int n)
{
	this->possible[n-1] = true;
}

void SudokuSquare::delPossible(int n)
{
	this->possible[n-1] = false;
}

bool SudokuSquare::isPossible(int n)
{
	return this->possible[n-1];
}

void SudokuSquare::clear()
{
	for(int i = 0; i < 9; i++)
		this->possible[i] = true;
	this->val = 0;
}