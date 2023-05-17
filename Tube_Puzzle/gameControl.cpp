// GameControl implementation file
#include "GameControl.h"

/**
 * The function initializes a game object with given parameters and initializes tubeSet, column stacks, and action queues.
 *
 * @param no_col The number of columns in the game.
 * @param no_tube The number of tubes in the game.
 * @param values An array of integers representing the initial state of the game board. The array is of size no_col *
 * no_tube, where no_col is the number of columns and no_tube is the number of tubes. Each element of the array represents
 * the color of a ball in the game board.
 */
Game::Game(int no_col, int no_tube, int* values) :no_col(no_col), no_tube(no_tube),stepsCount(0), undoCount(0), redoCount(0), tmp_tube_details{}
{
	// initializing tubeSet
	tubes = new TubeSet(no_col, no_tube);
	this->values = new int[no_col * no_tube];
	for (int Index = 0; Index < no_col * no_tube; Index++) this->values[Index] = values[Index];
	tubes->fillArray(values);

	// initializing column Stacks
	colTubStack = new Stack * [no_col];
	for (int Index = 0; Index < no_col; Index++)
	{
		colTubStack[Index] = new Stack(no_tube);
	}
	resetTmpDetails();

	//initializing actions Queue
	actions = new ActionStack();
	redoActions = new ActionStack();
}

/**
 * The destructor of the Game class deletes various dynamically allocated objects.
 */
Game::~Game()
{
	// wxLogDebug("-------------------Entered Game Destructor %p colTubStack%p actions%p redoAc%p", this,colTubStack,actions,redoActions);
	for (int Index = 0; Index < no_col; Index++)
	{
		delete colTubStack[Index];
	}
//	delete[] colTubStack;
	delete actions;
	delete redoActions;
	delete values;
}

void Game::resetTmpDetails() {
	tmp_tube_details[0] = -1;
	tmp_tube_details[1] = 0;
	tmp_tube_details[2] = 0;
}

void Game::pushIDinStack(int col, int ID)
{

	colTubStack[col]->push(ID);
}

void Game::reverseStack(int col)
{
	colTubStack[col]->reverse();
}

void Game::swapTubesColor(int col1, int tub1, int col2, int tub2)
{
	int tmp = tubes->getColor(col1, tub1);
	tubes->setColor(col1, tub1, tubes->getColor(col2, tub2));
	tubes->setColor(col2, tub2, tmp);
}

int Game::getColor(int column, int tube)
{
	//// wxLogDebug("\t\t GamegetColor%p  %d %d", tubes, column, tube);
	return tubes->getColor(column, tube);
}

/**
 * This function returns a wxColor object based on a given integer value.
 *
 * @param value The parameter "value" is an integer value that is passed to the function "getWXColor". It is used to
 * determine the color that should be returned by the function. The function likely uses this value to look up a specific
 * color from a color palette or map.
 *
 * @return A wxColor object is being returned. The wxColor object is obtained by calling the getWXColor() method of the
 * tubes object, passing in the value parameter.
 */
wxColor Game::getWXColor(int value)
{
	return tubes->getWXColor(value);
}

void Game::fillTmpDetails(int col_n, int color=0, int ID=0)
{
	tmp_tube_details[0] = col_n;
	tmp_tube_details[1] = color;
	tmp_tube_details[2] = ID;
}

void Game::setTmpColNo(int col)
{
	tmp_tube_details[0] = col;
}

int Game::getTmpCol()
{
	return tmp_tube_details[0];
}

int Game::getColStackTop(int col)
{
	return colTubStack[col]->top();
}

int Game::getColStackCount(int col)
{
	return colTubStack[col]->count();
}

void Game::makeColStackEmpty(int col_n)
{
	colTubStack[col_n]->makeEmpty();
}

wxString Game::traverseColStack(int col_n)
{

	return colTubStack[col_n]->traverse();
}

/**
 * The function checks if a specified column in a game is empty.
 *
 * @param col_n The parameter `col_n` is an integer representing the column number in a game board.
 *
 * @return The function `isColEmpty` returns a boolean value (`true` or `false`) depending on whether the column specified
 * by `col_n` is empty or not. If the column is empty, the function returns `true`, otherwise it returns `false`.
 */
bool Game::isColEmpty(int col_n)
{
	if (colTubStack[col_n]->isEmpty()) {
		return true;
	}
	return false;
}

/**
 * The function traverses all columns in a game and returns a string representation of the stack in each column.
 *
 * @return A wxString object that contains the result of calling the traverseColStack function for each column in the Game
 * object, with each result separated by a newline character.
 */
wxString Game::traverseColStackAll()
{
	wxString str = wxString::Format(" ");
	for (int Index = 0; Index <no_col; Index++)
	{

		str.Append("\n").Append(traverseColStack(Index));
	}
	return str;
}

bool Game::isColFull(int col_n)
{
	if (colTubStack[col_n]->isFull()) {
		return true;
	}
	return false;
}

/**
 * This function swaps two tubes in a game if the move is valid and updates the game state accordingly.
 *
 * @param col_n1 The index of the column from which a tube is being moved.
 * @param col_n2 col_n2 is an integer variable representing the index of the column where the second tube will be swapped
 * to.
 *
 * @return a boolean value. It returns true if the move is valid and the tubes are swapped successfully, and false if the
 * move is invalid.
 */
