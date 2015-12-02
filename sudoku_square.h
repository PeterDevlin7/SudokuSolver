#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class SudokuSquare
{
	public:
		SudokuSquare(int val = 0);
		void set(int n);
		int value();
		void addPossible(int n);
		void delPossible(int n);
		bool isPossible(int n);
		void clear();
	private:
		int val;
		bool possible[9];
};

#endif

