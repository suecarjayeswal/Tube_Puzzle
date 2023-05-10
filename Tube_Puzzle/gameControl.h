#pragma once
#include "TubeSet.h"
#include "stack.h"
#include "ActionStack.h"
#include "Queue.h"
#include <wx/wx.h>
class Game
{
private:
	TubeSet* tubes;
	int no_col;
	int no_tube;
	int tmp_tube_details[3];
	Stack** colTubStack;
	ActionStack* actions;
	Queue* redoActions;;
public:
	Game(int no_col, int no_tube, int* values);
	~Game();
	void resetTmpDetails();
	void pushIDinStack(int col, int color);
	void reverseStack(int col);
	void fillTmpDetails(int col_n, int color, int ID);
	void setTmpColNo(int col);
	int getTmpCol();	
	int getColStackTop(int col);	// get top element of stack
	int getColStackCount(int col);	// get the number of elements in the stack
	void makeColStackEmpty(int col_n); //make stack empty
	wxString traverseColStack(int col_n); //traverse
	wxString traverseColStackAll(); //traverse
	wxString traverseTubeSet(); //traverse tube set

	void swapTubesColor(int col1, int tub1, int col2, int tub2);
	int getColor(int column, int tube);
	wxColor getWXColor(int value);
	int getNumCols() const;
	int getNumTubes() const;

	bool isColEmpty(int col_n);
	bool isColFull(int col_n);
	void swapByClick(int col_n1, int col_n2);

	void saveStateOnSwapByClick();
	void revertAction();
};

