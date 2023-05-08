#pragma once
#include "TubeSet.h"
#include "stack.h"
class Game
{
private:
	TubeSet* tubes;
	int no_col;
	int no_tube;
	int tmp_tube_details[3];
	Stack** colTubStack;

public:
	Game(int no_col, int no_tube, int* values);
	~Game();
	void resetTmpDetails();
	void pushIDinStack(int col, int ID);
	void fillTmpDetails(int tub_n, int color, int ID);

	void swapTubesColor(int col1, int tub1, int col2, int tub2);

	bool isColEmpty(int col_n);
	bool isColFull(int col_n);
	void swapByClick(int col_n1, int col_n2);
};

