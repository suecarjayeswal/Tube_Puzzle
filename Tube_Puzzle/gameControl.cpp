#include "GameControl.h"

Game::Game(int no_col, int no_tube, int* values) :no_col(no_col), no_tube(no_tube)
{
	tubes = new TubeSet(no_col, no_tube);
	tubes->fillArray(values);

	colTubStack = new Stack * [no_col];
	for (int Index = 0; Index < no_col; Index++)
	{
		colTubStack[Index] = new Stack(no_tube);
	}

}

Game::~Game()
{
	delete[] tubes;
	for (int Index = 0; Index < no_col; Index++)
	{
		delete colTubStack[Index];
	}
	delete[] colTubStack;
}

void Game::resetTmpDetails() {
	tmp_tube_details[0] = 0;
	tmp_tube_details[1] = 0;
	tmp_tube_details[2] = 0;
}

void Game::pushIDinStack(int col, int ID)
{
	colTubStack[col]->push(ID);
}

void Game::swapTubesColor(int col1, int tub1, int col2, int tub2)
{
	int tmp = tubes->getColor(col1, tub1);
	tubes->setColor(col1, tub1, tubes->getColor(col1, tub1));
	tubes->setColor(col2, tub2, tmp);
}

void Game::fillTmpDetails(int tub_n, int color, int ID)
{
	tmp_tube_details[0] = tub_n;
	tmp_tube_details[1] = color;
	tmp_tube_details[2] = ID;
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
	if (!isColEmpty(col_n1) && !isColFull(col_n2)) {
		swapTubesColor(col_n1, colTubStack[col_n1]->count(), col_n2, colTubStack[col_n2]->count());
	}
}
