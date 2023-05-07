//GameControl.h
#pragma once
#include <wx/wx.h>
class TubeSet {
public:
	TubeSet(int num_columns, int num_tubes);
	~TubeSet();

	void fillArray(int* values);
	int get(int column, int tube);
	wxColor GetColor(int value);
	int setValue(int column, int tube, int value);
private:
	int** m_array;
	int m_num_columns;
	int m_num_tubes;
};