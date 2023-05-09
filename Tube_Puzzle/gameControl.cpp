#include "GameControl.h"

Game::Game(int no_col, int no_tube, int* values) :no_col(no_col), no_tube(no_tube), tmp_tube_details{}
{
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
}

Game::~Game()
{
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

bool Game::isColFull(int col_n)
{
	if (colTubStack[col_n]->isFull()) {
		return true;
	}
	return false;
}

void Game::swapByClick(int col_n1, int col_n2)
{
	if( col_n1 != -1){

		if (!isColEmpty(col_n1) && !isColFull(col_n2)) {
			int tub_n = (colTubStack[col_n1]->pop())%100-1;

			swapTubesColor(col_n1, tub_n, col_n2, no_tube - (colTubStack[col_n2]->count())-2);
			colTubStack[col_n2]->push(tub_n);
			tmp_tube_details[0] = -1;

			//register the action 
			wxLogDebug("Action Deemed to Register");
			actions->push(tubes,colTubStack,no_col);
			redoActions->makeEmpty();
		}
	}
}
void Game::revertAction()
{

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