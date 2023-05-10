#include "GameControl.h"

Game::Game(int no_col, int no_tube, int* values) :no_col(no_col), no_tube(no_tube), tmp_tube_details{}
{
	// wxLogDebug("Entered Game contructor %p col-%d tub-%d val%p", this,no_col,no_tube,values);
	// initializing tubeSet
	tubes = new TubeSet(no_col, no_tube);
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
	redoActions = new Queue();
	// wxLogDebug("gameConstructor tubes%p colTubStack%p actions%p redoAc%p", tubes, colTubStack, actions, redoActions);
}

Game::~Game()
{
	// wxLogDebug("-------------------Entered Game Destructor %p colTubStack%p actions%p redoAc%p", this,colTubStack,actions,redoActions);
	for (int Index = 0; Index < no_col; Index++)
	{
		delete colTubStack[Index];
	}
	delete[] colTubStack;
	delete actions;
	delete redoActions;
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

bool Game::isColEmpty(int col_n)
{
	if (colTubStack[col_n]->isEmpty()) {
		return true;
	}
	return false;
}

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

void Game::swapByClick(int col_n1, int col_n2)
{
	// wxLogDebug("enter SwapBy Click");
	if( col_n1 != -1){

		if (!isColEmpty(col_n1) && !isColFull(col_n2)) {
			int tub_n = (colTubStack[col_n1]->pop())%100-1;

			swapTubesColor(col_n1, tub_n, col_n2, no_tube - (colTubStack[col_n2]->count())-2);
			colTubStack[col_n2]->push(tub_n);
			tmp_tube_details[0] = -1;

			saveStateOnSwapByClick();
		}
	}
}
void Game::saveStateOnSwapByClick() {
	//register the action 
	// wxLogDebug("Action Deemed to Register");
	// wxLogDebug("Tubes%s",traverseTubeSet());
	// wxLogDebug("ColStac%s", traverseColStackAll());

	actions->push(tubes, colTubStack, no_col);
	redoActions->makeEmpty();
}
void Game::revertAction()
{
	// wxLogDebug("inside revertAction%p tubes%p stack%p noCOl%d",this,tubes,colTubStack,no_col);
	if (!actions->isEmpty())
	{
		colTubStack = actions->topColStack();
		TubeSet* tmpTubes = actions->pop();
		// wxLogDebug("inside mid revert col%p tmpTub%p",colTubStack,tmpTubes);
		// wxLogDebug("%s", traverseColStackAll());
		// wxLogDebug("%s", traverseTubeSet());
		redoActions->enqueue(tmpTubes, colTubStack, no_col);
		//if(!actions->isEmpty()) tmpTubes = actions->pop();
		tubes = tmpTubes;
	}
	else {
		// wxLogDebug("no actions to undo");
		wxLogStatus(wxString::Format("no actions to undo"));
	}

	// wxLogDebug("Inside revertAction redAc%p tubes%p \n%s",redoActions,tubes, traverseTubeSet());
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