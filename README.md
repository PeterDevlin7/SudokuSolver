# SudokuSolver by Peter Devlin and Jasper Andrew
Final Project for CS 375

### SudokuBoard Class

**initFromFile:** Initializes the board from an input file<br/>
*@param* _**filepath:**_ the path to the input file
*@returns* `true` if the operation is successful, and `false` if not

**clearBoard:** Clears the contents of the board

**setSqr:** Sets the value of a square<br/>
*@param* _**row:**_ the row the target square is in<br/>
*@param* _**col:**_ the column the target square is in<br/>
*@param* _**x:**_ the value to put in the square
*@returns* `true` if the operation is successful, and `false` if not

**getSqr:** Gets the value of a square<br/>
*@param* _**row:**_ the row the target square is in<br/>
*@param* _**col:**_ the column the target square is in
*@returns* the value in the target square

**clearSqr:** Clears a single square's value<br/>
*@param* _**row:**_ the row the target square is in<br/>
*@param* _**col:**_ the column the target square is in

**rowHas:** Checks if a row contains a value<br/>
*@param* _**row:**_ the row to search
*@param* _**x:**_ the value to search for
*@returns* `true` if the row contains the value, and `false` if not

**colHas:** Checks if a column contains a value<br/>
*@param* _**col:**_ the column to search
*@param* _**x:**_ the value to search for
*@returns* `true` if the column contains the value, and `false` if not

**boxHas:** Checks if a 9-square box contains a value<br/>
*@para*m _**bRow:**_ the "box row" (1 to 3)
*@param* _**bCol:**_ the "box column" (1 to 3)
*@param* _**x:**_ the value to search for
*@returns* `true` if the box contains the value, and `false` if not

**isSolved:** Checks if the board is currently solved<br/>
*@returns* `true` if the board is solved, and `false` if not

**print:** Prints the board layout and contents<br/>
