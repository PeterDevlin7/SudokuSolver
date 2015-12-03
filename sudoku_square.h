#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SudokuSquare
{
	public:
		SudokuSquare();
		void set(int n);
		int value();
		void addGuess(int n);
		void delGuess(int n);
		bool isGuess(int n);
		int numGuesses();
		void clear();
	private:
		int val;
		bool guess[9];
};

#endif