bool Game::swapByClick(int col_n1, int col_n2)
{
	// wxLogDebug("enter SwapBy Click");
	if( col_n1 != -1){

		if (checkMoveValidity(col_n1,col_n2)) {
			int tub_n = (colTubStack[col_n1]->pop())%100-1;

			swapTubesColor(col_n1, tub_n, col_n2, no_tube - (colTubStack[col_n2]->count())-2);
			colTubStack[col_n2]->push(tub_n);
			tmp_tube_details[0] = -1;

			saveStateOnSwapByClick();

			stepsCount++;
			undoCount = 0;
			redoCount = 0;
			return true;
		}
		else {
			wxLogStatus(wxString::Format("Invalid Move"));
			return false;
		}
	}
}
/**
 * The function checks the validity of a move in a game by comparing the colors of the topmost tubes in two columns and
 * ensuring that the source column is not empty and the destination column is not full.
 *
 * @param col_n1 The column number of the tube from which a ball is being moved.
 * @param col_n2 The parameter col_n2 represents the index of the column (or pile) where the player wants to move a card
 * to.
 *
 * @return a boolean value.
 */
bool Game::checkMoveValidity(int col_n1, int col_n2) {
	bool tmp = getColor(col_n1, colTubStack[col_n1]->top() % 100 - 1) == getColor(col_n2, no_tube - (colTubStack[col_n2]->count()) - 1);
	tmp = tmp || getColor(col_n2, no_tube - (colTubStack[col_n2]->count()) - 1)==0;

	return tmp && !isColEmpty(col_n1) && !isColFull(col_n2);
}
/**
 * This function saves the current state of the game when the player swaps two tubes by clicking on them.
 */
void Game::saveStateOnSwapByClick() {
	actions->push(tubes, colTubStack, no_col);
	redoActions->makeEmpty();
}
/**
 * The function reverts the last action taken in a game by popping the top element from a stack and pushing it onto another
 * stack for redoing.
 */
void Game::revertAction()
{
	// wxLogDebug("inside revertAction%p tubes%p stack%p noCOl%d",this,tubes,colTubStack,no_col);
	if (!actions->isEmpty())
	{
		colTubStack = actions->topColStack();
		TubeSet* tmpTubes = actions->pop();
		tubes = tmpTubes;
		redoActions->push(tmpTubes, colTubStack, no_col);
		if (undoCount==0)
		{
			colTubStack = actions->topColStack();
			tmpTubes = actions->pop();
			tubes = tmpTubes;
			redoActions->push(tmpTubes, colTubStack, no_col);
		}

		undoCount++;
		stepsCount++;
	}
	else {
		// wxLogDebug("no actions to undo");
		wxLogStatus(wxString::Format("no actions to undo"));
	}

	// wxLogDebug("Inside revertAction redAc%p tubes%p \n%s",redoActions,tubes, traverseTubeSet());
}
/**
 * This function undoes a previous action and reverts the game state to its previous state.
 */
void Game::undoRevert()
{
	if (!redoActions->isEmpty())
	{
		colTubStack = redoActions->topColStack();
		TubeSet* tmpTubes = redoActions->pop();
		tubes = tmpTubes;
		if (redoCount == 0)
		{
			colTubStack = redoActions->topColStack();
			tmpTubes = redoActions->pop();
			tubes = tmpTubes;
		}
		actions->push(tmpTubes, colTubStack, no_col);

		stepsCount++;
		redoCount++;
	}
	else {
		wxLogStatus(wxString::Format("no actions to Undorevert"));
	}
}
/**
 * The function hardReset resets the game by emptying actions and redoActions, filling tubes with values, resetting
 * undoCount, redoCount, and stepsCount, and initializing column stacks.
 */
void Game::hardReset()
{
	actions->makeEmpty();
	redoActions->makeEmpty();
	tubes->fillArray(values);
	undoCount = 0;
	redoCount = 0;
	stepsCount = 0;
	resetTmpDetails();

	// deleting ealier colStack
	for (int Index = 0; Index < no_col; Index++)
	{
		delete colTubStack[Index];
	}
	delete[] colTubStack;
	// initializing column Stacks
	colTubStack = new Stack * [no_col];
	for (int Index = 0; Index < no_col; Index++)
	{
		colTubStack[Index] = new Stack(no_tube);
	}
}

/**
 * The function checks if the current round of the game is complete by calling the checkTubeMatch function of the tubes
 * object and returning its result.
 *
 * @return The function `roundCompleteCheck()` is returning the result of the function call `tubes->checkTubeMatch()`. The
 * value returned by `checkTubeMatch()` is being compared to 0 using the equality operator `==`. If the result is equal to
 * 0, then `roundCompleteCheck()` will return 1, indicating that the round is complete. If the result is not equal to
 */
int Game::roundCompleteCheck()
{
	return tubes->checkTubeMatch()==0;
}

int Game::getNumCols() const {
	return no_col;
}

wxString Game::traverseTubeSet()
{
	return tubes->traverseTubeSet();
}

int Game::getNumTubes() const {
	return no_tube;
}
int Game::getStepsCount() const {
	return stepsCount;
}
