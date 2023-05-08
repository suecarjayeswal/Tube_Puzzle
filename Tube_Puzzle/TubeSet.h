//GameControl.h
#pragma once
#include <wx/wx.h>
class TubeSet {
public:
	TubeSet(int num_columns, int num_tubes);
	~TubeSet();

	void fillArray(int* values);
	int getColor(int column, int tube);
	wxColor getWXColor(int value);
	int setColor(int column, int tube, int value);
	int getID(int column, int tube);
	void setID(int column, int tube, int value);
private:
	int*** m_array;
	int m_num_columns;
	int m_num_tubes;
};
