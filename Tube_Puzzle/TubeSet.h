//tubeset.h
#pragma once
#include <wx/wx.h>
class TubeSet {
public:
	TubeSet();
	TubeSet(int num_columns, int num_tubes);
	TubeSet( TubeSet* other);
	TubeSet& operator=(const TubeSet* other);
	~TubeSet();

	void fillArray(int* values);
	int getColor(int column, int tube) const;
	wxColor getWXColor(int value);
	int setColor(int column, int tube, int value);
	int getID(int column, int tube) const;
	void setID(int column, int tube, int value);
	wxString traverseTubeSet();

	int checkTubeMatch();
	int getTotalColNo();
private:
	int*** m_array;
	int m_num_columns;
	int m_num_tubes;
};
