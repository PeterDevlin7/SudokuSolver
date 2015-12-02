#include "sudoku_board.h"
#include "sudoku_square.h"

void sudokuSolve(SudokuBoard board);
void testBoard(SudokuBoard board);

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "[ERROR] Invalid argument(s)\n[NOTE] Usage: run <filepath>\n";
		return -1;
	}
	
	SudokuBoard branson;
	if(branson.initFromFile(argv[1]))
	{
		testBoard(branson);
		//sudokuSolve(branson);
		return 0;
	}
	else return -1;
}
/*
void sudokuSolve(SudokuBoard board)
{
  for(int i = 1; i <= 9; i++)
	{
		for(int j = 1; j <= 9; j++)
		{
			if(board.getSqr(i,j).value != 0)
			{
        int value = board.getSqr(i,j).value;
				for(int k = 1; k <= 9; k++) //Check row for any new finds based on this elimination
				{
					if(k != j && board.getSqr(i,k).value == 0)
					{
            int count = 0; int index = -1;
						board.getSqr(i,k).possibilities[value-1] = 0;
						for(int l = 1; l <= 9; l++)
						{
							if(board.getSqr(i,k).possibilities[l-1] == 1)
							{
								count++;
								index = l;
							}
						}
						if(count == 1) board.setSqr(i,k,index);
					}
				}
        for(int m = 1; m <= 9; m++) //Check column for any new finds based on this elimination
				{
					if(m != i && board.getSqr(m,j).value == 0)
					{
            int count = 0; int index = -1;
						board.getSqr(m,j).possibilities[value-1] = 0;
						for(int l = 1; l <= 9; l++)
						{
							if(board.getSqr(m,j).possibilities[l-1] == 1)
							{
								count++;
								index = l;
							}
						}
						if(count == 1) board.setSqr(m,j,index);
					}
				}
				int boxRow = (i + 2) / 3; //i.e 0 corresponds to box row 1
				int boxCol = (j + 2) / 3; //Check box for any new finds based on this elimination
				//std::cout << "boxRow = " << boxRow << std::endl;
				//std::cout << "boxCol = " << boxCol << std::endl;
        for(int r = (3*boxRow)-2; r <= 3*boxRow; r++)
				{
					for(int c = (3*boxCol)-2; c <= 3*boxCol; c++) //lel
					{
						if(r != i && c != j && board.getSqr(r,c).value == 0)
						{
							int count = 0; int index = -1;
							board.getSqr(r,c).possibilities[value-1] = 0;
							for(int l = 1; l <= 9; l++)
							{
								if(board.getSqr(r,c).possibilities[l-1] == 1)
								{
									count++;
									index = l;
								}
							}
							if(count == 1) board.setSqr(r,c,index);
						}
					}
				}
			}
			if(board.getSqr(i,j).value == 0)
			{
				for(int n = 1; n <= 9; n++)
				{
					if(board.getSqr(i,j).possibilities[n-1] == 1)
					{
						if(board.rowHas(i, n)) board.getSqr(i,j).possibilities[n-1] = 0;
            if(board.colHas(j, n)) board.getSqr(i,j).possibilities[n-1] = 0;
						if(board.boxHas((i+2)/3,(j+2)/3,n)) board.getSqr(i,j).possibilities[n-1] = 0;
						//Check for row and column insufficiencies
						int relatives = 0; int indices [9];
						int crelatives = 0; int cindices [9];
						for(int h = 1; h <= 9; h++)
						{ 
							if(h != j && board.getSqr(i,h).value == 0 && board.getSqr(i,h).possibilities[n-1] == 1)
							{
								indices[relatives] = h;
								relatives++;
							}
							if(h != i && board.getSqr(h,j).value == 0 && board.getSqr(h,j).possibilities[n-1] == 1)
							{
								cindices[crelatives] = h;
								crelatives++;
							}
						}
						if(relatives >= 3)
						{
							int pairs [relatives][2];
							for(int v = 0; v < relatives; v++)
							{
								int possibilities = 0;
								for(int y = 1; y <= 9; y++)
								{
									if(board.getSqr(i,indices[v]).possibilities[y-1] == 1) possibilities++;
								}
								if(possibilities == 3)
								{
									for(int w = 1; w <= 9; w++)
									{
										int index = 0;
										if(w != n && board.getSqr(i,indices[v]).possibilities[w-1] == 1)
										{
											pairs[v][index] = w; index++;
										}
									}
								}
								else
								{
									pairs[v][0] = -1;
									pairs[v][1] = -1;
								}
							}
							//Determine if three cells have the same 3 possibilities
							int z, a, d;
							int f = -1;
							for(z = 0; z < relatives; z++)
								for(a = 1; a < relatives; a++)
									for(d = 2; d < relatives; d++)
									{
										if(pairs[z][0] != -1 && pairs[z][0] == pairs[a][0] && pairs[z][1] == pairs[a][1] \
																				 && pairs[a][0] == pairs[d][0] && pairs[a][1] == pairs[d][1] \
																				 && z != a && z != d && a != d)
										{
											f = 1;
											break;
										}
									}
							if(f == 1) board.getSqr(i,j).possibilities[n-1] = 0;
						}
						if(crelatives >= 3)
						{
							int pairs [crelatives][2];
							for(int v = 0; v < crelatives; v++)
							{
								int possibilities = 0;
								for(int y = 1; y <= 9; y++)
								{
									if(board.getSqr(cindices[v],j).possibilities[y-1] == 1) possibilities++;
								}
								if(possibilities == 3)
								{
									for(int w = 1; w <= 9; w++)
									{
										int index = 0;
										if(w != n && board.getSqr(cindices[v],j).possibilities[w-1] == 1)
										{
											pairs[v][index] = w; index++;
										}
									}
								}
								else
								{
									pairs[v][0] = -1;
									pairs[v][1] = -1;
								}
							}
							//Determine if three cells have the same 3 possibilities
							int z, a, d;
							int f = -1;
							for(z = 0; z < crelatives; z++)
								for(a = 1; a < crelatives; a++)
									for(d = 2; d < crelatives; d++)
									{
										if(pairs[z][0] != -1 && pairs[z][0] == pairs[a][0] && pairs[z][1] == pairs[a][1] \
																				 && pairs[a][0] == pairs[d][0] && pairs[a][1] == pairs[d][1] \
																				 && z != a && z != d && a != d)
										{
											f = 1;
											break;
										}
									}
							if(f == 1) board.getSqr(i,j).possibilities[n-1] = 0;
						}
					}
				}
        int count = 0; int index = -1;
				for(int g = 1; g <= 9; g++)
				{
					if(board.getSqr(i,j).possibilities[g-1] == 1)
					{
						count++;
						index = g;
					}
				}
				if(count == 1) board.setSqr(i,j,index);
			}
		}
	}
	if(!board.isSolved()) sudokuSolve(board);
	board.print();
}
*/

void testBoard(SudokuBoard board)
{
	cout << "\n:::: TESTING SUDOKUBOARD METHODS ::::\n";
	cout << "\n:: setSqr ::\n";
	for(int i = -1; i < 11; i++){
		board.setSqr(i, 2, 7);
	}
	
	cout << "\n:: clearSqr ::\n";
	board.clearSqr(4, 2);
	
	cout << "\n:: rowHas ::\n";
	if(board.rowHas(5, 7))
		cout << "Row 5 has 7\n";
	
	cout << "\n:: colHas ::\n";
	if(board.colHas(8, 6))
		cout << "Col 8 has 6\n";
	
	cout << "\n:: boxHas ::\n";
	if(board.boxHas(1, 4, 4))
		cout << "Box 3 has 4\n";
	
	cout << "\n:: isSolved ::\n";
	board.isSolved();
	
	cout << "\n:: print ::\n";
	board.print();
}

