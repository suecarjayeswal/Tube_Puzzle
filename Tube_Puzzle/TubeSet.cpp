//TubeSet.cpp
#include "TubeSet.h"
#include <iostream>
//TubeSet::TubeSet()
//{
//	
//	m_num_columns = (0); 
//	m_num_tubes = (0);
//	m_array = nullptr;
//
//}
TubeSet::TubeSet()
{
	m_num_columns = 3;
	m_num_tubes = 3;
	m_array = new int** [m_num_columns];
	for (int i = 0; i < m_num_columns; i++) {
		m_array[i] = new int* [m_num_tubes];
		for (int j = 0; j < m_num_tubes; j++) {
			m_array[i][j] = new int[2];
			m_array[i][j][0] = 0;
			m_array[i][j][1] = 0;
		}
	}
	wxLogDebug("Entered TubeSet defConstructor %p m_arr%p", this,m_array);
}
TubeSet::TubeSet(int num_columns = 3, int num_tubes = 3)
	: m_num_columns(num_columns), m_num_tubes(num_tubes)
{
	m_array = new int** [m_num_columns];
	for (int i = 0; i < m_num_columns; i++) {
		m_array[i] = new int* [m_num_tubes];
		for (int j = 0; j < m_num_tubes; j++) {
			m_array[i][j] = new int[2];
			m_array[i][j][0] = 0;
			m_array[i][j][1] = 0;
		}
	}
	wxLogDebug("Entered tubeSet constrWithCol%dTub%d m_arr%p %p",num_columns,num_tubes,m_array, this);
}

TubeSet::TubeSet( TubeSet* other)
{
	wxLogDebug("Entered tubeSet PointConstructor%p otherM_arr%p col%dtub%d m_arr%p this%p \n%s", other,other->m_array,other->m_num_columns,other->m_num_tubes,m_array, this, traverseTubeSet());
	m_num_columns = other->m_num_columns;
	m_num_tubes = other->m_num_tubes;
	m_array = new int** [m_num_columns];
	for (int i = 0; i < m_num_columns; i++) {
		m_array[i] = new int* [m_num_tubes];
		for (int j = 0; j < m_num_tubes; j++) {
			m_array[i][j] = new int[2];
			m_array[i][j][0] = other->getColor(i, j);
			m_array[i][j][1] = other->getID(i, j);
		}
	}
	wxLogDebug("Entered tubeSet PointConstructorthis%p M_arr%p col%dtub%d \n%s", this, this->m_array, this->m_num_columns, this->m_num_tubes, traverseTubeSet());
}
//
//TubeSet& TubeSet::operator=(const TubeSet* other) {
//	if (this != other) { // Avoid self-assignment
//		m_num_columns = other->m_num_columns;
//		m_num_tubes = other->m_num_tubes;
//		m_array = new int** [m_num_columns];
//		for (int i = 0; i < m_num_columns; i++) {
//			m_array[i] = new int* [m_num_tubes];
//			for (int j = 0; j < m_num_tubes; j++) {
//				m_array[i][j] = new int[2];
//				m_array[i][j][0] = other->getColor(i, j);
//				m_array[i][j][1] = other->getID(i, j);
//			}
//		}
//	}
//	return *this;
//}

TubeSet::~TubeSet()
{
	wxLogDebug("-------------inside tubeset Destructor m_arr%p %p",m_array, this);
	if (m_array != nullptr) {
		for (int i = 0; i < m_num_columns; i++) {
			if (m_array[i] != nullptr) {
				
				for (int j = 0; j < m_num_tubes; j++) {
					if (m_array[i][j] != nullptr)
					{
						delete[] m_array[i][j];
					}
				}
				delete[] m_array[i];
			}
		}
		delete[] m_array;
	}
}

void TubeSet::fillArray(int* values)
{
	int index = 0;
	for (int i = 0; i < m_num_columns; i++) {
		for (int j = 0; j < m_num_tubes; j++) {
			m_array[i][j][0] = values[index];
			index++;
		}
	}
}
int TubeSet::getColor(int col_n, int tube_n) const {
	if ((col_n < 0 || col_n >= m_num_columns) || (tube_n < 0 || tube_n >= m_num_tubes)) {
		return 0;
	}
	return m_array[col_n][tube_n][0];
}
wxColor TubeSet::getWXColor(int value) {
	wxColor color;
	switch (value) {
	case 1:
		color = wxColor(255, 0, 0); // Red
		break;
	case 2:
		color = wxColor(0, 255, 0); // Green
		break;
	case 3:
		color = wxColor(0, 0, 255); // Blue
		break;
	case 4:
		color = wxColor(255, 255, 0); // Yellow
		break;
	case 5:
		color = wxColor(255, 0, 255); // Magenta
		break;
	default:
		color = wxColor(255, 255, 255); // White
		break;
	}
	return color;
}
int TubeSet::setColor(int column, int tube, int value)
{
	int originalValue = m_array[column][tube][0];
	m_array[column][tube][0] = value;
	return originalValue;
}

int TubeSet::getID(int column, int tube) const
{
	return m_array[column][tube][1];
}

void TubeSet::setID(int column, int tube, int value)
{
	m_array[column][tube][1] = value;
}

wxString TubeSet::traverseTubeSet()
{

	wxString str = wxString::Format(" ");
	if (this == nullptr) return str;
	for (int i = 0;i < m_num_columns;i++) {
		for (int Index = 0; Index < m_num_tubes; Index++)
		{
			char buffer[16];
			sprintf_s(buffer, "%d", m_array[i][Index][0]);
			if (str.length() > 1)
				str.Append(" ");
			str.Append(buffer);
		}
		char buffer[16];
		if(i%2==0) sprintf_s(buffer, "\n");
		else sprintf_s(buffer, "\t");
		if (str.length() > 1)
			str.Append(" ");
		str.Append(buffer);
	}
	return str;
}

int TubeSet::getTotalColNo()
{
	return m_num_columns;
}
