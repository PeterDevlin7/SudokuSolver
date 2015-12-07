# SudokuSolver by Peter Devlin and Jasper Andrew
Final Project for CS 375

### SudokuBoard Class

**initFromFile:** Initializes the board from an input file<br/>
*@param* _**filepath:**_ the path to the input file<br/>
*@returns* `true` if the operation is successful, and `false` if not

**clearBoard:** Clears the contents of the board

**setSqr:** Sets the value of a square<br/>
*@param* _**row:**_ the row the target square is in<br/>
*@param* _**col:**_ the column the target square is in<br/>
*@param* _**x:**_ the value to put in the square<br/>
*@returns* `true` if the operation is successful, and `false` if not

**getSqr:** Gets the value of a square<br/>
*@param* _**row:**_ the row the target square is in<br/>
*@param* _**col:**_ the column the target square is in<br/>
*@returns* the value in the target square

**rowHas:** Checks if a row contains a value<br/>
*@param* _**row:**_ the row to search<br/>
*@param* _**x:**_ the value to search for<br/>
*@returns* `true` if the row contains the value, and `false` if not

**colHas:** Checks if a column contains a value<br/>
*@param* _**col:**_ the column to search<br/>
*@param* _**x:**_ the value to search for<br/>
*@returns* `true` if the column contains the value, and `false` if not

**boxHas:** Checks if a 9-square box contains a value<br/>
*@param* _**bRow:**_ the "box row" (1 to 3)<br/>
*@param* _**bCol:**_ the "box column" (1 to 3)<br/>
*@param* _**x:**_ the value to search for<br/>
*@returns* `true` if the box contains the value, and `false` if not

**isSolved:** Checks if the board is currently solved<br/>
*@returns* `true` if the board is solved, and `false` if not

**print:** Prints the board layout and contents<br/>

### SudokuSquare Class

**set:** Initializes the board from an input file<br/>
*@param* _**n:**_ the value to set the square to<br/>

**value:** Gets the value of the square
*@returns* The current value of the square

**addGuess:** Adds a value to the `guess` list<br/>
*@param* _**n:**_ the guess value to add<br/>

**delGuess:** Removes a value from the `guess` list<br/>
*@param* _**n:**_ the guess value to delete<br/>

**isGuess:** Checks if a square has a certain guess<br/>
*@param* _**n:**_ the value of the guess<br/>
*@returns* `true` if the guess is set for the square, and `false` if not

**numGuesses:** Checks if a column contains a value<br/>
*@returns* the number of guesses currently set

**clear:** Clears the square, setting `val` to 0 and all guesses to `true`<br/>